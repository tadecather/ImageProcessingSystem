#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <QImage>
#include <QVector>

class ImageSegmentation
{
public:
    static QImage * ostu(QImage &image);
    static QImage * RobertOperator(QImage *img);
    static QImage * SobelOperator(QImage *img);
    static QImage * PrewittOperator(QImage *img);
    static QImage * LaplacianOperator(QImage *img);
    static QImage * GaussLaplacianOperator(QImage *img);
    static QImage * KrischOperator(QImage *img);

    static QImage * houghTran(QImage & image);
};

#endif // SEGMENTATION_H
