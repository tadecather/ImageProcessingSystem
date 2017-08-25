#include "imageenhancement.h"

double ImageEnhancement::V1 = 0.0;
double ImageEnhancement::V2 = 0.0;
double ImageEnhancement::S = 0.0;
int ImageEnhancement::phase = 0;

ImageEnhancement::ImageEnhancement()
{
}
//以下是外部接口

//添加高斯噪声。mu为均值, sigma为方差，k为噪声系数，均需外部传入S
void ImageEnhancement::AddGaussianNoise(QImage *image, double mu, double sigma, int k)
{
    srand((unsigned int)(time(NULL)));
    int width = 0;
    int height = 0;
    QList<QRgb> * rgbList =  ImagTranslate::imageToList(*image, width, height);
    for(int i = 0; i < width * height; i++)
    {
        QRgb pixel = rgbList->at(i);
        int Red = qRed(pixel) + k*GenerateGaussianNoise(mu, sigma);
        if(Red > 255) Red = 255;
        if(Red < 0) Red = 0;
        int Green = qGreen(pixel)+ k*GenerateGaussianNoise(mu, sigma);
        if(Green > 255) Green = 255;
        if(Green < 0) Green = 0;
        int Blue = qBlue(pixel)+ k*GenerateGaussianNoise(mu, sigma);
        if(Blue > 255) Blue = 255;
        if(Blue < 0) Blue = 0;
        QRgb newPixel = qRgb(Red, Green, Blue);
        // i % width 得到目前像素点的列值，i /width 得到当前像素点的行值
        image->setPixel(i / height , i % height, newPixel);
    }
    delete rgbList;
}

//添加椒盐噪声， snr为信噪比
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

//均值平滑, size为均值平滑矩阵大小
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
            //得到均值
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

//中值平滑， size为中值平滑矩阵大小
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
        //qDebug()<<gMask[i][0]<<"    "<<gMask[i][1]<<"    "<<gMask[i][2]<<"    "<<gMask[i][3]<<"    "<<gMask[i][4];
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

