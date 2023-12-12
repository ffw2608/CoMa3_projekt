#ifndef MUSIKTAFELFENSTER_H
#define MUSIKTAFELFENSTER_H

#include <QWidget>

class TonfolgeModell;

class MusiktafelFenster: public QWidget
{
    Q_OBJECT

    TonfolgeModell* tonfolgeModell;

public:
    MusiktafelFenster(QWidget *parent = nullptr);
    ~MusiktafelFenster();

public slots:
    void ansichtErstellen();// TODO
    // hier slots füllen

protected:
    void closeEvent(QCloseEvent* event) override;
};

#endif // MUSIKTAFELFENSTER_H
