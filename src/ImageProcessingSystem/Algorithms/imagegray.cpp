#include "imagegray.h"
#include "imagtranslate.h"

#include "fileoperation.h"

#include "imagesegmentation.h"


#include <QDebug>
#include <QMainWindow>
#include <math.h>

ImageGray::ImageGray()
{

}


//传入一个 QImage 对象，返回一个 QImage 指针
QImage * ImageGray::colorToGrey(QImage &image)
{
    int width = 0;
    int height = 0;
    //得到一个从左到右，从上到下遍历的RGB像素点QList
    QList<QRgb> * rgbList =  ImagTranslate::imageToList(image, width, height);
    image.convertToFormat(QImage::Format_ARGB32);
    // 循环遍历QList 进行像素点的操作，然后对Image 对象进行逐个像素点的赋值
    for(int i = 0; i < width * height; i++){
        QRgb pixel = rgbList->at(i);
        int Red = qRed(pixel);
        int Green = qGreen(pixel);
        int Blue = qBlue(pixel);
        int Grey = 0.3 * Red + 0.59 * Green + 0.11 * Blue;
        QRgb newPixel = qRgb(Grey, Grey, Grey);
        // i % width 得到目前像素点的列值，i /width 得到当前像素点的 行值
        image.setPixel(i / height , i % height, newPixel);
    }
    delete rgbList;
    return &image;
}

QImage *ImageGray::GrayToColor(QImage &image)
{

}


// 图片负相处理
QImage *ImageGray::negetiveImage(QImage &image)
{
    image.convertToFormat(QImage::Format_ARGB32);

    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            int Gray = qRed(image.pixel(i, j));
            QRgb newPixel = qRgb(255 - Gray, 255 - Gray, 255 - Gray);
            image.setPixel(i, j, newPixel);
        }
    }

    return &image;
}


//二值化
QImage *ImageGray::binaryzation(QImage &image, int keyValue)
{
    image.convertToFormat(QImage::Format_ARGB32);

    keyValue = getKeyValueHist(&image);

    qDebug() << "KeyValue" << keyValue;

    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            int Gray = qRed(image.pixel(i, j));
            QRgb newPixel;
            if( Gray >= keyValue){
                newPixel = qRgb(255, 255, 255);
            }else{
                newPixel = qRgb(0, 0, 0);
            }
            image.setPixel(i, j, newPixel);
        }
    }
    return &image;
}

// 线性变换
QImage *ImageGray::linearStretch(QImage &image)
{
    QImage * lineImage = new QImage(image.width(), image.height(), QImage::Format_RGB888);
    QVector<int> map(256);

    float k = 0.3;
    int d = 0.5;

    for(int i = 0; i < 256; i++){
        map[i] = int(i * k + d);
        if(map[i] > 255){
            map[i] = 255;
        }
        if(map[i] < 0){
            map[i] = 0;
        }
    }

    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            int gray = qRed(image.pixel(i, j));

            QRgb newPixel = qRgb(map[gray], map[gray], map[gray]);
            lineImage->setPixel(i, j, newPixel);
        }
    }

    return lineImage;

}

// 指数变换
QImage *ImageGray::exponentialStretch(QImage &image)
{
    QImage * expImage = new QImage(image.width(), image.height(), QImage::Format_RGB888);
    QVector<int> map(256);

    float c = 1.0 / 255;
    float r = 2;

    for(int i = 0; i < 256; i++){
        float temp = pow((c * i), r);

        if(temp > 1){
            map[i] = 1 * 255;
        }else if(temp < 0){
            map[i] = 0;
        } else {
            map [i] = int(temp * 255 + 0.5);
        }

    }

    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            int gray = qRed(image.pixel(i, j));

            QRgb newPixel = qRgb(map[gray], map[gray], map[gray]);
            expImage->setPixel(i, j, newPixel);
        }
    }

    return expImage;

}

// 对数变换
QImage *ImageGray::logarithmicStretch(QImage &image)
{

    //c*log2(1 + v*src_img)/log2(v+1)
    QImage * logImage = new QImage(image.width(), image.height(), QImage::Format_RGB888);
    QVector<int> map(256);

    int  v = 50;

    for(int i = 0; i < 256; i++){
        float temp = log2(1 + v * (i * 1.0 / 255)) / log2(v + 1);
        if(temp > 1){
            map[i] = 1 * 255;
        }else if(temp < 0){
            map[i] = 0;
        } else {
            map [i] = int(temp * 255 + 0.5);
        }

    }


    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            int gray = qRed(image.pixel(i, j));

            QRgb newPixel = qRgb(map[gray], map[gray], map[gray]);
            logImage->setPixel(i, j, newPixel);
        }
    }

    return logImage;
}


// 绘制直方图，需要接受一个灰度表示的图片，返回一张代表灰度分布的直方图
QImage * ImageGray::plotHistogram(QImage &image)
{

    // 获取灰度数据
    QVector<int>  histgram = countGrayHistogram(&image);

    QImage * grayHistgramImage = drawHistogram(histgram);


    return grayHistgramImage;
}

