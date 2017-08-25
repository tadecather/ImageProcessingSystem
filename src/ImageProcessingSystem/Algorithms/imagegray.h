#ifndef GREYIMAGE_H
#define GREYIMAGE_H

#include <QImage>

class ImageGray
{
public:
    ImageGray();
    static QImage * colorToGrey(QImage * image);
    static QImage * GrayToColor(QImage *image);
    static QImage * negetiveImage(QImage *image);
    static QImage * binaryzation(QImage *image, int keyValueType, int keyValue = 127);
    static QImage * linearStretch(QImage *image, double k = 0.3, double d = 0.5);
    static QImage * exponentialStretch(QImage *image, double c = 1, double r = 2);
    static QImage * logarithmicStretch(QImage *image, double v = 50);
    static QImage * plotHistogram(QImage *image);
    static QImage * balanceHistogram(QImage *image);
    static QVector<int> countGrayHistogram(QImage * image);
private:
    static QImage * drawHistogram(QVector<int> grayHist);
    static int getKeyValue(QImage * image);
    static int getKeyValueHist(QImage *image);
};

#endif // GREYIMAGE_H
