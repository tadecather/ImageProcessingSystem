#include "imagesegmentation.h"


#include "imagegray.h"

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
