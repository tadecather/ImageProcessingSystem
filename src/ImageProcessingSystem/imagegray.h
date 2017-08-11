#ifndef GREYIMAGE_H
#define GREYIMAGE_H

#include <QImage>

class ImageGray
{
public:
    ImageGray();
    static QImage * colorToGrey(QImage &image);
};

#endif // GREYIMAGE_H
