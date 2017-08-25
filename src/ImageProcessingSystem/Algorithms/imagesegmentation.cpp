﻿#include "imagesegmentation.h"


#include "imagegray.h"

using namespace std;
// 大津阈值获取
QImage * ImageSegmentation::ostu(QImage &image)
{
    // 方差最大时说明图片的前后背景色的划分为最合适
    QVector<int> grayHist = ImageGray::countGrayHistogram(&image);

    int N = image.width() * image.height(); //图片总的像素点
    int N0 = 0; // 背景色所占的像素的总数
    int N1 = 0; // 前景色所占的像素的总数
    int max = 0; // 最大方差所取时的灰度值
    double gMax = 0; // 最大方差

    for(int i = 0; i < 256; i++){

        N0 += grayHist[i];
        N1 = N - N0;

        if(N1 == 0){
            break;
        }

        double w0 = N0 * 1.0 / N;
        double w1 = 1 - w0;

        int sum = 0;
        for(int m = 0; m <= i; m++){
            sum += m * grayHist[i];
        }
        double u0 = sum * 1.0 / N0;

        sum = 0;
        for( int n = i + 1; n < 256; n++){
            sum += n * grayHist[i];
        }
        double u1 = sum * 1.0 / N1;

        double g = w0*w1*(u0-u1)*(u0-u1);

        if(g > gMax){
            gMax = g;
            max = i;
        }

    }

    QImage * newImage = ImageGray::binaryzation(image, max);

    return newImage;

}


//所有算子对阈值是否应该有个判断
QImage *ImageSegmentation::RobertOperator(QImage *img)
{
    QImage * newImg = new QImage(*img);
    int newHeight = newImg->height(),
            newWidth = newImg->width();
//读取图像中的像素灰度存入两层vector构成的矩阵
    vector<vector<float>> tmpR;
    vector<vector<float>> tmpG;
    vector<vector<float>> tmpB;
    ImagTranslate::colorImage2Vector(*img,tmpR,tmpG,tmpB);
    for(int i = 0;i < newHeight-1;++i)
    {
        for(int j =0;j< newWidth-1;++j)
        {
            tmpR[i][j] = abs(tmpR[i][j]-tmpR[i+1][j+1])+abs(tmpR[i+1][j]-tmpR[i][j+1]);
            tmpR[i][j] = tmpR[i][j]>255?255:tmpR[i][j];
            tmpG[i][j] = abs(tmpG[i][j]-tmpG[i+1][j+1])+abs(tmpG[i+1][j]-tmpG[i][j+1]);
            tmpG[i][j] = tmpG[i][j]>255?255:tmpG[i][j];
            tmpB[i][j] = abs(tmpB[i][j]-tmpB[i+1][j+1])+abs(tmpB[i+1][j]-tmpB[i][j+1]);
            tmpB[i][j] = tmpB[i][j]>255?255:tmpB[i][j];
        }
    }
    //转回图像
    ImagTranslate::vector2ColorImage(tmpR,tmpG,tmpB,*newImg);
    return newImg;

}



QImage *ImageSegmentation::SobelOperator(QImage *img)
{
    QImage * newImg = new QImage(*img);
    int newHeight = newImg->height(),
            newWidth = newImg->width();
    vector<vector<float>> tmpR;
    vector<vector<float>> tmpG;
    vector<vector<float>> tmpB;
    ImagTranslate::colorImage2Vector(*img,tmpR,tmpG,tmpB);
    vector<vector<float>> resultR = tmpR;
    vector<vector<float>> resultG = tmpG;
    vector<vector<float>> resultB = tmpB;
    float resultRX,resultRY;
    float resultGX,resultGY;
    float resultBX,resultBY;
    for(int i = 1;i < newHeight-1;++i)
    {
        for(int j =1;j< newWidth-1;++j)
        {
            resultRX      = tmpR[i-1][j+1] + 2*tmpR[i][j+1] + tmpR[i+1][j+1]-(tmpR[i-1][j-1] + 2*tmpR[i][j-1] + tmpR[i+1][j-1]);
            resultRY      = tmpR[i+1][j+1] + 2*tmpR[i+1][j] + tmpR[i+1][j-1]-(tmpR[i-1][j+1] + 2*tmpR[i-1][j] + tmpR[i-1][j-1]);
            resultR[i][j] = sqrt( resultRX* resultRX+ resultRY* resultRY);
            resultR[i][j] = resultR[i][j]>255?255:resultR[i][j];
            resultGX      = tmpG[i-1][j+1] + 2*tmpG[i][j+1] + tmpG[i+1][j+1]-(tmpG[i-1][j-1] + 2*tmpG[i][j-1] + tmpG[i+1][j-1]);
            resultGY      = tmpG[i+1][j+1] + 2*tmpG[i+1][j] + tmpG[i+1][j-1]-(tmpG[i-1][j+1] + 2*tmpG[i-1][j] + tmpG[i-1][j-1]);
            resultG[i][j] = sqrt( resultGX* resultGX+ resultGY* resultGY);
            resultG[i][j] = resultG[i][j]>255?255:resultG[i][j];
            resultBX      = tmpB[i-1][j+1] + 2*tmpB[i][j+1] + tmpB[i+1][j+1]-(tmpB[i-1][j-1] + 2*tmpB[i][j-1] + tmpB[i+1][j-1]);
            resultBY      = tmpB[i+1][j+1] + 2*tmpB[i+1][j] + tmpB[i+1][j-1]-(tmpB[i-1][j+1] + 2*tmpB[i-1][j] + tmpB[i-1][j-1]);
            resultB[i][j] = sqrt( resultBX* resultBX+ resultBY* resultBY);
            resultB[i][j] = resultB[i][j]>255?255:resultB[i][j];
        }
    }
    //转回图像
    ImagTranslate::vector2ColorImage(resultR,resultG,resultB,*newImg);
    return newImg;
}

