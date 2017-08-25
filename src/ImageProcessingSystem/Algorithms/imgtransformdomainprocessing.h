#ifndef IMGTRANSFORMDOMAINPROCESSING_H
#define IMGTRANSFORMDOMAINPROCESSING_H
#include "imagtranslate.h"
class imgTransformdomainprocessing
{
public:
    imgTransformdomainprocessing();
    static QImage * imgSetValidPic(QImage * img);

    //这里必须返回新的QImage，因为需要对原图像进行添加像素操作
    static void imgCopy(const QImage & src,QImage & newImg);
    static void imgSetWHFCoefficientZero(QImage *img,int & count);
    static void imgHardThreshold(QImage *img,int & count,int lambda);
    static void imgSoftThreshold(QImage *img,int & count,int lambda);
    static QImage* imgHaar(QImage * img,int times,int &count);
    static void imgHaarInversion(QImage * img,int &count);
private:
    static void haarWaveletTransform(vector<vector<float> > &tmp);
    static void haarWaveletTransformInversion(vector<vector<float> > &tmp);

};

#endif // IMGTRANSFORMDOMAINPROCESSING_H
