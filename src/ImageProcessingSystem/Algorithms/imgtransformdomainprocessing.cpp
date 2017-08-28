#include "imgtransformdomainprocessing.h"

#include<QColor>

imgTransformdomainprocessing::imgTransformdomainprocessing()
{
    
}

void imgTransformdomainprocessing::imgCopy(const QImage &src, QImage &newImg)
{
    for(int i = 0;i<src.height();++i)
    {
        QRgb * line = (QRgb *)src.scanLine(i);
        QRgb * newline = (QRgb *)newImg.scanLine(i);
        memcpy(newline,line,src.bytesPerLine());
    }
}




//将图片设置有效，放在内部调用
QImage *imgTransformdomainprocessing::imgSetValidPic(QImage *img)
{
    int a = (img->width()%2)*2+(img->height()%2);
    //原图符合要求a=0;
    //原图宽度符合要求，高度不符合要求,a=1;
    //原图宽度不符合要求，高度符合要求,a=2;
    //原图的宽和高都不符合要求，a=3;

    QImage * newImg;
    QRgb * line;
    QRgb * newline;
    switch (a) {
    case 0:
        newImg = new QImage(img->width(),img->height(),QImage::Format_RGB32);
        imgCopy(*img,*newImg);
        delete img;
        img = NULL;
        return newImg;
        break;
    case 1:
        newImg = new QImage(img->width(),img->height()+1,QImage::Format_RGB32);
        imgCopy(*img,*newImg);
        line = (QRgb *)img->scanLine(img->height()-1);
        newline = (QRgb *)newImg->scanLine(newImg->height()-1);
        memcpy(newline,line,img->bytesPerLine());
        delete img;
        img = NULL;
        return newImg;
        break;
    case 2:
        newImg = new QImage(img->width()+1,img->height(),QImage::Format_RGB32);
        imgCopy(*img,*newImg);
        for(int i = 0;i<img->height();++i)
        {
            QRgb rgb = img->pixel(img->width()-1,i);
            newImg->setPixel(newImg->width()-1,i,rgb);
        }
        delete img;
        img = NULL;
        return newImg;
        break;
    case 3:
        newImg = new QImage(img->width()+1,img->height()+1,QImage::Format_RGB32);
        imgCopy(*img,*newImg);
        line = (QRgb *)img->scanLine(img->height()-1);
        newline = (QRgb *)newImg->scanLine(newImg->height()-1);
        memcpy(newline,line,img->bytesPerLine());
        for(int i = 0;i<img->height();++i)
        {
            QRgb rgb = img->pixel(img->width()-1,i);
            newImg->setPixel(newImg->width()-1,i,rgb);
        }
        QRgb rgb = img->pixel(img->width()-1,img->height()-1);
        newImg->setPixel(newImg->width()-1,newImg->height()-1,rgb);
        delete img;
        img = NULL;
        return newImg;
        break;
    }
}
    //先将图片复制一遍，除了第一个不需要复制


void imgTransformdomainprocessing::haarWaveletTransform( vector<vector<float> > &tmp)
{
    int  newHeight = tmp.size();
    int  newWidth  = tmp.at(1).size();
//    qDebug()<<"newHeight:"<<newHeight<<"newWidth:"<<newWidth;
    vector<vector<float>> ltmp = tmp;
    for(int i =0;i<newWidth;++i)
    {
        for(int j=0;2*j<newHeight;++j)
        {
            //tmp.at(a).at(b)
            //a表示行，b表示列，a行b列
            ltmp[j][i]             = (tmp[2*j][i]+tmp[2*j+1][i])/2;
            ltmp[j+newHeight/2][i] = (tmp[2*j][i]-tmp[2*j+1][i])/2;
        }
    }
    //对列进行哈尔小波变换
    for(int i = 0;i < newHeight;++i)
    {
        for(int j = 0;2*j<newWidth;++j){
            tmp[i][j]              = (ltmp[i][2*j]+ltmp[i][2*j+1])/2;
            tmp[i][j+newWidth/2]   = (ltmp[i][2*j]-ltmp[i][2*j+1])/2;
        }
    }
}

void imgTransformdomainprocessing::haarWaveletTransformInversion(vector<vector<float> > &tmp)
{
    int height = tmp.size();
    int width  = tmp.at(1).size();
    vector<vector<float>> ltmp =tmp;
    for(int i = 0;2*i < height;++i)
    {
        for(int j = 0;j<width;++j){
            ltmp[2*i][j]   = tmp[i][j]+tmp[i+height/2][j];
            ltmp[2*i+1][j] = tmp[i][j]-tmp[i+height/2][j];
        }
    }
   for(int i = 0;i < height;++i)
   {
       for(int j = 0;2*j<width;++j){
           tmp[i][2*j]   = ltmp[i][j]+ltmp[i][j+width/2];
           tmp[i][2*j+1] = ltmp[i][j]-ltmp[i][j+width/2];
       }
   }

}