QImage *ImageSegmentation::PrewittOperator(QImage *img)
{

    QImage * newImg = new QImage(*img);
    int newHeight = newImg->height(),
            newWidth = newImg->width();
    vector<vector<float>> tmpR;
    vector<vector<float>> tmpG;
    vector<vector<float>> tmpB;
    ImagTranslate::colorImage2Vector(*img,tmpR,tmpG,tmpB);
    vector<vector<float>> resultR = tmpR;
    vector<vector<float>> resultG = tmpG;
    vector<vector<float>> resultB = tmpB;
    float resultRX,resultRY;
    float resultGX,resultGY;
    float resultBX,resultBY;
    for(int i = 1;i < newHeight-1;++i)
    {
        for(int j =1;j< newWidth-1;++j)
        {
            resultRX      = tmpR[i-1][j+1] + tmpR[i][j+1] + tmpR[i+1][j+1]-(tmpR[i-1][j-1] + tmpR[i][j-1] + tmpR[i+1][j-1]);
            resultRY      = tmpR[i+1][j+1] + tmpR[i+1][j] + tmpR[i+1][j-1]-(tmpR[i-1][j+1] + tmpR[i-1][j] + tmpR[i-1][j-1]);
            resultR[i][j] = sqrt( resultRX* resultRX+ resultRY* resultRY);
            resultR[i][j] = resultR[i][j]>255?255:resultR[i][j];
            resultGX      = tmpG[i-1][j+1] + tmpG[i][j+1] + tmpG[i+1][j+1]-(tmpG[i-1][j-1] + tmpG[i][j-1] + tmpG[i+1][j-1]);
            resultGY      = tmpG[i+1][j+1] + tmpG[i+1][j] + tmpG[i+1][j-1]-(tmpG[i-1][j+1] + tmpG[i-1][j] + tmpG[i-1][j-1]);
            resultG[i][j] = sqrt( resultGX* resultGX+ resultGY* resultGY);
            resultG[i][j] = resultG[i][j]>255?255:resultG[i][j];
            resultBX      = tmpB[i-1][j+1] + tmpB[i][j+1] + tmpB[i+1][j+1]-(tmpB[i-1][j-1] + tmpB[i][j-1] + tmpB[i+1][j-1]);
            resultBY      = tmpB[i+1][j+1] + tmpB[i+1][j] + tmpB[i+1][j-1]-(tmpB[i-1][j+1] + tmpB[i-1][j] + tmpB[i-1][j-1]);
            resultB[i][j] = sqrt( resultBX* resultBX+ resultBY* resultBY);
            resultB[i][j] = resultB[i][j]>255?255:resultB[i][j];
        }
    }
    //转回图像
     ImagTranslate::vector2ColorImage(resultR,resultG,resultB,*newImg);
    return newImg;
}



//    Laplace算子对孤立象素的响应要比对边缘或线的响应要更强烈，因此只适用于无噪声图象。存在噪声情况下，使用Laplacian算子检测边缘之前需要先进行低通滤波
QImage *ImageSegmentation::LaplacianOperator(QImage *img)
{
    QImage * newImg = new QImage(*img);
    int newHeight = newImg->height(),
            newWidth = newImg->width();
    vector<vector<float>> tmpR;
    vector<vector<float>> tmpG;
    vector<vector<float>> tmpB;
    ImagTranslate::colorImage2Vector(*img,tmpR,tmpG,tmpB);
    vector<vector<float>> resultR = tmpR;
    vector<vector<float>> resultG = tmpG;
    vector<vector<float>> resultB = tmpB;
    for(int i = 1;i < newHeight-1;++i)
    {
        for(int j =1;j< newWidth-1;++j)
        {

            resultR[i][j] = tmpR[i+1][j] + tmpR[i-1][j] + tmpR[i][j+1] + tmpR[i][j-1] - 4*tmpR[i][j];
            resultG[i][j] = tmpG[i+1][j] + tmpG[i-1][j] + tmpG[i][j+1] + tmpG[i][j-1] - 4*tmpG[i][j];
            resultB[i][j] = tmpB[i+1][j] + tmpB[i-1][j] + tmpB[i][j+1] + tmpB[i][j-1] - 4*tmpB[i][j];
            resultR[i][j] = resultR[i][j]>0?(resultR[i][j]>255?255:resultR[i][j]):0;
            resultG[i][j] = resultG[i][j]>0?(resultG[i][j]>255?255:resultG[i][j]):0;
            resultB[i][j] = resultB[i][j]>0?(resultB[i][j]>255?255:resultB[i][j]):0;
        }
    }
    //转回图像
     ImagTranslate::vector2ColorImage(resultR,resultG,resultB,*newImg);
    return newImg;
}

