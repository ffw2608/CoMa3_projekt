#ifndef MUSIKTAFEL_CONTROL_H
#define MUSIKTAFEL_CONTROL_H

#include <QObject>
#include <QVector>

#include "musiktafel_view.h"

class Musiktafel_control
    : public QObject
{
    Q_OBJECT

private:

    Musiktafel_view *view;

    QVector<QLineF> linien;
    QVector<QPointF> punkte;

    int _hoehe              = 500   ;
    int _breite             = 1000  ;

    const int _ANZAHLLINIEN = 29    ;
    const int _STARTX       = 10    ;
    const int _PUNKTSIZE    = 5;

    int _linienAbstand      = _hoehe/_ANZAHLLINIEN;
    int _punkteAbstand      = _breite/_ANZAHLLINIEN;



    void initLinien()
    {
        for (int i = 1; i <= _ANZAHLLINIEN; i++)
        {
            linien.push_back(QLineF(0, i * _linienAbstand, _breite , i * _linienAbstand));
        }
    }

    void setFormatPunkte()
    {

        for (int i = 0; i < punkte.size(); ++i) {
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
        view->setLines(linien);
        view->setPoints(punkte);
    }

private slots:

    void punktHinzufuegen(const QPointF& punkt)
{
        int minAbstandLinie = qRound((punkt.y() + _linienAbstand / 2.0) / _linienAbstand) * _linienAbstand;

        if (minAbstandLinie > view->height())
        {
            minAbstandLinie = view->height();
        }
        else if (minAbstandLinie < 0)
        {
            minAbstandLinie = 0;
        }

        punkte.append(QPointF(punkt.x(), minAbstandLinie));
        std::sort(punkte.begin(), punkte.end(), [](const QPointF &a, const QPointF &b) {
            return a.x() < b.x();
        });

        setFormatPunkte();

        view->setPoints(punkte);
    }

    void punktEntfernen(const QPointF& punkt)
    {
        for (int i = 0; i < punkte.size(); ++i)
        {
            if (abstand(punkt, punkte[i]) < _PUNKTSIZE * 2)
            {
                punkte.remove(i);

                setFormatPunkte();

                view->setPoints(punkte);

                return;
            }
        }
}
    //  /*** Hilfsmethoden ***/

    qreal abstand(const QPointF& p1, const QPointF& p2)
    {
        return QLineF(p1, p2).length();
    }
};
#endif // MUSIKTAFEL_CONTROL_H
