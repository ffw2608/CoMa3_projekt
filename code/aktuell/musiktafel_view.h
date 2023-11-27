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
    QVector<QPointF> punkte;
    const int punktSize = 5;


public:
    Musiktafel_view(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setFixedSize(1000, 500);
    }

    void setLines(const QVector<QLineF>& lines)
    {
        this->linien = lines;
        update();
    }

    void setPoints(const QVector<QPointF>& points)
    {
        this->punkte = points;
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
                QVector<qreal> dashes = {20, 20};
                QPen dashedPen(Qt::DashLine);
                dashedPen.setColor(Qt::black);
                dashedPen.setDashPattern(dashes);
                painter.setPen(dashedPen);
                painter.drawLine(linien[i]);
                painter.setPen(Qt::black);
            } else {
                painter.drawLine(linien[i]);
            }
        }

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);

        for (const QPointF& punkt : punkte)
        {
            painter.setBrush(QColor::fromHsvF(punkt.y() / height(), 1, 1));
            painter.drawEllipse(punkt, punktSize, punktSize);
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
