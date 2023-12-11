#include"musiktafelfenster.h"

#include"tonfolgewidget.h"
#include"tonfolgemodell.h"
#include"tonfolgecontroller.h"


#include<QWidget>
#include<QVBoxLayout>
#include<QPushButton>
#include<QCoreApplication>
#include<QCloseEvent>

MusiktafelFenster::MusiktafelFenster(QWidget *parent)
    : QWidget(parent)
{
    resize(750,750);

    //TODO//Menuwidget* menuwidget     = new Menuwidget;
    //TODO//Musiktafelwidget* tafelwidget   = new Tafelwidget;

    tonfolgeModell                         = new TonfolgeModell(this);
    TonfolgeWidget * tonfolgeAnsicht       = new TonfolgeWidget(*tonfolgeModell);
    /*TonfolgeController* tonController = */ new TonfolgeController(*tonfolgeModell, *tonfolgeAnsicht, this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    //TODO//layout->addWidget(menuwidget);
    layout->addWidget(tonfolgeAnsicht);
    //TODO//layout->addWidget(farbwahlwidget);

}

MusiktafelFenster::~MusiktafelFenster()
{
}

void MusiktafelFenster::ansichtErstellen()
{
    TonfolgeWidget* widget = new TonfolgeWidget(*tonfolgeModell);
    widget->setAttribute(Qt::WA_DeleteOnClose, true);
    widget->resize(200,200);
    widget->show();
}

void MusiktafelFenster::closeEvent(QCloseEvent* event)
{
    QWidget::closeEvent(event);
    if(event->isAccepted())
        QCoreApplication::quit(); // das Programm beenden, wenn das Hauptfenster geschlossen wird
}
