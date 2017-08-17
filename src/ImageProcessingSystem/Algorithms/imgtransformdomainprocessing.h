#ifndef IMGTRANSFORMDOMAINPROCESSING_H
#define IMGTRANSFORMDOMAINPROCESSING_H
#include "mainwindow.h"

class imgTransformdomainprocessing
{
public:
    imgTransformdomainprocessing();
    static QImage * imgSetValidPic(const QImage & img);
    static QImage * imgHaarWaveletTransform(const QImage & img);
    static void imgHaarWaveletTransformInversion(QImage *img);
    static void imgCopy(const QImage & src,QImage & newImg);
};

#endif // IMGTRANSFORMDOMAINPROCESSING_H
