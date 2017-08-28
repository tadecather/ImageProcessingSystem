#ifndef IMAGEENHANCEMENT_H
#define IMAGEENHANCEMENT_H

#include <QImage>
#include <iostream>
#include <time.h>
#include <qDebug>
#include <algorithm>
#include <QMessageBox>
#include <qmath.h>
#include "imagtranslate.h"


class ImageSegmentation;
class ImageEnhancement
{
public:
    ImageEnhancement();
    static void AddGaussianNoise(QImage* image, double mu, double sigma, int k);
    static void AddSaltPepperNoise(QImage* image, double snr);
    static QImage* MeanSmoothing(QImage* image, int size);
    static QImage* MedianSmoothing(QImage* image, int size);
    static QImage* GaussianSmoothing(QImage* image, int size, int theta);
    static QImage* SelectiveMaskSmoothing(QImage* image);
    static QImage* GradientSharpening(QImage* image, int operatorNo, double multiplier);
    static QImage* LaplacianSharpening(QImage* image, double multiplier);
    static double ImageQualityAssessment(QImage* ref, QImage* img);
private:
    static double GenerateGaussianNoise(double mu, double sigma);
    static double V1, V2, S;
    static int phase;
};

#endif // IMAGEENHANCEMENT_H
