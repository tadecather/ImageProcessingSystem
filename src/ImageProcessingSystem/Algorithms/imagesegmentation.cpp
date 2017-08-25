#include "imagesegmentation.h"

#include "dct.h"
#include "imagegray.h"
#include <QStack>

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

        int sum1 = 0;
        for( int n = i + 1; n < 256; n++){
            sum1 += n * grayHist[i];
        }
        double u1 = sum1 * 1.0 / N1;

        double g = w0*w1*(u0-u1)*(u0-u1);

        if(g > gMax){
            gMax = g;
            max = i;
        }

    }

    QImage * newImage = ImageGray::binaryzation(&image, 1, max);

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


// 区域生长
QImage *ImageSegmentation::regionGrowing(QImage *image)
{
    // 种子点周围的点
    int connectPoint[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    QImage * newImage = new QImage(image->width(), image->height(), QImage::Format_RGB888);
    // 标记是否被检查过
    QVector<QVector<int>> flagMatrix(image->width(), QVector<int>(image->height()));

    // 存放种子点的栈
    QStack<int *> seedStack;

    int  * seed;

    // 初始牙入栈的三个种子
    seed = new int[2];
    seed[0] = 0;
    seed[1] = 0;
    seedStack.push(seed);

    seed = new int[2];
    seed[0] = image->width() - 1;
    seed[1] = image->height() - 1;
    seedStack.push(seed);

    seed = new int[2];
    seed[0] = image->width()/2 - 1;
    seed[1] = image->height()/2 - 1;
    seedStack.push(seed);

   // 栈不为空，就继续遍历
    while(!seedStack.isEmpty()){
        int * point = seedStack.top();
        int seedx = point[0];
        int seedy = point[1];
        seedStack.pop();
        delete(point);

        // 标记点
        flagMatrix[seedx][seedy] = 1;

        //遍历周围8个点

        for(int i = 0; i < 8; i++){
            int tempx = seedx + connectPoint[i][0];
            int tempy = seedy + connectPoint[i][1];

            // 出界，接受本次循环
            if(tempx < 0 || tempy < 0 || tempx >= image->width() || tempy >= image->height()){
                continue;
            }

            // 如果遍历到的点位前景点，并且没有被标记过
            if(qRed(image->pixel(tempx, tempy)) >= 128 && flagMatrix[tempx][tempy] != 1){
               newImage->setPixel(tempx, tempy, qRgb(255, 255, 255));    // 生长
               flagMatrix[tempx][tempy] = 1; //标记
               seed = new int[2];
               seed[0] = tempx;
               seed[1] = tempy;
               seedStack.push(seed);   // 入栈
            }
        }
    }
    return newImage;

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













