#include "graycommand.h"

//GrayCommand::GrayCommand()
//{

//}
QImage * GrayCommand::color2Gray(QImage & img)
{

            int height = img.height();
            int width = img.width();
            // QImage ret(width, height, QImage::Format_Indexed8)创建Indexed8格式的Image用于接收处理后的图像
            QImage * ret =new QImage(width, height, QImage::Format_Indexed8);
            ret->setColorCount(256);

            for(int i = 0; i < 256; i++)
            {
                ret->setColor(i, qRgb(i, i, i));
            }
            switch(img.format())
            {
            case QImage::Format_Indexed8:
                for(int i = 0; i < height; i ++)
                {
                    const uchar *pSrc = (uchar *)img.constScanLine(i);
                    uchar *pDest = (uchar *)ret->scanLine(i);
                    memcpy(pDest, pSrc, width);
                }
                break;
            case QImage::Format_RGB32:
            case QImage::Format_ARGB32:
            case QImage::Format_ARGB32_Premultiplied:
                for(int i = 0; i < height; i ++)
                {
                    const QRgb *pSrc = (QRgb *)img.constScanLine(i);
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
