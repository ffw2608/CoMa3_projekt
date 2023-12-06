#ifndef MUSIKTAFEL_CONTROL_H
#define MUSIKTAFEL_CONTROL_H

#include <QObject>
#include <QVector>

#include "musiktafel_view.h"
#include "musiktafel_model.h"
class Musiktafel_control
    : public QObject
{
    Q_OBJECT

private:

    Musiktafel_view& view;
    Musiktafel_model& model;

    QVector<QLineF> linien;
    QVector<QPointF> punkte;

    int _hoehe              = 750   ;
    int _breite             = 1500  ;

    const int _ANZAHLLINIEN = 29    ;
    const int _STARTX       = 10    ;
    const int _PUNKTSIZE    = 10    ;

    int _linienAbstand      = _hoehe/_ANZAHLLINIEN;
    int _punkteAbstand      = _breite/_ANZAHLLINIEN;

    void initLinien()
    {
        for (int i = 1; i <= _ANZAHLLINIEN; i++)
        {
            linien.push_back(QLineF(0, i * _linienAbstand, _breite , i * _linienAbstand));
        }
    }

    void reformatPunkte()
    {
        // stellt festen Abstand und linksbündigkeit wieder her
        for (int i = 0; i < punkte.size(); ++i)
        {
            punkte[i].setX(_STARTX + i * _punkteAbstand);
        }
    }

public:

    Musiktafel_control(QObject *parent = nullptr)
        : QObject(parent)
    {
        initLinien();
    }

    void setView(Musiktafel_view *view)
    {
        this->view = view;

        connect(view, &Musiktafel_view::neuerPunkt, this, &Musiktafel_control::punktHinzufuegen);
        connect(view, &Musiktafel_view::punktLoeschen, this, &Musiktafel_control::punktEntfernen);

        view->setLinien(linien);
        view->setPunkte(punkte);
    }

private slots:

    void punktHinzufuegen(const QPointF& punkt)
    {
        // Um einen Punkt zu setzen, muss die rightige Linie gefunden werden.
        // Die richtige Linie ist die, die den geringsten Abstand zur Klickposition hat.
        // Aus der gefunden Linie ergibt sich die resultierende Höhe
        int zielHöhe = qRound((punkt.y() + _linienAbstand / 2.0) / _linienAbstand) * _linienAbstand;
            int minAbstand = view->height();
        for (const QLineF& linie : linien)
        {
            int abstand = qAbs(linie.y1() - punkt.y());
            if (abstand < minAbstand)
            {
                minAbstand = abstand;
                zielHöhe = linie.y1();
            }
        }

        // Setzt Punkt mit korrekter Höhe auf die Liste der anzuzeigenden Punkte
        punkte.append(QPointF(punkt.x(), zielHöhe));

        //*/
        // Für das Einfügen zwischen bestehenden Punkten
        std::sort(punkte.begin(), punkte.end(), [](const QPointF &a, const QPointF &b)
        {
            return a.x() < b.x();
        });
        //*/

        reformatPunkte();

        view->setPunkte(punkte);
    }

    void punktEntfernen(const QPointF& punkt)
    {
        for (int i = 0; i < punkte.size(); ++i)
        {
            if (messeAbstand(punkt, punkte[i]) < _PUNKTSIZE * 2)
            {
                punkte.remove(i);

                reformatPunkte();

                view->setPunkte(punkte);

                return;
            }
        }
    }

    qreal messeAbstand(const QPointF& p1, const QPointF& p2)
    {
        return QLineF(p1, p2).length();
    }

};
#endif // MUSIKTAFEL_CONTROL_H
