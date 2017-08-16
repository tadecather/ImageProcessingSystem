#ifndef IMAGEENHANCEMENT_H
#define IMAGEENHANCEMENT_H

#include <QImage>
#include <time.h>
#include <qDebug>
#include "imagtranslate.h"

class ImageEnhancement
{
public:
    ImageEnhancement();
    static void AddGaussianNoise(QImage* image, double mu, double sigma, int k);
private:
    static double GenerateGaussianNoise(double mu, double sigma);
    static double V1, V2, S;
    static int phase;
};

#endif // IMAGEENHANCEMENT_H
