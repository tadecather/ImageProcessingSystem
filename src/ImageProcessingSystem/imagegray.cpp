#include "imagegray.h"
#include "imagtranslate.h"

#include "fileoperation.h"
#include <QDebug>

ImageGray::ImageGray()
{

}


//传入一个 QImage 对象，返回一个 QImage 指针
QImage * ImageGray::colorToGrey(QImage &image)
{
    int width = 0;
    int height = 0;
    //得到一个从左到右，从上到下遍历的RGB像素点QList
    QList<QRgb> * rgbList =  ImagTranslate::imageToList(image, width, height);
    image.convertToFormat(QImage::Format_ARGB32);
    // 循环遍历QList 进行像素点的操作，然后对Image 对象进行逐个像素点的赋值
    for(int i = 0; i < width * height; i++){
        QRgb pixel = rgbList->at(i);
        int Red = qRed(pixel);
        int Green = qGreen(pixel);
        int Blue = qBlue(pixel);
        int Grey = 0.3 * Red + 0.59 * Green + 0.11 * Blue;
        QRgb newPixel = qRgb(Grey, Grey, Grey);
        // i % width 得到目前像素点的列值，i /width 得到当前像素点的 行值
        image.setPixel(i % width , i / width, newPixel);
    }
    delete rgbList;
    return &image;
}
