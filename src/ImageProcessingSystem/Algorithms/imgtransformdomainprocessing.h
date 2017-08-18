#ifndef IMGTRANSFORMDOMAINPROCESSING_H
#define IMGTRANSFORMDOMAINPROCESSING_H
#include "mainwindow.h"

class imgTransformdomainprocessing
{
public:
    imgTransformdomainprocessing();
    static QImage * imgSetValidPic(const QImage & img);
    static QImage * imgHaarWaveletTransform(const QImage & img, int & count);
    static void imgHaarWaveletTransformInversion(QImage *img,int & count);
    //这里必须返回新的QImage，因为需要对原图像进行添加像素操作
    static void imgCopy(const QImage & src,QImage & newImg);
    static void imgSetWHFCoefficientZero(QImage *img,int & count);
    static void imgHardThreshold(QImage *img,int & count,int lambda);
    static void imgSoftThreshold(QImage *img,int & count,int lambda);

};

#endif // IMGTRANSFORMDOMAINPROCESSING_H