// 均衡直方图的映射，然后返回经过映射后的图片
QImage * ImageGray::balanceHistogram(QImage &image)
{
    QImage * blanceHist = new QImage(image.width(), image.height(), QImage::Format_RGB888);


    std::vector<int> grayCount = countGrayHistogram(&image).toStdVector();

    std::vector<int> culmCountZero(256);

    int numPixel = image.width() *image.height();

    culmCountZero[0] = 1.0 * grayCount[0] / numPixel * 255;
    int sum = grayCount[0];
    // 得到均衡直方图
    for(int i = 1; i < 256; i++){
        sum += grayCount[i];
        culmCountZero[i] = 1.0 * sum /numPixel * 255;
    }
    // 对图片的灰度进行重新映射
    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            int Red = qRed(image.pixel(i, j));
            QRgb newPixel = qRgb(culmCountZero[Red], culmCountZero[Red], culmCountZero[Red]);
            blanceHist->setPixel(i, j, newPixel);
        }
    }

//    FileOperation::saveAs(*blanceHist);

    return blanceHist;

}


// 接受一个灰度图片的指针，并且将统计此张图片的灰度值分布情况
QVector<int> ImageGray::countGrayHistogram(QImage *image)
{
    QVector<int> histgram(256);

    for (int i = 0; i < image->width(); i++){
        for(int j = 0; j < image->height(); j++){
            QRgb pixel = image->pixel(i, j);
            int Red = qRed(pixel);
            histgram[Red] ++;
        }
    }
    return histgram;
}


// 绘制指定的直方图
QImage *ImageGray::drawHistogram(QVector<int> grayHist)
{
    QImage * hist = new QImage(768, 512, QImage::Format_RGB888);
    std::vector<int> sortcount = grayHist.toStdVector();
    std::sort(sortcount.begin(),sortcount.end());
    int maxcount = sortcount[sortcount.size()-1];

    // 绘制直方图
    QPainter p(hist);
    hist->fill(qRgb(255, 255, 255));

    // 设置原点为左下角顶点（默认为左上角顶点）
    p.translate(0, hist->height());

    int wid=hist->width();
    int hei=hist->height();
    p.drawLine(10, -10, wid - 10, -10);// 横轴
    p.drawLine(10, -10, 10, -hei + 10);//纵轴

    // 得到步长
    float xstep = float(wid - 20) / 256;
    float ystep = float(hei - 20) / maxcount;

    for(int i = 0; i < 256; i++)
    {
        QColor color(i, 255-i, 0);

        // pen 设置呼出的形状的边， brush 则负责填充画出的图形
        p.setBrush(color);
        p.setPen(color);
        // 画出矩形
        p.drawRect(10 + i * xstep, -10, xstep, -10 - ystep * (grayHist[i]));

        // 如果i= 32 的倍数，或者255 则，在下方画出数字
        if(i % 32 == 0 || i==255)
        {
            // 第一个参数为数字的左下角的坐标，第二个为需要画出的字符串
            p.drawText(QPointF(10 + (i - 0.5) * xstep, 0), QString::number(i));
        }
    }

    // 存储直方图
//      FileOperation::saveAs(*hist);
    return hist;
}

// 得到二值化 的 (平均）阀值
int ImageGray::getKeyValue(QImage *image)
{
    QVector<int> histgram = countGrayHistogram(image);

    int sum = 0;
    for(int i = 0; i < 256; i++){
        sum += (i * histgram[i]);
    }

    int keyValue = sum / (image->width() * image->height());
    return keyValue;
}

// 通过得到直方图的两个峰值，然后得到两个峰值之间的低谷值为阀值
int ImageGray::getKeyValueHist(QImage *image)
{
    QVector<int> histgram = countGrayHistogram(image);


    int indexMax = 0, indexSecondMax = 0;
    int max = histgram[0], secondMax = 0;
    for(int i = 1; i < 256; i++){
        if(histgram[i] >= max){
            secondMax = max;
            max = histgram[i];
            indexSecondMax = indexMax;
            indexMax = i;
        }else if(histgram[i] > secondMax && histgram[i] < max)
        {
            secondMax = histgram[i];
            indexSecondMax = i;
        }else{
            continue;
        }

    }


    if(indexMax < indexSecondMax){
        int temp;
        temp = indexMax;
        indexMax = indexSecondMax;
        indexSecondMax = temp;
    }

     int keyValue = (indexMax  + indexSecondMax) / 2 + 0.5;
     return keyValue;

//    int keyValue = histgram[indexSecondMax];
//    int indexKeyValue = indexSecondMax;
//    for(int i = indexSecondMax; i < indexMax; i++){
//        if(histgram[i] < keyValue){
//            keyValue = histgram[i];
//            indexKeyValue = i;
//        }
//    }

//    return indexKeyValue;
}





