//选择式掩模平滑
QImage* ImageEnhancement::SelectiveMaskSmoothing(QImage* image)
{
    //拷贝构造，这样边缘两个像素就略过不管了
    QImage* afterSmooth = new QImage(*image);
    //9个掩模对应的 均值
    double mu[9] = {-1.0};
    //9个掩模对应的 方差
    double sigma[9] = {-1.0};
    //中心像素周围的25个像素，默认0
    int mask[5][5] = {-1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1};
    int x, y, a, b;
    //待设置的pixel
    QRgb newPixel;
    //每个像素，取得它周围25个像素
    for(x = 2; x < image->width()-2; x++)
    {
        for(y = 2; y < image->height()-2; y++)
        {
            //中心像素为pixel(x, y)
            for(a = x - 2; a <= x + 2; a++)
            {
                for(b = y - 2; b <= y + 2; b++)
                {
                    //为mask赋值
                    mask[a - x + 2][b - y + 2] = qRed(image->pixel(a, b));
                    //这个mask没有问题!!
                }
            }
            //得到每个中心像素的mask, x,y为该中心像素坐标
            //针对计算9种模板的均值、方差，将方差最小的模板的方差赋给pixel(x, y)
            //模板1
            mu[0] = (mask[1][1]+mask[1][2]+mask[1][3]+mask[2][1]+mask[2][2]+mask[2][3]+mask[3][1]+mask[3][2]+mask[3][3])/9;
            sigma[0] = mask[1][1]*mask[1][1]
                      +mask[1][2]*mask[1][2]
                      +mask[1][3]*mask[1][3]
                      +mask[2][1]*mask[2][1]
                      +mask[2][2]*mask[2][2]
                      +mask[2][3]*mask[2][3]
                      +mask[3][1]*mask[3][1]
                      +mask[3][2]*mask[3][2]
                      +mask[3][3]*mask[3][3]
                      -9*(mu[0]*mu[0]);

            //模板2
            mu[1] = (mask[0][1]+mask[1][1]+mask[0][2]+mask[1][2]+mask[2][2]+mask[0][3]+mask[1][3])/7;
            sigma[1] = mask[0][1]*mask[0][1]
                       +mask[1][1]*mask[1][1]
                       +mask[0][2]*mask[0][2]
                       +mask[1][2]*mask[1][2]
                       +mask[2][2]*mask[2][2]
                       +mask[0][3]*mask[0][3]
                       +mask[1][3]*mask[1][3]
                       -7*(mu[1]*mu[1]);
            //模板3
            mu[2] = (mask[1][0]+mask[2][0]+mask[3][0]+mask[1][1]+mask[2][1]+mask[3][1]+mask[2][2])/7;
            sigma[2] = mask[1][0]*mask[1][0]
                    +mask[2][0]*mask[2][0]
                    +mask[3][0]*mask[3][0]
                    +mask[1][1]*mask[1][1]
                    +mask[2][1]*mask[2][1]
                    +mask[3][1]*mask[3][1]
                    +mask[2][2]*mask[2][2]
                    -7*(mu[2]*mu[2]);
            //模板4
            mu[3] = (mask[3][1]+mask[4][1]+mask[2][2]+mask[3][2]+mask[4][2]+mask[3][3]+mask[4][3])/7;
            sigma[3] = mask[3][1]*mask[3][1]
                    +mask[4][1]*mask[4][1]
                    +mask[2][2]*mask[2][2]
                    +mask[3][2]*mask[3][2]
                    +mask[4][2]*mask[4][2]
                    +mask[3][3]*mask[3][3]
                    +mask[4][3]*mask[4][3]
                    -7*(mu[3]*mu[3]);
            //模板5
            mu[4] = (mask[2][2]+mask[1][3]+mask[2][3]+mask[3][3]+mask[1][4]+mask[2][4]+mask[3][4])/7;
            sigma[4] = mask[2][2]*mask[2][2]
                    +mask[1][3]*mask[1][3]
                    +mask[2][3]*mask[2][3]
                    +mask[3][3]*mask[3][3]
                    +mask[1][4]*mask[1][4]
                    +mask[2][4]*mask[2][4]
                    +mask[3][4]*mask[3][4]
                    -7*(mu[4]*mu[4]);
            //模板6
            mu[5] = (mask[0][0]+mask[1][0]+mask[0][1]+mask[1][1]+mask[2][1]+mask[1][2]+mask[2][2])/7;
            sigma[5] = mask[0][0]*mask[0][0]
                    +mask[1][0]*mask[1][0]
                    +mask[0][1]*mask[0][1]
                    +mask[1][1]*mask[1][1]
                    +mask[2][1]*mask[2][1]
                    +mask[1][2]*mask[1][2]
                    +mask[2][2]*mask[2][2]
                    -7*(mu[5]*mu[5]);
            //模板7
            mu[6] = (mask[3][0]+mask[4][0]+mask[2][1]+mask[3][1]+mask[4][1]+mask[2][2]+mask[3][2])/7;
            sigma[6] = mask[3][0]*mask[3][0]
                    +mask[4][0]*mask[4][0]
                    +mask[2][1]*mask[2][1]
                    +mask[3][1]*mask[3][1]
                    +mask[4][1]*mask[4][1]
                    +mask[2][2]*mask[2][2]
                    +mask[3][2]*mask[3][2]
                    -7*(mu[6]*mu[6]);
            //模板8
            mu[7] = (mask[2][2]+mask[3][2]+mask[2][3]+mask[3][3]+mask[4][3]+mask[3][4]+mask[4][4])/7;
            sigma[7] = mask[2][2]*mask[2][2]
                    +mask[3][2]*mask[3][2]
                    +mask[2][3]*mask[2][3]
                    +mask[3][3]*mask[3][3]
                    +mask[4][3]*mask[4][3]
                    +mask[3][4]*mask[3][4]
                    +mask[4][4]*mask[4][4]
                    -7*(mu[7]*mu[7]);
            //模板9
            mu[8] = (mask[1][2]+mask[2][2]+mask[0][3]+mask[1][3]+mask[2][3]+mask[0][4]+mask[1][4])/7;
            sigma[8] = mask[1][2]*mask[1][2]
                    +mask[2][2]*mask[2][2]
                    +mask[0][3]*mask[0][3]
                    +mask[1][3]*mask[1][3]
                    +mask[2][3]*mask[2][3]
                    +mask[0][4]*mask[0][4]
                    +mask[1][4]*mask[1][4]
                    -7*(mu[8]*mu[8]);

            //取得最小的方差序号， 为minSigmaIndex
            int minSigma = sigma[0];
            int minSigmaIndex = 0;
            for(int i = 0; i <= 8; i++)
            {
                if(sigma[i]<minSigma)
                {
                    minSigma = sigma[i];
                    minSigmaIndex = i;
                }
            }

            //取方差最小的掩模的均值，作为新像素点的值
            int result = mu[minSigmaIndex];
            newPixel = qRgb(result, result, result);
            afterSmooth->setPixel(x, y, newPixel);

//            //输出"选择性掩模测试图"的结果
//            if(x==2&&y==2)
//            std::cout<<"mask at (2, 2) :"<<minSigmaIndex<<"\n";
//            if(x==8&&y==2)
//            std::cout<<"mask at (8, 2) :"<<minSigmaIndex<<"\n";
//            if(x==14&&y==2)
//            std::cout<<"mask at (14, 2) :"<<minSigmaIndex<<"\n";

        }
    }
    delete image;
    image = NULL;
    return afterSmooth;
}