QImage *ImageSegmentation::GaussLaplacianOperator(QImage *img)
{
   int Template1[5][5] =  { 0, 0, -1, 0, 0,
                            0, -1, -2, -1, 0,
                            -1, -2, 16,-2, -1,
                            0, -1, -2, -1, 0,
                            0, 0, -1, 0, 0};
   QImage * newImg = new QImage(*img);
   int newHeight = newImg->height(),
           newWidth = newImg->width();
   vector<vector<float>> tmpR;
   vector<vector<float>> tmpG;
   vector<vector<float>> tmpB;
   ImagTranslate::colorImage2Vector(*img,tmpR,tmpG,tmpB);
   vector<vector<float>> resultR = tmpR;
   vector<vector<float>> resultG = tmpG;
   vector<vector<float>> resultB = tmpB;
   for(int i = 2;i < newHeight-2;++i)
   {
       for(int j =2;j< newWidth-2;++j)
       {
           resultR[i][j] = 0;
           resultG[i][j] = 0;
           resultB[i][j] = 0;
           for(int k =-2;k< 3;++k)
           {
               for(int l =-2;l< 3;++l)
               {

                   resultR[i][j] +=Template1[k+2][l+2]*tmpR[i+k][j+l];
                   resultG[i][j] +=Template1[k+2][l+2]*tmpG[i+k][j+l];
                   resultB[i][j] +=Template1[k+2][l+2]*tmpB[i+k][j+l];
               }
           }
           resultR[i][j] = resultR[i][j]>0?(resultR[i][j]>255?255:resultR[i][j]):0;
           resultG[i][j] = resultG[i][j]>0?(resultG[i][j]>255?255:resultG[i][j]):0;
           resultB[i][j] = resultB[i][j]>0?(resultB[i][j]>255?255:resultB[i][j]):0;
       }
   }
   //转回图像
   ImagTranslate::vector2ColorImage(resultR,resultG,resultB,*newImg);
   return newImg;
}



