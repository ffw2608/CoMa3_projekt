#ifndef TONFOLGECONTROLLER_H
#define TONFOLGECONTROLLER_H

#include <QObject>

class QMouseEvent;
class QKeyEvent;

class TonfolgeModell;
class TonfolgeWidget;

class TonfolgeController
    : public QObject
{
    Q_OBJECT

    TonfolgeModell& modell;
    TonfolgeWidget& ansicht;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

    std::size_t aktuellerTon = std::numeric_limits<std::size_t>::max();
    bool aktuellerTonGueltig() const;


public:
    explicit TonfolgeController(TonfolgeModell& modell, TonfolgeWidget& ansicht, QObject* parent = nullptr);
    bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // TONFOLGECONTROLLER_H
