#include <QtWidgets>
#include <QApplication>
#include <QPainter>

/*** Klasse Musiktafel ***/

class Musiktafel : public QWidget
{
public:

    //    /*** Konstruktor ***/

    Musiktafel(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFixedSize(1000, 500); // Festlegen der Größe des Widgets
        initializeLines(); // Initialisierung der Linien
    }


protected:

    //    /*** Punkte Zeichnen ***/

    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);

        painter.setPen(Qt::black);
        for (int i = 0; i < lines.size(); i+=2)
        {
            if (    i == 0
                ||  i == 2
                ||  i == lines.size() / 2
                ||  i == lines.size() - 3
                ||  i == lines.size() - 1)
            {
                // Zeichne eine Gestrichelte Linie
                QVector<qreal> dashes = {20, 20};
                QPen dashedPen(Qt::DashLine);
                dashedPen.setColor(Qt::black);
                dashedPen.setDashPattern(dashes);
                painter.setPen(dashedPen);
                painter.drawLine(lines[i]);

                // Stelle den Stift wieder auf normalen Stil zurück
                painter.setPen(Qt::black);
            }
            else
            {
                painter.drawLine(lines[i]); // Zeichne normale Linien für andere Linien
            }
        }

        // Zeichnen der Punkte mit unterschiedlichen Farben basierend auf ihrer Linie
        for (const QPointF& point : points)
        {
            painter.setPen(QColor::fromHsvF(point.y() / height(), 1, 1)); // Farbe basierend auf der Y-Position setzen
            painter.setBrush(QColor::fromHsvF(point.y() / height(), 1, 1)); // Farbe basierend auf der Y-Position setzen
            painter.drawEllipse(point, pointSize, pointSize);
        }

    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            addOrRemovePoint(event->pos());
            update();
        }
    }


private:

    //  /*** Attribute ***/

    QVector<QLineF> lines;
    const int numLines = 29;
    const int lineSpacing = height() / (numLines);

    QVector<QPointF> points;
    const int pointSize = 5;
    const int pointSpacing = 20;
    const int startX = 10;


    //  /*** Einfügen der Linien ***/

    void initializeLines()
    {
        for (int i = 1; i <= numLines; ++i)
            lines.push_back(QLineF(0, i * lineSpacing, width(), i * lineSpacing));
    }


    //  /*** Einfügen/Löschen der Punkte ***/

    void addOrRemovePoint(const QPoint& pos)
    {
        for (int i = 0; i < points.size(); ++i)
        {
            // Überprüfen, ob der Klick nahe genug am Punkt liegt, um ihn zu entfernen
            if (distance(pos, points[i]) < pointSize * 2)
            {
                points.remove(i);
                adjustPoints();
                return;
            }
        }
        // Wenn kein Punkt zum Entfernen gefunden wurde, füge einen neuen hinzu
        addPoint(pos);
    }

    void addPoint(const QPoint& pos)
    {
        // Bestimmen der nächsten Linie, auch wenn die Klickposition nicht exakt auf einer Linie liegt
        int closestLine = qRound((pos.y() + lineSpacing / 2.0) / lineSpacing) * lineSpacing;

        // Begrenzung der Linienpositionen
        if (closestLine > height())
            closestLine = height();
        else if (closestLine < 0)
            closestLine = 0;


        // Finden des kleineren Abstands zur nächsten Linie
        int closestDistance = height(); // Größtmöglicher Anfangswert

        for (const QLineF& line : lines)
        {
            int distance = qAbs(line.y1() - pos.y());

            if (distance < closestDistance)
            {
                closestDistance = distance;
                closestLine = line.y1();
            }
        }

        // Festlegen der X-Koordinate auf die Mausposition (pos.x()) für die Punkteplatzierung
        // Auf der nächstgelegenen Linie
        points.append(QPointF(pos.x(), closestLine));
        std::sort(points.begin(), points.end(), [](const QPointF &a, const QPointF &b) {
            return a.x() < b.x();
        });
        adjustPoints();
    }

    void adjustPoints()
    {
        for (int i = 0; i < points.size(); ++i)
            points[i].setX(startX + i * pointSpacing);
    }


    //  /*** Hilfsmethoden ***/

    qreal distance(const QPointF& p1, const QPointF& p2)
    {
        return QLineF(p1, p2).length();
    }


};// Klasse Musiktafel Ende