//这个算子速度很慢，需要调整
QImage *ImageSegmentation::KrischOperator(QImage *img)
{
        int Template1[3][3] = {  5,    5,    5,
                                -3,    0,   -3,
                                -3,   -3,  -3 };
        int Template2[3][3] = { -3,    5,    5,
                                -3,    0,    5,
                                -3,    -3,   -3 };
        int Template3[3][3] = { -3,    -3,   5,
                                -3,     0,   5,
                                -3,    -3,   5 };
        int Template4[3][3] = { -3,    -3,   -3,
                                -3,     0,    5,
                                -3,     5,    5 };
        int Template5[3][3] = { -3,    -3,    -3,
                                -3,     0,    -3,
                                 5,     5,     5 };
        int Template6[3][3] = {  -3,   -3,    -3,
                               5,    0,    -3,
                               5,    5,    -3 };
        int Template7[3][3] = {   5,    -3,   -3,
                               5,     0,   -3,
                               5,    -3,   -3 };
        int Template8[3][3] = {   5,     5,   -3,
                               5,     0,   -3,
                              -3,    -3,   -3 };

        QImage * newImg = new QImage(*img);
        int newHeight = newImg->height(),
                newWidth = newImg->width();
        vector<vector<float>> tmpR;
        vector<vector<float>> tmpG;
        vector<vector<float>> tmpB;
        ImagTranslate::colorImage2Vector(*img,tmpR,tmpG,tmpB);
        vector<vector<float>> resultR1 = tmpR;
        vector<vector<float>> resultG1 = tmpG;
        vector<vector<float>> resultB1 = tmpB;

        vector<vector<float>> resultR2 = tmpR;
        vector<vector<float>> resultG2 = tmpG;
        vector<vector<float>> resultB2 = tmpB;

        vector<vector<float>> resultR3 = tmpR;
        vector<vector<float>> resultG3 = tmpG;
        vector<vector<float>> resultB3 = tmpB;

        vector<vector<float>> resultR4 = tmpR;
        vector<vector<float>> resultG4 = tmpG;
        vector<vector<float>> resultB4 = tmpB;

        vector<vector<float>> resultR5 = tmpR;
        vector<vector<float>> resultG5 = tmpG;
        vector<vector<float>> resultB5 = tmpB;

        vector<vector<float>> resultR6 = tmpR;
        vector<vector<float>> resultG6 = tmpG;
        vector<vector<float>> resultB6 = tmpB;

        vector<vector<float>> resultR7 = tmpR;
        vector<vector<float>> resultG7 = tmpG;
        vector<vector<float>> resultB7 = tmpB;

        vector<vector<float>> resultR8 = tmpR;
        vector<vector<float>> resultG8 = tmpG;
        vector<vector<float>> resultB8 = tmpB;

        for(int i = 1;i < newHeight-1;++i)
        {
            for(int j =1;j< newWidth-1;++j)
            {
                resultR1[i][j] = 0;
                resultG1[i][j] = 0;
                resultB1[i][j] = 0;
                for(int k =-1;k< 2;++k)
                {
                    for(int l =-1;l< 2;++l)
                    {

                        resultR1[i][j] +=Template1[k+1][l+1]*tmpR[i+k][j+l];
                        resultG1[i][j] +=Template1[k+1][l+1]*tmpG[i+k][j+l];
                        resultB1[i][j] +=Template1[k+1][l+1]*tmpB[i+k][j+l];
                    }
                }
                resultR1[i][j] = resultR1[i][j]>0?(resultR1[i][j]>255?255:resultR1[i][j]):0;
                resultG1[i][j] = resultG1[i][j]>0?(resultG1[i][j]>255?255:resultG1[i][j]):0;
                resultB1[i][j] = resultB1[i][j]>0?(resultB1[i][j]>255?255:resultB1[i][j]):0;
            }
        }

        for(int i = 1;i < newHeight-1;++i)
        {
            for(int j =1;j< newWidth-1;++j)
            {
                resultR2[i][j] = 0;
                resultG2[i][j] = 0;
                resultB2[i][j] = 0;
                for(int k =-1;k< 2;++k)
                {
                    for(int l =-1;l< 2;++l)
                    {

                        resultR2[i][j] +=Template2[k+1][l+1]*tmpR[i+k][j+l];
                        resultG2[i][j] +=Template2[k+1][l+1]*tmpG[i+k][j+l];
                        resultB2[i][j] +=Template2[k+1][l+1]*tmpB[i+k][j+l];
                    }
                }
                resultR2[i][j] = resultR2[i][j]>0?(resultR2[i][j]>255?255:resultR2[i][j]):0;
                resultG2[i][j] = resultG2[i][j]>0?(resultG2[i][j]>255?255:resultG2[i][j]):0;
                resultB2[i][j] = resultB2[i][j]>0?(resultB2[i][j]>255?255:resultB2[i][j]):0;
            }
        }

        for(int i = 1;i < newHeight-1;++i)
        {
            for(int j =1;j< newWidth-1;++j)
            {

                resultR3[i][j] = 0;
                resultG3[i][j] = 0;
                resultB3[i][j] = 0;
                for(int k =-1;k< 2;++k)
                {
                    for(int l =-1;l< 2;++l)
                    {

                        resultR3[i][j] +=Template3[k+1][l+1]*tmpR[i+k][j+l];
                        resultG3[i][j] +=Template3[k+1][l+1]*tmpG[i+k][j+l];
                        resultB3[i][j] +=Template3[k+1][l+1]*tmpB[i+k][j+l];
                    }
                }
                resultR3[i][j] = resultR3[i][j]>0?(resultR3[i][j]>255?255:resultR3[i][j]):0;
                resultG3[i][j] = resultG3[i][j]>0?(resultG3[i][j]>255?255:resultG3[i][j]):0;
                resultB3[i][j] = resultB3[i][j]>0?(resultB3[i][j]>255?255:resultB3[i][j]):0;
            }
        }

        for(int i = 1;i < newHeight-1;++i)
        {
            for(int j =1;j< newWidth-1;++j)
            {
                resultR4[i][j] = 0;
                resultG4[i][j] = 0;
                resultB4[i][j] = 0;
                for(int k =-1;k< 2;++k)
                {
                    for(int l =-1;l< 2;++l)
                    {

                        resultR4[i][j] +=Template4[k+1][l+1]*tmpR[i+k][j+l];
                        resultG4[i][j] +=Template4[k+1][l+1]*tmpG[i+k][j+l];
                        resultB4[i][j] +=Template4[k+1][l+1]*tmpB[i+k][j+l];
                    }
                }
                resultR4[i][j] = resultR4[i][j]>0?(resultR4[i][j]>255?255:resultR4[i][j]):0;
                resultG4[i][j] = resultG4[i][j]>0?(resultG4[i][j]>255?255:resultG4[i][j]):0;
                resultB4[i][j] = resultB4[i][j]>0?(resultB4[i][j]>255?255:resultB4[i][j]):0;
            }
        }

        for(int i = 1;i < newHeight-1;++i)
        {
            for(int j =1;j< newWidth-1;++j)
            {
                resultR5[i][j] = 0;
                resultG5[i][j] = 0;
                resultB5[i][j] = 0;
                for(int k =-1;k< 2;++k)
                {
                    for(int l =-1;l< 2;++l)
                    {

                        resultR5[i][j] +=Template5[k+1][l+1]*tmpR[i+k][j+l];
                        resultG5[i][j] +=Template5[k+1][l+1]*tmpG[i+k][j+l];
                        resultB5[i][j] +=Template5[k+1][l+1]*tmpB[i+k][j+l];
                    }
                }
                resultR5[i][j] = resultR5[i][j]>0?(resultR5[i][j]>255?255:resultR5[i][j]):0;
                resultG5[i][j] = resultG5[i][j]>0?(resultG5[i][j]>255?255:resultG5[i][j]):0;
                resultB5[i][j] = resultB5[i][j]>0?(resultB5[i][j]>255?255:resultB5[i][j]):0;
            }
        }

        for(int i = 1;i < newHeight-1;++i)
        {
            for(int j =1;j< newWidth-1;++j)
            {
                resultR6[i][j] = 0;
                resultG6[i][j] = 0;
                resultB6[i][j] = 0;
                for(int k =-1;k< 2;++k)
                {
                    for(int l =-1;l< 2;++l)
                    {

                        resultR6[i][j] +=Template6[k+1][l+1]*tmpR[i+k][j+l];
                        resultG6[i][j] +=Template6[k+1][l+1]*tmpG[i+k][j+l];
                        resultB6[i][j] +=Template6[k+1][l+1]*tmpB[i+k][j+l];
                    }
                }
                resultR6[i][j] = resultR6[i][j]>0?(resultR6[i][j]>255?255:resultR6[i][j]):0;
                resultG6[i][j] = resultG6[i][j]>0?(resultG6[i][j]>255?255:resultG6[i][j]):0;
                resultB6[i][j] = resultB6[i][j]>0?(resultB6[i][j]>255?255:resultB6[i][j]):0;
            }
        }

        for(int i = 1;i < newHeight-1;++i)
        {
            for(int j =1;j< newWidth-1;++j)
            {
                resultR7[i][j] = 0;
                resultG7[i][j] = 0;
                resultB7[i][j] = 0;
                for(int k =-1;k< 2;++k)
                {
                    for(int l =-1;l< 2;++l)
                    {

                        resultR7[i][j] +=Template7[k+1][l+1]*tmpR[i+k][j+l];
                        resultG7[i][j] +=Template7[k+1][l+1]*tmpG[i+k][j+l];
                        resultB7[i][j] +=Template7[k+1][l+1]*tmpB[i+k][j+l];
                    }
                }
                resultR7[i][j] = resultR7[i][j]>0?(resultR7[i][j]>255?255:resultR7[i][j]):0;
                resultG7[i][j] = resultG7[i][j]>0?(resultG7[i][j]>255?255:resultG7[i][j]):0;
                resultB7[i][j] = resultB7[i][j]>0?(resultB7[i][j]>255?255:resultB7[i][j]):0;
            }
        }

        for(int i = 1;i < newHeight-1;++i)
        {
            for(int j =1;j< newWidth-1;++j)
            {
                resultR8[i][j] = 0;
                resultG8[i][j] = 0;
                resultB8[i][j] = 0;
                for(int k =-1;k< 2;++k)
                {
                    for(int l =-1;l< 2;++l)
                    {

                        resultR8[i][j] +=Template8[k+1][l+1]*tmpR[i+k][j+l];
                        resultG8[i][j] +=Template8[k+1][l+1]*tmpG[i+k][j+l];
                        resultB8[i][j] +=Template8[k+1][l+1]*tmpB[i+k][j+l];
                    }
                }
                resultR8[i][j] = resultR8[i][j]>0?(resultR8[i][j]>255?255:resultR8[i][j]):0;
                resultG8[i][j] = resultG8[i][j]>0?(resultG8[i][j]>255?255:resultG8[i][j]):0;
                resultB8[i][j] = resultB8[i][j]>0?(resultB8[i][j]>255?255:resultB8[i][j]):0;
            }
        }
        int tempR[8] = {0,0,0,0,0,0,0,0};
        int tempG[8] = {0,0,0,0,0,0,0,0};
        int tempB[8] = {0,0,0,0,0,0,0,0};
        for(int i = 1;i < newHeight-1;++i)
        {
            for(int j =1;j< newWidth-1;++j)
            {
                tmpR[i][j] = 0;
                tmpG[i][j] = 0;
                tmpB[i][j] = 0;

                tempR[0] = resultR1[i][j];
                tempR[1] = resultR2[i][j];
                tempR[2] = resultR3[i][j];
                tempR[3] = resultR4[i][j];
                tempR[4] = resultR5[i][j];
                tempR[5] = resultR6[i][j];
                tempR[6] = resultR7[i][j];
                tempR[7] = resultR8[i][j];

                tempG[0] = resultG1[i][j];
                tempG[1] = resultG2[i][j];
                tempG[2] = resultG3[i][j];
                tempG[3] = resultG4[i][j];
                tempG[4] = resultG5[i][j];
                tempG[5] = resultG6[i][j];
                tempG[6] = resultG7[i][j];
                tempG[7] = resultG8[i][j];

                tempB[0] = resultB1[i][j];
                tempB[1] = resultB2[i][j];
                tempB[2] = resultB3[i][j];
                tempB[3] = resultB4[i][j];
                tempB[4] = resultB5[i][j];
                tempB[5] = resultB6[i][j];
                tempB[6] = resultB7[i][j];
                tempB[7] = resultB8[i][j];

                for(int k = 0;k<8;k++){
                tmpR[i][j] = tmpR[i][j] > tempR[k]? tmpR[i][j] : tempR[k];
                tmpG[i][j] = tmpG[i][j] > tempG[k]? tmpG[i][j] : tempG[k];
                tmpB[i][j] = tmpB[i][j] > tempB[k]? tmpB[i][j] : tempB[k];
                }
            }
            ImagTranslate::vector2ColorImage(tmpR,tmpG,tmpB,*newImg);
        }
        //将tmpR,tmpG,tmpB转回图像中
        return newImg;
}

