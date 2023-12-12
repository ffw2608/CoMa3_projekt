//#include "Musiktafel.cpp"
#include "Musiktafel_control.cpp"
#include <QApplication>

/***  Main ***/
/*
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Musiktafel mt ;
    mt.show();

    return app.exec();
}
*/

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Musiktafel_view view;
    view.show();

    Musiktafel_control control;
    control.setView(&view);

    return app.exec();
}
