#include "greyimage.h"
#include "imagtranslate.h"

GreyImage::GreyImage()
{

}

QImage * GreyImage::colorToGrey(QImage &image)
{
    int width;
    int height;
    QList<QRgb> * rgbList =  ImagTranslate::imageToList(image, width, height);
    QImage * image = new QImage(width, height,  QImage::Format_ARGB32);
    for(int i = 0; i < width; i++){
        QRgb pixel = QList[i];
        int Red = qRed(pixel);
        int Green = qGreen(pixel);
        int Blue = qBlue(pixel);

        int Grey = 0.3 * Red + 0.59 * Green + 0.11 * Blue;
        QRgb newPixel = new QRgb(Grey, Grey, Grey);
        image->setPixel(i / width, i % height, newPixel);
    }
    return image;
}
