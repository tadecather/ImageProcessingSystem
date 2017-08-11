#include "imagtranslate.h"

ImagTranslate::ImagTranslate()
{

}

QList<QRgb> ImagTranslate::ImageToList(const QImage &image,  int &width, int &height)
{
    width = image->width();
    height = image->height();
    QList<QRgb> imgRGBList = new QList<QRgb>;
    // 通过遍历得到各个点的 RGB 值
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            QRgb pixel = img->pixel(i,j);
            int Red = qRed(pixel);
            int Green = qGreen(pixel);
            int Blue = qBlue(pixel);
            QRgb rgbPixel = qRgb(Red, Green, Blue);
            imgRGBList.append(rgbPixel);
        }
    }
    return imgRGBList;

}

QImage *ImagTranslate::ImageToList(QList<QRgb> rgbList, int width, int height)
{
    QImage * image = new Image(width, height,  QImage::Format_ARGB32);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            image->setPixel(i, j, rgbList[i * width + j]);
        }
    return image;
}
