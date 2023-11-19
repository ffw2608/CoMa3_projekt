
#include <QtWidgets>
#include <QApplication>

/*** Klasse Musiktafel ***/

class Musiktafel : public QWidget
{
public:

/*** Konstruktor ***/

    Musiktafel(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFixedSize(500, 300); // Festlegen der Größe des Widgets
        initializeLines(); // Initialisierung der Linien
    }


protected:

/*** Punkte Zeichnen ***/

    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);

        // Zeichnen der Linien
        painter.setPen(Qt::black);
        for (const QLineF& line : lines)
        {
            painter.drawLine(line);
        }

        // Zeichnen der Punkte
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        for (const QPointF& point : points)
        {
            painter.drawEllipse(point, pointSize, pointSize);
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
            // Bei einem Linksklick: Einen Punkt hinzufügen und neu zeichnen
            addOrRemovePoint(event->pos());
            update();
        }
    }


private:

/*** Attribute ***/

    QVector<QLineF> lines;
    QVector<QPointF> points;
    const int numLines = 11;
    const int pointSize = 5;
    const int pointSpacing = 20;


/*** Einfügen der Linien ***/

    void initializeLines()
    {
        const int spacing = height() / (numLines + 1);
        for (int i = 1; i <= numLines; i+=2 )
        {
            lines.append(QLineF(0, i * spacing, width(), i * spacing));
        }
    }


/*** Einfügen/Löschen der Punkte ***/

    void addOrRemovePoint(const QPoint& pos)
    {
        for (int i = 0; i < points.size(); ++i)
        {
            // Überprüfen, ob der Klick nahe genug am Punkt liegt, um ihn zu entfernen
            if (distance(pos, points[i]) < pointSize * 2)
            {
                points.remove(i);
                return;
            }
        }
        // Wenn kein Punkt zum Entfernen gefunden wurde, füge einen neuen hinzu
        addPoint(pos);
    }

    void addPoint(const QPoint& pos)
    {
        // Füge den Punkt auf der nächsten verfügbaren Linie hinzu
        const int lineSpacing = height() / (numLines + 1);
        const int closestLine = qRound((pos.y() + lineSpacing / 2.0) / lineSpacing) * lineSpacing;

        points.append(QPointF(pos.x(), closestLine));
        std::sort(points.begin(), points.end(), [](const QPointF &a, const QPointF &b)
                  {return a.x() < b.x();});

        // Vereinheitliche die Abstände zwischen den Punkten
        for (int i = 1; i < points.size(); ++i)
        {
            if (points[i].x() - points[i - 1].x() < pointSpacing)
            {
                points[i].setX(points[i - 1].x() + pointSpacing);
            }
        }
    }


/*** Hilfsmethoden ***/

    qreal distance(const QPointF& p1, const QPointF& p2)
    {
        return QLineF(p1, p2).length();
    }


};// Klasse Musiktafel Ende



/***  Main ***/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Musiktafel mt;
    mt.show();

    return app.exec();
}
