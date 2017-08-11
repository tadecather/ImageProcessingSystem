#ifndef GREYIMAGE_H
#define GREYIMAGE_H


class GreyImage
{
public:
    GreyImage();
    static QImage * colorToGrey(QImage &image);
};

#endif // GREYIMAGE_H
