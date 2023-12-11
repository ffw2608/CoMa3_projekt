#ifndef TONFOLGEMODELL_H
#define TONFOLGEMODELL_H

#include<QObject>
#include<QColor>

class TonfolgeModell: public QObject
{
    Q_OBJECT
public:
    // der parent dient wie immer in Qt der automatischen Speicherbereinigung durch Qt
    TonfolgeModell(QObject* parent);

    // Struktur/Klasse für die Daten eines Tons
    // hier public, da auf diese Datenstruktur von der Ansicht aus zugegriffen wird
    struct Ton
    {
        Ton(double x, double y, const QColor& farbe)
            : x(x)
            , y(y)
            , farbe(farbe)
        {}
        double x;
        double y;
        QColor farbe;
    };

    // Tonfolge-Vektor als konstante (unveränderliche) Referenz rausgeben (wird hier von der Ansicht zum zeichnen benutzt)
    const std::vector<Ton>& getTonfolge() const { return tonfolge; }

    std::size_t findeTon(const QPoint& pos, const QSize& widgetgroese) const;
    void verschiebeTon(std::size_t index, const QPointF& pos);
    void verschiebeTonRel(std::size_t index, double dx, double dy);
    void tonHinzufuegen(const Ton& quad);
    void tonEntfernen(std::size_t index);

    std::size_t laengeTonfolge() const          { return tonfolge.size(); }

private:
    // Die Struktur Ton ist zwar Public, die Daten bleiben aber privat (Klassenkapslung) -> Es kann kontroliert werden, was mit den Daten passiert und wer darauf zugreifen darf
    std::vector<Ton> tonfolge;

signals:
    void tonfolgeGeaendert(); // Dieses Signal wird immer dann gesendet (durch einen Funktionsaufruf in der Klasse), wenn sich die Daten geändert haben
    // dies kann sicher bestimmt werden, da die Daten privat, also gekapselt sind. Ein schreibener Zugriff erfolgt also ausschließlich durch die Methoden.
};


#endif // TONFOLGEMODELL_H
