#include "Musiktafel.cpp"

/***  Main ***/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Musiktafel mt ;
    mt.show();

    return app.exec();
}
