#ifndef TONFOLGEWIDGET_H
#define TONFOLGEWIDGET_H

#include<vector>
#include<limits>

#include<QWidget>

class TonfolgeModell;

class TonfolgeWidget
    : public QWidget
{
    Q_OBJECT
    const TonfolgeModell& modell;
public:
    TonfolgeWidget(const TonfolgeModell& modell, QWidget* parent = nullptr);

protected:
    // von den Events verbleibt nur das paintEvent, alle anderen werden durch den EventFilter direkt von der Steuerung (QuadrateContoller) behandelt
    void paintEvent(QPaintEvent* event) override;

public:
};

#endif // TONFOLGEWIDGET_H
