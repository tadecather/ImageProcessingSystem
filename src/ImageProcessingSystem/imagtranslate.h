#ifndef IMAGTRANSLATE_H
#define IMAGTRANSLATE_H

#include <QWidget>

class ImagTranslate
{
public:
    ImagTranslate();

    static QList<QRgb> ImageToList(const QImage &image, int &width, int &height);
    static QImage * ImageToList(const QImage &image, int &width, int &height);
};

#endif // IMAGTRANSLATE_H
