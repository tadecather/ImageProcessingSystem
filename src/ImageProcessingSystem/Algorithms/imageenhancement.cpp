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
}

//添加椒盐噪声
void ImageEnhancement::AddSaltPepperNoise(QImage* image, double snr)
{
    srand((unsigned int)(time(NULL)));
    //像素点个数
    for(int i = 0; i < image->width()*image->height()*(1.0-snr); i++)
    {
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

//均值平滑
QImage *ImageEnhancement::MeanSmoothing(QImage* image, int size)
{
    int x = 0;
    int y = 0;
    int sum = 0;
    //当前像素周围共times个像素
    int times = 0;
    //用于获取中心点周围size*size区域其他点的坐标
    int diff = size/2;
    qDebug()<<"diff"<<diff;
    QImage* afterSmooth = new QImage(image->width(), image->height(), image->format());
    for(x = 0; x < image->width(); x++)
    {
        for(y = 0; y < image->height(); y++)
        {
            //得到周围像素
            for(int a = x - diff; a <= x + diff; a++)
            {
                for(int b = y - diff; b <= y + diff; b++)
                {
                    if(a>=0&&a<image->width()&&b>=0&&b<image->height())
                    {
                        if(a == x && b == y)
                            continue;
                        sum+=qRed(image->pixel(a, b));
                        times++;
                    }

                }
            }
            sum = sum / times;
            times = 0;
            QRgb newPixel = qRgb(sum, sum, sum);
            sum = 0;
            afterSmooth->setPixel(x, y, newPixel);
        }
    }
    delete image;
    image = NULL;
    return afterSmooth;
}

//中值平滑
QImage* ImageEnhancement::MedianSmoothing(QImage* image, int size)
{
    int x = 0;
    int y = 0;
    //用于获取中心点周围size*size区域其他点的坐标
    int diff = size/2;
    QImage* afterSmooth = new QImage(image->width(), image->height(), image->format());
    std::vector<int> surround;
    QRgb newPixel;
    int median;
    for(x = 0; x < image->width(); x++)
    {
        for(y = 0; y < image->height(); y++)
        {
            for(int a = x - diff; a <= x + diff; a++)
            {
                for(int b = y - diff; b <= y + diff; b++)
                {
                    if(a>=0&&a<image->width()&&b>=0&&b<image->height())
                    {
                        surround.push_back(qRed(image->pixel(a, b)));
                    }
                }
            }
            std::sort(surround.begin(), surround.end());
            median = surround[surround.size()/2];
            newPixel = qRgb(median, median, median);
            afterSmooth->setPixel(x, y, newPixel);
            surround.clear();
        }
    }
    delete image;
    image = NULL;
    return afterSmooth;
}

//加权平滑（高斯平滑）
QImage* ImageEnhancement::GaussianSmoothing(QImage* image, int size, int theta)
{
    QImage* afterSmooth = new QImage(image->width(), image->height(), image->format());
    //高斯核，size需要>=3且为奇数
    double gMask[size][size];
    //中心元素的坐标
    int medium = size/2;
    //核的元素和，倒数即为规范系数
    double sum = 0;
    //可优化 因为高斯核中心对称
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            double param1 = (double)(1.0/(theta*theta));
            double distance = (double)((i-medium)*(i-medium)+(j-medium)*(j-medium));
            double param2 = (double)exp(((-1)*distance)/(2*(double)theta*(double)theta));
            gMask[i][j] = (double)param1*param2;
            sum+=gMask[i][j];
        }
    }
    //遍历所有像素
    int x;
    int y;
    //当前像素周围的像素
    int a;
    int b;
    double result = 0.0;
    QRgb newPixel;
    for(x = 0; x < image->width(); x++)
    {
        for(y = 0; y < image->height(); y++)
        {
            //得到周围size^2个
            for(a = x - medium; a <= x + medium; a++)
            {
                for(b = y - medium; b <= y + medium; b++)
                {
                    if(a>=0&&a<image->width()&&b>=0&&b<image->height())
                    {
                        result+=gMask[a-x+medium][b-y+medium]*(double)qRed(image->pixel(a, b))*(1.0/sum);
                    }
                }
            }
            newPixel = qRgb(result, result, result);
            afterSmooth->setPixel(x, y, newPixel);
            result = 0.0;
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
