#ifndef IMAGETRANS_H
#define IMAGETRANS_H

#include <QImage>


#include "mainwindow.h"

class imagetrans
{
public:
    imagetrans();
    //顺时针90
    static QImage * imgClockwiseRotate90(QImage & img);
    static QImage * imgAnticlockwiseRotate90(const QImage &img);
    static QImage * imgHorizontalInversion(const QImage & img);
    static QImage * imgVerticalInversion(const QImage & img);
    static QImage * imgTranspose(const QImage &img);
};

#endif // IMAGETRANS_H
