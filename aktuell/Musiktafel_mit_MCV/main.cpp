#include "musiktafelfenster.h"
#include <QApplication>

/***  Main ***/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MusiktafelFenster mtf;
    mtf.show();
    return app.exec();
}

