#define _USE_MATH_DEFINES
#include "tonfolgewidget.h"
#include "tonfolgemodell.h"

#include<cmath>

#include<QPaintEvent>
#include<QPainter>

#include<QRectF>
#include<QMouseEvent>

#include<QDebug>

TonfolgeWidget::TonfolgeWidget(const TonfolgeModell& modell, QWidget* parent)
    : QWidget(parent)
    , modell(modell)
{
    setFocusPolicy(Qt::StrongFocus);

    connect(&modell, &TonfolgeModell::tonfolgeGeaendert, this, QOverload<>::of(&TonfolgeWidget::update));
}

// Bekannte Zeichenfunktion
void TonfolgeWidget::paintEvent(QPaintEvent* /*event*/)
{
    const double breite     = width();
    const double hoehe      = height();
    const double punktSize  = 20;

    QPainter painter(this);

    for(const TonfolgeModell::Ton& ton : modell.getTonfolge()) // statt des direkten Zugriffs erfolgt hier jetzt eine Nachfrage beim Modell, dieses liefert die aktuelle Quadrateliste
    {
        /*/
        painter.setBrush(QBrush(ton.farbe));
        painter.drawRect(static_cast<int>(ton.x*breite)
                   , static_cast<int>(ton.y*hoehe )
                   , 20
                   , 20);
        //*/
        //*/
        //painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(ton.farbe));
        painter.drawEllipse(static_cast<int>(ton.x*breite)
                           ,static_cast<int>(ton.y*hoehe)
                           ,punktSize
                           ,punktSize);
        //*/
    }
}
