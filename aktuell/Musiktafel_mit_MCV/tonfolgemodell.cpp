#include "tonfolgemodell.h"

#include<algorithm>
#include<random>
#include<cmath>

#include<QSize>
#include<QPoint>
#include<QRectF>

TonfolgeModell::TonfolgeModell(QObject* parent)
    : QObject(parent)
{

}

// Methode um ein Quadrat an der angegebenen Position zu suchen und den Index zurück zu geben. Die Funktionalität wurde aus der ehemaligen QudrateWidget::mousePressEvent extraiert
std::size_t TonfolgeModell::findeTon(const QPoint& pos, const QSize& widgetgroese) const
{
    const double breite = widgetgroese.width();
    const double hoehe  = widgetgroese.height();

    QRectF suchRect((pos.x()-20)/breite
                    , (pos.y()-20)/hoehe
                    , (20        )/breite
                    , (20        )/hoehe);
    auto gefundenerTon = std::find_if(tonfolge.rbegin(), tonfolge.rend(), [&suchRect](const Ton& t){ return suchRect.contains(t.x, t.y); }); // hier kann auch die ältere, längere Methode benutzt werden
    if(gefundenerTon == tonfolge.rend())
        return std::numeric_limits<std::size_t>::max();
    return (tonfolge.rend() - gefundenerTon) - 1;
}

// Verschieb das Quadrat mit dem Index »index« an die angegeben Position
void TonfolgeModell::verschiebeTon(std::size_t index, const QPointF& pos)
{
    if(index < tonfolge.size())
    {
        tonfolge[index].x = pos.x();
        tonfolge[index].y = pos.y();
        tonfolgeGeaendert(); // die Daten wurden geändert (Qudarat verschoben), das wird jetzt bekannt gegeben
    }
}

void TonfolgeModell::verschiebeTonRel(std::size_t index, double dx, double dy)
{
    if(index < tonfolge.size()) // ist der übergebene Index gültig
    {
        tonfolge[index].x += dx;
        tonfolge[index].y += dy;
        tonfolgeGeaendert(); // die Daten wurden geändert (Qudarat verschoben), das wird jetzt bekannt gegeben
    }
}

void TonfolgeModell::tonHinzufuegen(const TonfolgeModell::Ton& ton)
{
    //TODO
    //Logik für das einfügen von Tönen

    // alt
    tonfolge.push_back(ton);

    tonfolgeGeaendert(); // die Daten wurden geändert (Qudarat hinzugefügt), das wird jetzt bekannt gegeben
}

void TonfolgeModell::tonEntfernen(std::size_t index)
{
    //TODO
    //Logik für das entfernen von Tönen

    if(index < tonfolge.size()) // ist der übergebene Index gültig
    {
        tonfolge.erase(tonfolge.begin() + index);
        tonfolgeGeaendert(); // die Daten wurden geändert (Qudarat gelöscht), das wird jetzt bekannt gegeben
    }
}
