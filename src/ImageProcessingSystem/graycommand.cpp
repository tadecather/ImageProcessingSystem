#include "graycommand.h"

//GrayCommand::GrayCommand()
//{

//}

//初始化一个GrayCommand
GrayCommand::GrayCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index)
{
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

void GrayCommand::redo()
{
    //处理
    //imageAfter = 拷贝构造 算法类：：灰度化算法(imageRight)
    if(this->imageRight == NULL)
    {
        //处理左，结果放到右
        //静态算法处理imageAfter
        mainTab->setImage(index, 1, imageAfter);
    }
    else
    {
        //静态算法处理imageAfter
        mainTab->setImage(index, 0, imageRight);
        mainTab->setImage(index, 1, imageAfter);
    }

}

void GrayCommand::undo()
{
    QMessageBox::about(NULL, "About", "About this application");
        mainTab->setImage(index, 0, imageLeft);
        mainTab->setImage(index, 1, NULL);
}

QImage * GrayCommand::color2Gray(QImage * img)
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
