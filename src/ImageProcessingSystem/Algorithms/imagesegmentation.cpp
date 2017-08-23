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