//高频系数置零
void imgTransformdomainprocessing::imgSetWHFCoefficientZero(QImage *img, int &count)
{
    int height = img->height(),
        width = img->width();
    int saveHeight = height/pow(2,count),
        saveWidth  = width/pow(2,count);
    vector<vector<float>> tmp;
    for(int i = 0;i < saveHeight;++i)
    {
        vector<float> oneline;
        QRgb *line = (QRgb*)img->scanLine(i);
        for(int j =0;j<saveWidth;++j)
        {
            oneline.push_back((float)qRed(*(line+j)));
        }
        for(int j =saveWidth;j<width;j++){
            oneline.push_back((float)0);
        }
        tmp.push_back(oneline);
    }
    for(int i = saveHeight;i < height;++i)
    {
         vector<float> oneline;
         for(int j =0;j<width;++j)
         {
             oneline.push_back((float)0);
         }
         tmp.push_back(oneline);
    }
   ImagTranslate::vector2GreyImage(tmp,*img);

}

void imgTransformdomainprocessing::imgHardThreshold(QImage *img, int &count, int lambda)
{

    //这里直接对矩阵操作 所以不调用imagetranslate的函数
    //    λ范围在0~255之间
    int height = img->height(),
        width = img->width();
    int saveHeight = height/pow(2,count),
        saveWidth  = width/pow(2,count);
    vector<vector<float>> tmp;
    for(int i = 0;i < saveHeight;++i)
    {
        vector<float> oneline;
        QRgb *line = (QRgb*)img->scanLine(i);
        for(int j =0;j<saveWidth;++j)
        {
            oneline.push_back((float)qRed(*(line+j)));
        }
        for(int j =saveWidth;j<width;j++){
            //系数的值的绝对值大于阈值，则返回，否则返回0
            oneline.push_back(
                         abs(qRed(*(line+j)))>lambda?qRed(*(line+j)):0
                        );
        }
        tmp.push_back(oneline);
    }
    for(int i = saveHeight;i < height;++i)
    {
         vector<float> oneline;
         QRgb *line = (QRgb*)img->scanLine(i);
         for(int j =0;j<width;++j)
         {
             oneline.push_back(
                         abs(qRed(*(line+j)))>lambda?qRed(*(line+j)):0
                         );
         }
         tmp.push_back(oneline);
    }

    ImagTranslate::vector2GreyImage(tmp,*img);
}
/*
 * 文献材料
 * 非线性软阈值法
 *    T = σ*sqrt(2logN)
 * 或者T = 0.3*σ*sqrt(2logN)
 * 或者T = σ*sqrt(2logN/n)
 * 或者T = 3*σ;
 * 其中σ=MED/0.6745，N为信号采样点数
 * 具体实现方法参见Donoho Johnstone关于提出使用小波系数估计噪声方差的公式
 *
 * 这里考虑实现困难程度，采用普通软阈值法
 * /
 * */
void imgTransformdomainprocessing::imgSoftThreshold(QImage *img, int &count, int lambda)
{
    int height = img->height(),
        width = img->width();
    int saveHeight = height/pow(2,count),
        saveWidth  = width/pow(2,count);
    vector<vector<float>> tmp;
    for(int i = 0;i < saveHeight;++i)
    {
        vector<float> oneline;
        QRgb *line = (QRgb*)img->scanLine(i);
        for(int j =0;j<saveWidth;++j)
        {
            oneline.push_back((float)qRed(*(line+j)));
        }
        for(int j =saveWidth;j<width;j++){
            //系数的值的绝对值大于阈值，则返回，否则返回0
            oneline.push_back(
                         abs(qRed(*(line+j)))>lambda?
                                (qRed(*(line+j))>0?qRed(*(line+j))-lambda:qRed(*(line+j))+lambda)
                                    :0
                        );
        }
        tmp.push_back(oneline);
    }
    for(int i = saveHeight;i < height;++i)
    {
         vector<float> oneline;
         QRgb *line = (QRgb*)img->scanLine(i);
         for(int j =0;j<width;++j)
         {
             oneline.push_back(
                         abs(qRed(*(line+j)))>lambda?
                                (qRed(*(line+j))>0?qRed(*(line+j))-lambda:qRed(*(line+j))+lambda)
                                    :0
                         );
         }
         tmp.push_back(oneline);
    }
    ImagTranslate::vector2GreyImage(tmp,*img);
}

QImage * imgTransformdomainprocessing::imgHaar(QImage *img, int times, int &count)
{
    img = imgSetValidPic(img);
    vector<vector<float>> tmp;
    ImagTranslate::greyImage2Vector(*img,tmp);
    for(int i=0;i<times;++i)
    {
        haarWaveletTransform(tmp);
        ++count;
    }
     ImagTranslate::vector2GreyImage(tmp,*img);
     return img;
}

void imgTransformdomainprocessing::imgHaarInversion(QImage *img, int &count)
{
      vector<vector<float>> tmp;
      ImagTranslate::greyImage2Vector(*img,tmp);
      for(;count>0;)
      {
          haarWaveletTransformInversion(tmp);
          count--;
      }
      ImagTranslate::vector2GreyImage(tmp,*img);
}



