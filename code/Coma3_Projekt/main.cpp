#include "Musiktafel_control.h"
#include <QApplication>

/***  Main ***/
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Musiktafel_view view;
    view.show();

    Musiktafel_model model;

    Musiktafel_control control;
    control.setView(&view);
    control.getModel(&model);
    return app.exec();
}
