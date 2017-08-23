#ifndef IMAGTRANSLATE_H
#define IMAGTRANSLATE_H

#include <QWidget>
using namespace std;
class ImagTranslate
{
public:
    ImagTranslate();

    static QList<QRgb> * imageToList(const QImage &image, int & width, int & height);
    static QImage * listToImage(QList<QRgb> rgbList , int width, int height);
    static void vector2GreyImage( vector<vector<float> > &result, QImage & img);
    static void greyImage2Vector(QImage & img,vector<vector<float> > &result);
    static void vector2ColorImage( vector<vector<float> > &resultR,vector<vector<float> > &resultG,vector<vector<float> > &resultB, QImage & img);
    static void colorImage2Vector(QImage & img,vector<vector<float> > &resultR,vector<vector<float> > &resultG,vector<vector<float> > &resultB);
};

#endif // IMAGTRANSLATE_H
