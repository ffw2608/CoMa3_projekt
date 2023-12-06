#ifndef MUSIKTAFEL_MODEL_H
#define MUSIKTAFEL_MODEL_H

#include <QObject>
#include <QVector>
#
class Musiktafel_model
    :public QObject
{
    Q_OBJECT

    struct Musiktafel
    {
        QVector<QPointF> punkte;//QVector<QPointF> view_punkte;
        QVector<QLineF> linien;     //QVector<QLineF> linien;

        int _hoehe              = 750   ;
        int _breite             = 1500  ;

        const int _ANZAHLLINIEN = 29    ;
        const int _STARTX       = 10    ;
        const int _PUNKTSIZE    = 10    ;

        int _linienAbstand      = _hoehe/_ANZAHLLINIEN;
        int _punkteAbstand      = _breite/_ANZAHLLINIEN;

        const double dashLen   = 20;
        const double dashSpace = 20;
    };

};



#endif // MUSIKTAFEL_MODEL_H
