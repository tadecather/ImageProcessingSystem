#ifndef GREYIMAGE_H
#define GREYIMAGE_H

#include <QImage>
#include "mainwindow.h"

class ImageGray
{
public:
    ImageGray();
    static QImage * colorToGrey(QImage &image);
    static QImage * GrayToColor(QImage &image);
    static QImage * negetiveImage(QImage &image);
    static QImage * binaryzation(QImage &image);
    static QImage * linearStretch(QImage &image);
    static QImage * exponentialStretch(QImage &image);
    static QImage * logarithmicStretch(QImage &image);
    static QImage * plotHistogram(QImage &image);
    static QImage * balanceHistogram(QImage &image);
private:
    static QVector<int> countGrayHistogram(QImage * image);
    static QImage * drawHistogram(QVector<int> grayHist);
};

#endif // GREYIMAGE_H
