#ifndef DCT_H
#define DCT_H

#include <QImage>

class DCT
{
public:
   static QImage * dctImage(QImage & image);

   static QImage * dctNewImage(QImage &image);

   static QImage * dctIImage(QImage & image);

   static QImage * dctINewImage(QImage &image);
   static QImage * dctINewImage(QVector<QVector<QVector <double>>> dctData);

   static QVector<QVector<double>> getGrayImageMatrix(QImage &image);

   static QVector<QVector<double>>getTranslateMatrix(int n);

   static QVector<QVector<double> >  mulityMatrix(QVector<QVector<double>> matrix1, QVector<QVector<double>> matrix2);

   static QVector<QVector<double> > matrixTranslate(QVector<QVector<double> >);

   static QVector<QVector<QVector <double>>> getDivodedImage(QVector<QVector<double>> grayImage, int n);
};

#endif // DCT_H