//轮廓提取
QImage * ContourExtraction(QImage *img)
{

}

//边界跟踪：改进的虫随法
//需要输入图像为二值图像{0, 255}
QImage * ImageSegmentation::BoundaryTracking(QImage *img)
{

//    //方法1. 只能获取边界，无法获得链码
//    //如果一个黑色点上下左右四个点都是黑色，那它就不是边界点
//    QImage* image = new QImage(*img);
//    int i, j;
//    for(i = 1; i < img->width(); i++)
//    {
//        for(j = 1; j < img->height(); j++)
//        {
//            if(qRed(img->pixel(i, j))==0)
//            {
//                if((qRed(img->pixel(i-1, j))==0)
//                 &&(qRed(img->pixel(i, j-1))==0)
//                 &&(qRed(img->pixel(i, j+1))==0)
//                 &&(qRed(img->pixel(i+1, j))==0))
//                {
//                    image->setPixel(i, j, qRgb(255, 255, 255));
//                }
//                else
//                {
//                    image->setPixel(i, j, qRgb(0, 0, 0));
//                }
//            }

//        }
//    }
//    return image;


//    //方法2. 改进的虫随法，只需平均检测5个点即可，但是只能检测最外边界，并且在某些特殊情况下有bug（单像素穿过多像素）
//    QImage* image = new QImage(*img);
//    typedef struct{
//        int dx;
//        int dy;
//    }diff;
//    diff directions[8] = {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};

//    int width = image->width();
//    int height = image->height();

//    qDebug()<<qRed(image->pixel(2, 3));
//    for(int h = 1; h < height - 1; h++)
//    {
//        for(int w = 1; w < width - 1; w++)
//        {
//            //得到每个点

//            //初始方向
//            int direction = 0;
//            //初始像素
//            int startX, startY;
//            //是否找到一个完整路径
//            bool success = false;

////            QPolygon border;
////            QPainterPath path;

//            //若这个点为黑色（应该被追踪）
//            if(qRed(image->pixel(w, h))==0)
//            {
//                //如果是内部点，则跳过
//                if((qRed(image->pixel(w-1, h))!=255)
//                 &&(qRed(image->pixel(w, h-1))!=255)
//                 &&(qRed(image->pixel(w, h+1))!=255)
//                 &&(qRed(image->pixel(w+1, h))!=255))
//                {
//                    continue;
//                }



//                //初始点坐标
//                startX = w;
//                startY = h;
//                qDebug()<<"start"<<w<<h;

//                //当前点坐标
//                int currentX = w;
//                int currentY = h;
//                //border<<QPoint(w, h);
//                int flag = 0;


//                while(!success)
//                {
//                    int i = 0;


//                    int lastDirection = direction;
//                    //从当前方向顺时针移动2开始
////                    if(flag==0)
////                    {
//                        lastDirection-=2;
//                        if(lastDirection < 0)
//                            lastDirection = (lastDirection+8)%8;
////                    }
////                    if(flag==1)
////                    {
////                        lastDirection+=2;
////                        if(lastDirection >= 8)
////                            lastDirection%=8;
////                    }

//                    qDebug()<<"lastdirection-2"<<lastDirection;
//                    //从direction开始++, >=8则%8, 检查5位

//                    for(i = 0; i < 5; i++)
//                    {
//                        //i为0-4
////                        if(flag==0)
////                        {
//                            direction = lastDirection + i;
//                            if(direction >= 8)
//                                direction%=8;
////                        }
////                        if(flag==1)
////                        {
////                            direction = lastDirection - i;
////                            if(direction < 0)
////                                direction = (direction+8)%8;
////                        }


//                        //检查某个方向
//                        int tempX = currentX+directions[direction].dx;
//                        int tempY = currentY+directions[direction].dy;
//                        if(tempX>=0&&tempX<width&&tempY>=0&&tempY<height)
//                        {
//                            if(qRed(image->pixel(tempX, tempY))==0)
//                            {
//                                //是下一个边缘像素
//                                //若回到了初始点
//                                qDebug()<<"前"<<direction<<"进后";
//                                if(tempX == startX&&tempY == startY)
//                                {
//                                    success = true;
//                                    //qDebug()<<"x:"<<tempX<<"y:"<<tempY;
//                                    //qDebug()<<"方向："<<direction;
//                                    //qDebug()<<"回到了初始点";
//                                    //border<<QPoint(tempX, tempY);
//                                    //置灰
//                                    qDebug()<<"起始点"<<tempX<<tempY;
//                                    image->setPixel(tempX, tempY, qRgb(150, 150, 150));
//                                    //qDebug()<<border.isClosed();
//                                    //填充该封闭区域，break后寻找下一个0点
//                                    break;
//                                }
//                                //压入polygon
//                                //置灰
//                                //border<<QPoint(tempX, tempY);
//                                qDebug()<<tempX<<tempY;
//                                image->setPixel(tempX, tempY, qRgb(150, 150, 150));
//                                currentX = tempX;
//                                currentY = tempY;
//                                lastDirection = direction;
//                                //qDebug()<<"x:"<<tempX<<"y:"<<tempY;
//                                break;
//                            }
////                            else if((qRed(image->pixel(tempX-1, tempY))==150)
////                                    ||(qRed(image->pixel(tempX, tempY-1))==150)
////                                    ||(qRed(image->pixel(tempX, tempY+1))==150)
////                                    ||(qRed(image->pixel(tempX+1, tempY))==150))
////                            {
////                                success = true;
////                                break;
////                            }
//                            else
//                            {
//                                if(i==4)
//                                {
//                                    flag++;
//                                    qDebug()<<"flag++";
//                                    if(flag==1)
//                                    {
//                                        //qDebug()<<"终点";
//                                        currentX = startX;
//                                        currentY = startY;
//                                        direction = 4;
//                                        break;
//                                    }
//                                    if(flag==2)
//                                    {
//                                        //qDebug()<<"尽头";
//                                        success = true;
//                                    }
//                                }
//                            }
//                        }
//                        else
//                        {
//                            continue;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    for(int i = 0; i < image->width(); i++)
//    {
//        for(int j = 0; j < image->height(); j++)
//        {
//            if(qRed(image->pixel(i, j))==0)
//                image->setPixel(i, j, qRgb(255, 255, 255));
//        }
//    }
//    return image;

    //方法3. 自己改进的虫随法，可以检测内外边界，能够处理多像素交叉。能够处理单像素穿过多像素的特殊情况，但该特殊情况下无法获得正确链码
    //
    //  3   2   1
    //  4   p   0
    //  5   6   7
    //
    QImage* image = new QImage(*img);
    typedef struct{
        int dx;
        int dy;
    }diff;
    diff directions[8] = {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};

    //着色
    int color[7] = {70, 83, 116, 149, 182, 215, 250};
    //色序
    int colorNo = 0;
    //边界数
    int border = 0;

    int width = image->width();
    int height = image->height();

    for(int h = 1; h < height - 1; h++)
    {
        for(int w = 1; w < width - 1; w++)
        {
            //得到每个点

            //初始像素
            int startX, startY;
            //是否找到一个完整路径
            bool success = false;


            //若这个点为黑色（应该被追踪）
            if(qRed(image->pixel(w, h))==0)
            {
                //如果是内部点（此处需在原图img进行检测），则跳过
                if((qRed(img->pixel(w-1, h))==0)
                 &&(qRed(img->pixel(w, h-1))==0)
                 &&(qRed(img->pixel(w, h+1))==0)
                 &&(qRed(img->pixel(w+1, h))==0))
                {
                    continue;
                }

                //使用原图img判断是内圈点还是外圈点
                bool isOutSide = false;
                //该点左上方三个点中黑色的数量
                int leftUpSum = 0;
                //该点右下方三个点中黑色的数量
                int rightDownSum = 0;
                if(qRed(img->pixel(w-1, h-1))==0) leftUpSum++;
                if(qRed(img->pixel(w, h-1))==0) leftUpSum++;
                if(qRed(img->pixel(w-1, h))==0) leftUpSum++;
                if(qRed(img->pixel(w+1, h))==0) rightDownSum++;
                if(qRed(img->pixel(w+1, h+1))==0) rightDownSum++;
                if(qRed(img->pixel(w, h+1))==0) rightDownSum++;
                if(leftUpSum==rightDownSum)
                {
                    image->setPixel(w, h, qRgb(color[colorNo], color[colorNo], color[colorNo]));
                }
                else if(leftUpSum<rightDownSum)
                {
                    image->setPixel(w, h, qRgb(color[colorNo], color[colorNo], color[colorNo]));
                    isOutSide = true;
                }
                else
                {
                    image->setPixel(w, h, qRgb(color[colorNo], color[colorNo], color[colorNo]));
                    isOutSide = false;
                }

                //初始方向，内圈为5，退2位，从3开始
                int direction = 5;
                //初始方向，外圈为4，退2位，从6（而不是3的对角7）开始（6是经验值，可以避免内圈有形如5、p、7三点，从5开始遍历时出现错误）
                if(!isOutSide)
                    direction = 4;

                //初始点坐标
                startX = w;
                startY = h;
                qDebug()<<"start from"<<w<<h;

                //当前点坐标
                int currentX = w;
                int currentY = h;

                //虫随法沿着一条路走到重点（周围再也找不到黑色点）时，会将flag++并返回初始点，以相反的方向重新搜索。如果flag==2，则认为寻找到一条完整路径，结束此次搜索。
                int flag = 0;


                while(!success)
                {
                    int i = 0;

                    int lastDirection = direction;

                    //外圈，flag==0， 从3开始逆时针搜索（顺逆时针体现在for循环内对direction的操作）
                    if(isOutSide&&(flag==0))
                    {
                        lastDirection-=2;
                        if(lastDirection < 0)
                        lastDirection = (lastDirection+8)%8;
                    }
                    //外圈，flag==1， 从3开始顺时针搜索
                    else if(isOutSide&&(flag==1))
                    {
                        lastDirection+=2;
                        if(lastDirection >= 8)
                        lastDirection%=8;
                    }
                    //内圈，flag==0， 从6开始顺时针搜索
                    else if((!isOutSide)&&(flag==0))
                    {
                        lastDirection+=2;
                        if(lastDirection >= 8)
                        lastDirection%=8;
                    }
                    //内圈，flag==1， 从6开始逆时针搜索
                    else
                    {
                        lastDirection+=2;
                        if(lastDirection >= 8)
                        lastDirection%=8;
                    }

                    for(i = 0; i < 5; i++)
                    {
                        if(isOutSide&&(flag==0))
                        {
                            direction = lastDirection + i;
                            if(direction >= 8)
                            direction%=8;
                        }
                        else if(isOutSide&&(flag==1))
                        {
                            direction = lastDirection - i;
                            if(direction < 0)
                            direction = (direction+8)%8;
                        }
                        else if((!isOutSide)&&(flag==0))
                        {
                            direction = lastDirection - i;
                            if(direction < 0)
                            direction = (direction+8)%8;
                        }
                        else
                        {
                            direction = lastDirection + i;
                            if(direction >= 8)
                            direction%=8;

                        }

                        //检查该方向
                        int tempX = currentX+directions[direction].dx;
                        int tempY = currentY+directions[direction].dy;
                        if(tempX>=0&&tempX<width&&tempY>=0&&tempY<height)
                        {
                            if(qRed(image->pixel(tempX, tempY))==0)
                            {
                                //黑色，则是下一个边缘像素
                                //若回到了初始点，则认为找到了一条【封闭的完整路径】，比如凸多边形、圆形
                                if(tempX == startX&&tempY == startY)
                                {
                                    success = true;
                                    image->setPixel(tempX, tempY, qRgb(color[colorNo], color[colorNo], color[colorNo]));
                                    break;
                                }
                                image->setPixel(tempX, tempY, qRgb(color[colorNo], color[colorNo], color[colorNo]));
                                currentX = tempX;
                                currentY = tempY;
                                lastDirection = direction;
                                break;
                            }
                            else
                            {
                                if(i==4||((qRed(image->pixel(tempX, tempY))!=0)&&(qRed(image->pixel(tempX, tempY))!=255)))
                                {
                                    flag++;
                                    //若是一个方向到尽头了，则回到初始点，从反方向开始搜索
                                    if(flag==1)
                                    {
                                        //image->setPixel(currentX, currentY, qRgb(color[num], color[num], color[num]));
                                        currentX = startX;
                                        currentY = startY;
                                        //flag==1后，回到while循环会固定对direction+2，所以为了外圈从3开始内圈从6开始，需要如下设置
                                        if(isOutSide)
                                            direction = 1;
                                        else
                                            direction = 4;
                                        break;
                                    }
                                    //若是从初始点走第二个方向又到头了，则认为找到了一条【不封闭的完整路径】，比如线段
                                    if(flag==2)
                                    {
                                        //image->setPixel(currentX, currentY, qRgb(color[num], color[num], color[num]));
                                        success = true;
                                        colorNo++;
                                        if(colorNo>=6)
                                            colorNo=0;
                                        border++;
                                        break;
                                    }
                                }


                            }
                        }
                        else
                        {
                            continue;
                        }

                    }
                }
            }
        }
    }
    //之前略过的“黑色内部点”全部改为背景色
    for(int i = 0; i < image->width(); i++)
    {
        for(int j = 0; j < image->height(); j++)
        {
            if(qRed(image->pixel(i, j))==0)
                image->setPixel(i, j, qRgb(255, 255, 255));
        }
    }
    QMessageBox::information(NULL, "边界追踪结果", QString("共追踪到的封闭边界数：")+QString::number(border));
    delete img;
    img = NULL;
    return image;

}

