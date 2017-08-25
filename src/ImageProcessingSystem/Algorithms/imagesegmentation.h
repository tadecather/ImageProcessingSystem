#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <QImage>
#include <QVector>
#include <QPolygonF>
#include <QPainterPath>

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
    static QImage * ContourExtraction(QImage *img);
    static QImage * BoundaryTracking(QImage *img);
    static QImage * regionGrowing(QImage *image);
    static QImage * houghTran(QImage & image);
};

#endif // SEGMENTATION_H
