#include "imageenhancement.h"

double ImageEnhancement::V1 = 0.0;
double ImageEnhancement::V2 = 0.0;
double ImageEnhancement::S = 0.0;
int ImageEnhancement::phase = 0;

ImageEnhancement::ImageEnhancement()
{
}
//以下是外部接口

//添加高斯噪声。mu为均值, sigma为方差，k为噪声系数，均需外部传入
void ImageEnhancement::AddGaussianNoise(QImage *image, double mu, double sigma, int k)
{
    srand((unsigned int)(time(NULL)));
    int width = 0;
    int height = 0;
    //得到一个从左到右，从上到下遍历的RGB像素点QList
    QList<QRgb> * rgbList =  ImagTranslate::imageToList(*image, width, height);
    //image.convertToFormat(QImage::Format_ARGB32);
    // 循环遍历QList 进行像素点的操作，然后对Image 对象进行逐个像素点的赋值
    for(int i = 0; i < width * height; i++){
        QRgb pixel = rgbList->at(i);
        int Red = qRed(pixel) + k*GenerateGaussianNoise(0, 1);
        if(Red > 255) Red = 255;
        if(Red < 0) Red = 0;
        int Green = qGreen(pixel)+ k*GenerateGaussianNoise(0, 1);
        if(Green > 255) Green = 255;
        if(Green < 0) Green = 0;
        int Blue = qBlue(pixel)+ k*GenerateGaussianNoise(0, 1);
        if(Blue > 255) Blue = 255;
        if(Blue < 0) Blue = 0;
        QRgb newPixel = qRgb(Red, Green, Blue);
        // i % width 得到目前像素点的列值，i /width 得到当前像素点的行值
        image->setPixel(i / height , i % height, newPixel);
    }
    delete rgbList;
    qDebug()<<"done";
}

void ImageEnhancement::AddSaltPepperNoise(QImage* image, double snr)
{
    srand((unsigned int)(time(NULL)));
    //像素点个数
    for(int i = 0; i < image->width()*image->height()*(1.0-snr); i++)
    {

        //qDebug()<<x<<y<<image->width()<<image->height();
        QRgb newPixel;
        if(rand()%2)
        {
            newPixel = qRgb(0, 0, 0);
        }
        else
        {
            newPixel = qRgb(255, 255, 255);
        }
        int x = (int)(rand()*1.0/RAND_MAX*(double)image->width());
        if(x == image->width()) x--;
        int y = (int)(rand()*1.0/RAND_MAX*(double)image->height());
        if(y == image->height()) y--;
        image->setPixel(x, y, newPixel);
    }
}

QImage *ImageEnhancement::MeanSmoothing(QImage* image)
{
//    int width = image->width();
//    int height = image->height();
//    //得到一个从左到右，从上到下遍历的RGB像素点QList
//    QList<QRgb> * rgbList =  ImagTranslate::imageToList(*image, width, height);
//    QList<QRgb> * afterList = new QList<QRgb>();
//    //每个像素点，取周围9个均值
//    for(int i = 0; i < width * height; i++){
//        QRgb pixel = rgbList->at(i);


//        QRgb newPixel = qRgb(Red, Green, Blue);
//    }
//    // i % width 得到目前像素点的列值，i /width 得到当前像素点的行值
//    image->setPixel(i / height , i % height, newPixel);
//    delete rgbList;
//    qDebug()<<"done";
    int x = 0;
    int y = 0;
    QImage* afterSmooth = new QImage(image->width(), image->height(), image->format());
    for(x = 0; x < image->width(); x++)
    {
        for(y = 0; y < image->height(); y++)
        {
            //得到周围8个
            int sum = 0;
            int times = 0;
            for(int a = x - 1; a <= x + 1; a++)
            {
                for(int b = y - 1; b <= y + 1; b++)
                {
                    if(a>=0&&a<image->width()&&b>=0&&b<image->height())
                    {
                        times++;
                        sum+=qRed(image->pixel(a, b));
                    }
                }
            }
            sum = sum / 9;
            QRgb newPixel = qRgb(sum, sum, sum);
            afterSmooth->setPixel(x, y, newPixel);
        }
    }
    delete image;
    image = NULL;
    return afterSmooth;
}

//以下是内部方法

//产生高斯噪声数值
//每进行一次生成，产生V1、V2两个地位相同的值，默认结果X与V1相关，之后phase在0和1之间转换一次
//下次生成直接使用V2生成X， 第三次再重新生成V1、V2
double ImageEnhancement::GenerateGaussianNoise(double mu, double sigma)
{
    double X, U1, U2;
    if(ImageEnhancement::phase == 0)
    {
        do
        {
            U1 = (double)rand()/RAND_MAX;
            U2 = (double)rand()/RAND_MAX;

            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;

            S = V1*V1 + V2*V2;
        }while(S >= 1 || S == 0);
        X = V1 * sqrt(-2 * log(S) / S);
    }
    else
    {
        X = V2 * sqrt(-2 * log(S) / S);
    }
    phase = 1 - phase;
    return mu+sigma*X;
}
