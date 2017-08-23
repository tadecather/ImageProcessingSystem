#include "graycommand.h"

Color2GrayCommand::Color2GrayCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index)
{
    name = new QString("灰度化");

    this->imageLeft = new QImage(*imageLeft);
    //this->imageRight = imageRight;
    if(imageRight == NULL)
    {
        this->imageRight = NULL;
        this->imageAfter = new QImage(*imageLeft);
    }
    else
    {
        this->imageRight = new QImage(*imageRight);
        this->imageAfter = new QImage(*imageRight);
    }
    this->mainTab = mainTab;
    this->index = index;
}

void Color2GrayCommand::redo()
{
    if(this->imageRight == NULL)
    {
        ImageGray::colorToGrey(*imageAfter);
        mainTab->setImage(index, 1, imageAfter);
    }
    else
    {
        ImageGray::colorToGrey(*imageAfter);
        mainTab->setImage(index, 0, imageRight);
        mainTab->setImage(index, 1, imageAfter);
    }

}

void Color2GrayCommand::undo()
{
    if(this->imageRight == NULL)
    {
        mainTab->setImage(index, 0, imageLeft);
        mainTab->setImage(index, 1, NULL);
    }
    else
    {
        mainTab->setImage(index, 0, imageLeft);
        mainTab->setImage(index, 1, imageRight);
    }
}

//现在用不到的方法
QImage * Color2GrayCommand::color2Gray(QImage * img)
{

            int height = img->height();
            int width = img->width();
            // QImage ret(width, height, QImage::Format_Indexed8)创建Indexed8格式的Image用于接收处理后的图像
            QImage * ret =new QImage(width, height, QImage::Format_Indexed8);
            ret->setColorCount(256);

            for(int i = 0; i < 256; i++)
            {
                ret->setColor(i, qRgb(i, i, i));
            }
            switch(img->format())
            {
            case QImage::Format_Indexed8:
                for(int i = 0; i < height; i ++)
                {
                    const uchar *pSrc = (uchar *)img->constScanLine(i);
                    uchar *pDest = (uchar *)ret->scanLine(i);
                    memcpy(pDest, pSrc, width);
                }
                break;
            case QImage::Format_RGB32:
            case QImage::Format_ARGB32:
            case QImage::Format_ARGB32_Premultiplied:
                for(int i = 0; i < height; i ++)
                {
                    const QRgb *pSrc = (QRgb *)img->constScanLine(i);
                    uchar *pDest = (uchar *)ret->scanLine(i);

                    for( int j = 0; j < width; j ++)
                    {
                        pDest[j] = qGray(pSrc[j]);
                    }
                }
                break;
            default:
                break;
            }

            return ret;
}
