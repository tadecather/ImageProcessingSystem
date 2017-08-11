#ifndef GREYIMAGE_H
#define GREYIMAGE_H

#include <QImage>

class GreyImage
{
public:
    GreyImage();
    static QImage * colorToGrey(QImage &image);
};

#endif // GREYIMAGE_H