QImage* ImageEnhancement::GradientSharpening(QImage* image, int operatorNo, double multiplier)
{
    //operatorNo为选择的锐化算子序号(0~2)，0为Roberts, 1为Sobel, 2为Prewitt, multiplier为叠加时算子处理后图像的乘数

    //算子处理后的图像
    QImage* after = new QImage(*image);

    //最终图像
    QImage* result = new QImage(*image);

    if(operatorNo == 0)
    {
        //Roberts算子
        after = ImageSegmentation::RobertOperator(after);
    }
    else if(operatorNo == 1)
    {
        //Sobel算子
        after = ImageSegmentation::SobelOperator(after);
    }
    else
    {
        //Prewitt算子
        after = ImageSegmentation::PrewittOperator(after);
    }

    for(int i = 0; i < image->width()-1; i++)
    {
        for(int j = 0; j < image->height() - 1; j++)
        {
            double resultP = (double)qRed(image->pixel(i, j))-multiplier*(double)qRed(after->pixel(i, j));
            if(resultP < 0) resultP = 0;
            result->setPixel(i, j, qRgb((int)resultP, (int)resultP, (int)resultP));
        }
    }

    delete after;
    after = NULL;
    return result;
}

//拉普拉斯锐化
QImage* ImageEnhancement::LaplacianSharpening(QImage* image, double multiplier)
{
    //算子处理后的图像
    QImage* after = new QImage(*image);

    //最终图像
    QImage* result = new QImage(*image);


    after = ImageSegmentation::LaplacianOperator(after);


    for(int i = 0; i < image->width()-1; i++)
    {
        for(int j = 0; j < image->height() - 1; j++)
        {
            if(qRed(after->pixel(i, j))>=0)
            {
                double resultP = (double)qRed(image->pixel(i, j))-multiplier*(double)qRed(after->pixel(i, j));
                if(resultP < 0 ) resultP = 0;
                result->setPixel(i, j, qRgb((int)resultP, (int)resultP, (int)resultP));
            }

        }
    }

    delete after;
    after = NULL;
    return result;
}

//图像质量评价，输出MSE(可进而计算得到PTNR)
double ImageEnhancement::ImageQualityAssessment(QImage* ref, QImage* img)
{
    //图片为MxN, 计算公式为(1/(m*n))*(每个点的灰度值差值平方 和)
    //要评估的图像需比参考图大
    if(!(img->width()>=ref->width()&&img->height()>=ref->height()))
    {
        return -1.0;
    }
    //方误差
    double squareError = 0.0;
    for(int i = 0; i < ref->width(); i++)
    {
        for(int j = 0; j < ref->height(); j++)
        {
            //获得要评估的图像和参考图的每个像素点
            squareError+=pow((qRed(ref->pixel(i, j))-qRed(img->pixel(i, j))), 2);
        }
    }
    squareError/=ref->width()*ref->height();
    return squareError;
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
