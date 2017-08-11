#include "imagtranslate.h"

ImagTranslate::ImagTranslate()
{

}

// 将图片转化为一个 QList 数组，需要参数为一个转化图片的 QImage 指针，以及两个int 类型的指针，
 // return 一个QList<QRgb>* ，同时会改传进来的两个int ，用作返回图片原本的 宽 和 高
QList<QRgb> * ImagTranslate::imageToList(const QImage &image,  int &width, int &height)
{
    width = image.width();
    height = image.height();
    QList<QRgb> *imgRGBList = new QList<QRgb>();
    // 通过遍历得到各个点的 RGB 值
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            QRgb pixel = image.pixel(i,j);
            int Red = qRed(pixel);
            int Green = qGreen(pixel);
            int Blue = qBlue(pixel);
            QRgb rgbPixel = qRgb(Red, Green, Blue);
            imgRGBList->append(rgbPixel);
        }
    }
    return imgRGBList;

}


//将一个 QList<QRgb> ，转化为一个给定宽和高的图片
// 返回一个 QImage *
QImage * ImagTranslate::listToImage(QList<QRgb> rgbList, int width, int height)
{
    QImage * image = new QImage(width, height,  QImage::Format_ARGB32);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            image->setPixel(i, j, rgbList[i * width + j]);
        }
    }
    return image;
}