// Hough 变换识别图片中的直线
QImage * ImageSegmentation::houghTran(QImage & image)
{
    int width = image.width();
    int height = image.height();


    int theaterMax = 90;
    int RMax = width + height; //假定最大的数为x * 1 + y * 1
    QVector<double> sinValue(91);
    QVector<double> cosValue(91);

    for(int i = 0; i <= theaterMax; i++){
        sinValue[i] = sin(i*3.1415926/180);
        cosValue[i] = cos(i*3.1415926/180);
    }

     qDebug() << sinValue;

    //累加数组
    QVector<QVector<int>> culmData(RMax, QVector<int>(91));

    int RValue = 0;
    for(int i = 0; i < width; i++){
        for(int j =0; j < height; j++){

            if(qRed(image.pixel(i, j)) >= 250){
                qDebug() << qRed(image.pixel(i, j));
                for(int k = 0; k <= theaterMax; k++){
                    RValue = (int) (i * sinValue[k] + j * cosValue[k] + 0.5);
                    culmData[RValue][k] += 1;
                }
            }

        }
        if( i % 100 == 0){
            qDebug() << "caculing" << i;
        }
    }



    QImage * newImage = new QImage(width, height, QImage::Format_RGB888);
    int lineR = 0;
    int lineTheater = 0;


    // 如果点的数量大于 100 则视为一条直线
    for(int i = 0; i < RMax; i++){
        for(int j = 0; j <= theaterMax; j++){
            if(100 < culmData[i][j]){
                lineR = i;
                lineTheater = j;

                // 如果发现一条直线，那就遍历图像将直线所有的点设置为红色（效率低下）
                for(int i1 = 0; i1 < width; i1++){
                    for(int j1 = 0; j1 < height; j1++){
                        if(qRed(image.pixel(i1, j1)) >= 250){
                            int temp = i1 * sinValue[lineTheater] + j1 * cosValue[lineTheater] + 0.5;
                            if(temp <= lineR + 1 && temp >= lineR - 1 ){
                                newImage->setPixel(i1, j1, qRgb(255, 0, 0));
                            }
                        }


                    }

                }

            }


        }
    }

    qDebug() << lineR << lineTheater;

    delete(&sinValue);
    delete(&cosValue);

    return newImage;
}













