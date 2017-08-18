#include "imagesegmentation.h"


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
    vector<vector<float>> tmp;
    ImagTranslate::greyImage2Vector(*img,tmp);
    vector<vector<float>> result = tmp;
    for(int i = 0;i < newHeight-1;++i)
    {
        for(int j =0;j< newWidth-1;++j)
        {
            result[i][j] = abs(tmp[i][j]-tmp[i+1][j+1])+abs(tmp[i+1][j]-tmp[i][j+1]);
            result[i][j] = result[i][j]>255?255:result[i][j];
        }
    }
    //转回图像
    ImagTranslate::vector2GreyImage(result,*newImg);
    return newImg;
}



QImage *ImageSegmentation::SobelOperator(QImage *img)
{
    QImage * newImg = new QImage(*img);
    int newHeight = newImg->height(),
            newWidth = newImg->width();
    vector<vector<float>> tmp;
    ImagTranslate::greyImage2Vector(*img,tmp);
    vector<vector<float>> result = tmp;
    float resultX,resultY;
    for(int i = 1;i < newHeight-1;++i)
    {
        for(int j =1;j< newWidth-1;++j)
        {
            resultX      = tmp[i-1][j+1] + 2*tmp[i][j+1] + tmp[i+1][j+1]-(tmp[i-1][j-1] + 2*tmp[i][j-1] + tmp[i+1][j-1]);
            resultY      = tmp[i+1][j+1] + 2*tmp[i+1][j] + tmp[i+1][j-1]-(tmp[i-1][j+1] + 2*tmp[i-1][j] + tmp[i-1][j-1]);
            result[i][j] = sqrt( resultX* resultX+ resultY* resultY);
            result[i][j] = result[i][j]>255?255:result[i][j];
        }
    }
    //转回图像
    ImagTranslate::vector2GreyImage(result,*newImg);
    return newImg;
}

QImage *ImageSegmentation::PrewittOperator(QImage *img)
{

    QImage * newImg = new QImage(*img);
    int newHeight = newImg->height(),
            newWidth = newImg->width();
    vector<vector<float>> tmp;
    ImagTranslate::greyImage2Vector(*img,tmp);
    vector<vector<float>> result = tmp;
    float resultX,resultY;
    for(int i = 1;i < newHeight-1;++i)
    {
        for(int j =1;j< newWidth-1;++j)
        {
            resultX      = tmp[i-1][j+1] + tmp[i][j+1] + tmp[i+1][j+1]-(tmp[i-1][j-1] + tmp[i][j-1] + tmp[i+1][j-1]);
            resultY      = tmp[i+1][j+1] + tmp[i+1][j] + tmp[i+1][j-1]-(tmp[i-1][j+1] + tmp[i-1][j] + tmp[i-1][j-1]);
            result[i][j] = sqrt( resultX* resultX+ resultY* resultY);
            result[i][j] = result[i][j]>255?255:result[i][j];
        }
    }
    //转回图像
    ImagTranslate::vector2GreyImage(result,*newImg);
    return newImg;
}



//    Laplace算子对孤立象素的响应要比对边缘或线的响应要更强烈，因此只适用于无噪声图象。存在噪声情况下，使用Laplacian算子检测边缘之前需要先进行低通滤波
QImage *ImageSegmentation::LaplacianOperator(QImage *img)
{
    QImage * newImg = new QImage(*img);
    int newHeight = newImg->height(),
            newWidth = newImg->width();
    vector<vector<float>> tmp;
    ImagTranslate::greyImage2Vector(*img,tmp);
    vector<vector<float>> result = tmp;
    for(int i = 1;i < newHeight-1;++i)
    {
        for(int j =1;j< newWidth-1;++j)
        {

            result[i][j] = tmp[i+1][j] + tmp[i-1][j] + tmp[i][j+1] + tmp[i][j-1] - 4*tmp[i][j];
            result[i][j] = result[i][j]>0?(result[i][j]>255?255:result[i][j]):0;s
        }
    }
    //转回图像
    ImagTranslate::vector2GreyImage(result,*newImg);
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
   vector<vector<float>> tmp;
   ImagTranslate::greyImage2Vector(*img,tmp);
   vector<vector<float>> result = tmp;
   for(int i = 2;i < newHeight-2;++i)
   {
       for(int j =2;j< newWidth-2;++j)
       {
           result[i][j]  = 0;
           for(int k =-2;k< 3;++k)
           {
               for(int l =-2;l< 3;++l)
               {

                   result[i][j] +=Template1[k+2][l+2]*tmp[i+k][j+l];
               }
           }
           result[i][j] = result[i][j]>0?(result[i][j]>255?255:result[i][j]):0;
       }
   }
   //转回图像
   ImagTranslate::vector2GreyImage(result,*newImg);
   return newImg;

}

