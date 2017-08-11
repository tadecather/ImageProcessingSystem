#ifndef IMAGTRANSLATE_H
#define IMAGTRANSLATE_H

#include <QWidget>

class ImagTranslate
{
public:
    ImagTranslate();

    static QList<QRgb> * imageToList(const QImage &image, int &width, int &height);
    static QImage * listToImage(QList<QRgb> rgbList , int width, int height);
};

#endif // IMAGTRANSLATE_H
