#ifndef MUSIKTAFEL_VIEW_H
#define MUSIKTAFEL_VIEW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QVector>

class Musiktafel_view
    : public QWidget
{
    Q_OBJECT
private:
    QVector<QLineF> linien;
    QVector<QPointF> view_punkte;
    const int    punktSize = 5;
    const double dashLen   = 20;
    const double dashSpace = 20;

public:
    Musiktafel_view(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setFixedSize(1500,750);
    }

    void setLinien(const QVector<QLineF>& punkte)
    {
        this->linien = punkte;
        update();
    }

    void setPunkte(const QVector<QPointF>& punkte)
    {
        this->view_punkte = punkte;
        update();
    }

signals:

    void neuerPunkt(const QPointF& punkt);
    void punktLoeschen(const QPointF& punkt);

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);

        // Linien und Strichellinien
        painter.setPen(Qt::black);
        for (int i = 0; i < linien.size(); i+=2)
        {
            if (
                i == 0 ||
                i == 2 ||
                i == linien.size() / 2 ||
                i == linien.size() - 3 ||
                i == linien.size() - 1
                )
            {
                // zeichne Strichellinie
                QVector<qreal> dashes = {dashLen, dashSpace};
                QPen dashedPen(Qt::DashLine);
                dashedPen.setColor(Qt::black);
                dashedPen.setDashPattern(dashes);
                painter.setPen(dashedPen);
                painter.drawLine(linien[i]);
                painter.setPen(Qt::black);
            }
            else
            {
                // zeichne Linie
                painter.drawLine(linien[i]);
            }
        }

        // zeichne die Punkte auf der Liste
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        for (const QPointF& v_punkt : view_punkte)
        {
            painter.setBrush(QColor::fromHsvF(v_punkt.y() / height(), 1, 1));
            painter.drawEllipse(v_punkt, punktSize, punktSize);
        }
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            QPointF punkt = event->pos();
            emit neuerPunkt(punkt);
        }
        if (event->button() == Qt::RightButton)
        {
            QPointF punkt = event->pos();
            emit punktLoeschen(punkt);
        }
    }
};

#endif // MUSIKTAFEL_VIEW_H
