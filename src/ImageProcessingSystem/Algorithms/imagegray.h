#ifndef GREYIMAGE_H
#define GREYIMAGE_H

#include <QImage>

class ImageGray
{
public:
    ImageGray();
    static QImage * colorToGrey(QImage &image);
    static QImage * GrayToColor(QImage &image);
    static QImage * negetiveImage(QImage &image);
    static QImage * binaryzation(QImage &image, int keyValue = 127);
    static QImage * linearStretch(QImage &image);
    static QImage * exponentialStretch(QImage &image);
    static QImage * logarithmicStretch(QImage &image);
    static QImage * plotHistogram(QImage &image);
    static QImage * balanceHistogram(QImage &image);
    static QVector<int> countGrayHistogram(QImage * image);
private:
    static QImage * drawHistogram(QVector<int> grayHist);
    static int getKeyValue(QImage * image);
    static int getKeyValueHist(QImage *image);
};

#endif // GREYIMAGE_H
