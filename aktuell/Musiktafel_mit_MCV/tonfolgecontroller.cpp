#include"tonfolgecontroller.h"
#include"tonfolgemodell.h"
#include"tonfolgewidget.h"

#include<QEvent>
#include<QMouseEvent>
#include<QKeyEvent>

#include<cstdlib>
#include<ctime>
#include<cmath>
#include<random>

//
TonfolgeController::TonfolgeController(TonfolgeModell& modell, TonfolgeWidget& ansicht, QObject* parent)
    : QObject(parent)
    , modell(modell)
    , ansicht(ansicht)
{
    ansicht.installEventFilter(this);
}

// Eventfilter um die Ereignise von der Ansicht (QuadrateWidget) abzufangen : MVC: die Ereignise werden von der Steuerung verarbeitet
bool TonfolgeController::eventFilter(QObject* /*watched*/, QEvent* event)
{
    switch(event->type())
    {
    // relevante Ereignistypen behandeln:
    case QEvent::MouseButtonPress:
        mousePressEvent(dynamic_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseMove:
        mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
        break;
    case QEvent::KeyPress:
        keyPressEvent(dynamic_cast<QKeyEvent*>(event));
        break;
    default:
        return false;
    }
    return event->isAccepted();
}

// Methoden analog zu dem alten QudarateWidget.
void TonfolgeController::mousePressEvent(QMouseEvent* event)
{
    const double breite = ansicht.width();
    const double hoehe  = ansicht.height();

    if(event->button() == Qt::RightButton) // Rechte Maustaste: Ein Quadrat einfügen;
    {
        // Logik für Farbwahl
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> farbDistribution(0, 255);

        // Farbe erzeugen
        uint8_t rot   = farbDistribution(gen);
        uint8_t gruen = farbDistribution(gen);
        uint8_t blau  = farbDistribution(gen);

        // Töne hinzufügen
        modell.tonHinzufuegen(TonfolgeModell::Ton(event->x()/breite
                                                , event->y()/hoehe
                                                , qRgb(rot, gruen, blau)
                                                  ));
        aktuellerTon = modell.laengeTonfolge() - 1; // neues Quadrat auswählen = letzte Quadrat
    }
    else
    {
        // Ein Qudrat finden ist in das Modell ausgelagert, deswegen nur die Modell-Methode aufrufen
        aktuellerTon = modell.findeTon(event->pos(), ansicht.size()); //
    }
}


void TonfolgeController::mouseMoveEvent(QMouseEvent* event)
{
    if(aktuellerTonGueltig()) // ein Quadrat aktiv?
    {
        // Neue Position für das Qudrat bestimmen
        QPointF neuePos(event->x()/static_cast<double>(ansicht.width ())
                        , event->y()/static_cast<double>(ansicht.height()));

        modell.verschiebeTon(aktuellerTon, neuePos); // Das Modell anweisen, das Qudarat mit der Nr »aktivesQuadrat« an die Position »neuePos« verschieben
    }
}


void TonfolgeController::keyPressEvent(QKeyEvent* event)
{
    if(!aktuellerTonGueltig()) // kein aktives Quadrat, Tastendrücke müssen nicht beachtet werden (Achtung: hierbei werden Tastendrücke weitergeleitet die ansonsten abgefangen worden wären)
        return event->ignore(); // Weiterleitung der Tastendrücke an QWidget und damit an die übergeordneten Widgets

    switch(event->key()) // Aktionen für die Tasten aufstellen
    {
    // Analog zu mouseMoveEvent das Qudarat verschieben, hier jetzt relativ um jeweils den Wert, den ein Pixel hat
    case Qt::Key_Left : modell.verschiebeTonRel(aktuellerTon, -1./ansicht.width (),                    0); break;
    case Qt::Key_Right: modell.verschiebeTonRel(aktuellerTon,  1./ansicht.width (),                    0); break;
    case Qt::Key_Up   : modell.verschiebeTonRel(aktuellerTon,                    0, -1./ansicht.height()); break;
    case Qt::Key_Down : modell.verschiebeTonRel(aktuellerTon,                    0,  1./ansicht.height()); break;
    case Qt::Key_Delete:
        modell.tonEntfernen(aktuellerTon); // Modell anweisen, das Qudarat zu löschen
        aktuellerTon = std::numeric_limits<std::size_t>::max(); // aktives Quadrad auf ungültigen Wert setzen
        break;
    default: // keine Taste die bearbeitet wird -> Aufruf der Methode vom Elternobjekt
        return event->ignore();
    }
}

// Prüfen um der aktuelle Quadrat-Index gültig ist
bool TonfolgeController::aktuellerTonGueltig() const
{
    return aktuellerTon < modell.laengeTonfolge();
}


