#include "imagetrans.h"

#include<QColor>
imagetrans::imagetrans()
{

}

QImage *imagetrans::imgClockwiseRotate90(QImage &img)
{
    QImage * newimg = new QImage(img.height(),img.width(),img.format());

    //这里声明起始的宽是为了代码的可读性
    int newWidth  = newimg->width(),
        newHeight = newimg->height(),
        oriHeight = img.height();

    for(int i =0;i<newHeight;++i)
    {
        //每次循环添加一行
        for(int j=0;j<newWidth;++j)
        {
            //每次循环对新图像的每一行的每一个点操作
            QRgb newPix = img.pixel(i,oriHeight-j-1);
            newimg->setPixel(j,i,newPix);
        }
    }
    return newimg;
}

QImage *imagetrans::imgAnticlockwiseRotate90(const QImage &img)
{
    QImage * newimg = new QImage(img.height(),img.width(),img.format());
    int  newHeight = newimg->height(),
         newWidth = newimg->width();
    for(int i=0;i<newWidth;i++)
    {
        QRgb * line    = (QRgb *) img.scanLine(i);
        for(int j=0;j<newHeight;j++){
            newimg->setPixel(i,newHeight-j-1,line[j]);
        }
    }
     return newimg;
}

//水平镜像翻转
QImage *imagetrans::imgHorizontalInversion(const QImage &img)
{
    QImage * newimg = new QImage(img);
    int newWidth  = newimg->width(),
        newHeight = newimg->height();
    for(int i =0;i<newHeight;++i)
    {
        QRgb * newline = (QRgb *) newimg->scanLine(i);
        QRgb * end = newline + newWidth - 1;
        QRgb tmp;
        for(int j=0;2*j<newWidth;++j)
        {
            tmp = *(newline+j);
            *(newline+j) = *(end-j);
            *(end-j)= tmp;
        }
    }
    return newimg;
}

QImage *imagetrans::imgVerticalInversion(const QImage &img)
{
    QImage * newimg =new QImage(img);
    int  newHeight = newimg->height();
//         newWidth = newimg->width();
//    int bytecount = img.bytesPerLine();
    for(int i =0;i<newHeight;i++)
    {

        QRgb * line    = (QRgb *) img.scanLine(i);
        QRgb * newline = (QRgb *) newimg->scanLine(newHeight-i-1);
//        QRgb tmp;
        qDebug("%p",newline);
        memcpy(newline,line,img.bytesPerLine());
//        for(int j =0;4*j<bytecount;j++)
//        {
//            tmp=*(line++);
//            *(line)=*(newline++);
//            *(newline) = tmp;
//        }
    }
    return newimg;

}

QImage *imagetrans::imgTranspose(const QImage &img)
{
     QImage * newimg = new QImage(img.height(),img.width(),img.format());
     int  newHeight = newimg->height(),
          newWidth = newimg->width();
     for(int i=0;i<newWidth;i++)
     {
         QRgb * line = (QRgb *) img.scanLine(i);
         for(int j=0;j<newHeight;j++){
             newimg->setPixel(i,j,line[j]);
         }
     }
      return newimg;
}
