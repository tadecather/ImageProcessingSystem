#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <QImage>
#include <QVector>
#include <QSize>
#include <QPolygonF>
#include <QPainterPath>

using namespace std;


class ImageEnhancement;
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
    static QImage * CustomEdge(QImage *img, int *selfTemplate);
    static QImage * ContourExtraction(QImage *img, int size, int t, int Ostu, float rat =0.5);
    static void TraceEdge(int y, int x, float nThrLow, vector<vector<float>> &res, vector<vector<float>> &pMag, QSize *sz);
    static QImage * BoundaryTracking(QImage *img);
    static QImage * regionGrowing(QImage *image);
    static QImage * houghTran(QImage & image);
};

#endif // SEGMENTATION_H
