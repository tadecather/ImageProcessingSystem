#include "imgtransformdomainprocessing.h"

#include<QColor>
using namespace std;
//#include <vector>
//struct Matrix:vector<vector<int> >//使用标准容器vector做基类，需#include语句
//{
//    Matrix(int x=0,int y=0,int z=0)//初始化，默认为0行0列空矩阵
//    {
//        assign(x,vector<int>(y,z));
//    }
//    int h_size()const//常量说明不可省，否则编译无法通过
//    {
//        return size();
//    }
//    int l_size()const
//    {
//        return empty()?0:front().size();//列数要考虑空矩阵的情况
//    }
//    Matrix pow(int k);//矩阵的k次幂，用快速幂实现，k为0时返回此矩阵的单位矩阵
//};
//Matrix operator*(const Matrix &m,const Matrix &n)//常量引用避免拷贝
//{
//    if(m.l_size()!=n.h_size())return Matrix();//非法运算返回空矩阵
//    Matrix ans(m.h_size(),n.l_size());
//    for(int i=0; i!=ans.h_size(); ++i)
//        for(int j=0; j!=ans.l_size(); ++j)
//            for(int k=0; k!=m.l_size(); ++k)
//                ans[i][j]+=m[i][k]*n[k][j];
//    return ans;
//}
//Matrix Matrix::pow(int k)
//{
//    if(k==0)
//    {
//        Matrix ans(h_size(),h_size());
//        for(int i=0; i!=ans.h_size(); ++i)
//            ans[i][i]=1;
//        return ans;
//    }
//    if(k==2)return (*this)*(*this);
//    if(k%2)return pow(k-1)*(*this);
//    return pow(k/2).pow(2);
//}
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

QImage *imgTransformdomainprocessing::imgSetValidPic(const QImage &img)
{
    int a = (img.width()%2)*2+(img.height()%2);
    //原图符合要求a=0;
    //原图宽度符合要求，高度不符合要求,a=1;
    //原图宽度不符合要求，高度符合要求,a=2;
    //原图的宽和高都不符合要求，a=3;

    QImage * newImg;
    QRgb * line;
    QRgb * newline;
    switch (a) {
    case 0:
        newImg = new QImage(img.width(),img.height(),QImage::Format_RGB32);
        imgCopy(img,*newImg);
        return newImg;
        break;
    case 1:
        newImg = new QImage(img.width(),img.height()+1,QImage::Format_RGB32);
        imgCopy(img,*newImg);
        line = (QRgb *)img.scanLine(img.height()-1);
        newline = (QRgb *)newImg->scanLine(newImg->height()-1);
        memcpy(newline,line,img.bytesPerLine());
        return newImg;
        break;
    case 2:
        newImg = new QImage(img.width()+1,img.height(),QImage::Format_RGB32);
        imgCopy(img,*newImg);
        for(int i = 0;i<newImg->height();++i)
        {
            QRgb rgb = img.pixel(img.width()-1,i);
            newImg->setPixel(newImg->width()-1,i,rgb);
        }
        return newImg;
        break;
    case 3:
        newImg = new QImage(img.width()+1,img.height()+1,QImage::Format_RGB32);
        imgCopy(img,*newImg);
        line = (QRgb *)img.scanLine(img.height()-1);
        newline = (QRgb *)newImg->scanLine(newImg->height()-1);
        memcpy(newline,line,img.bytesPerLine());
        for(int i = 0;i<newImg->height();++i)
        {
            QRgb rgb = img.pixel(img.width()-1,i);
            newImg->setPixel(newImg->width()-1,i,rgb);
        }
        return newImg;
        break;
    default:
        return NULL;
        break;
    }
}
    //先将图片复制一遍，除了第一个不需要复制


QImage *imgTransformdomainprocessing::imgHaarWaveletTransform(const QImage &img)
{
    QImage * newImg = new QImage(img);
    int newHeight = newImg->height(),
            newWidth = newImg->width();
//读取图像中的像素灰度存入两层vector构成的矩阵
    vector<vector<float>> tmp;
    for(int i = 0;i < newHeight;++i)
    {
        vector<float> oneline;
        QRgb *line = (QRgb*)newImg->scanLine(i);
        for(int j =0;j< newWidth;++j)
        {
            oneline.push_back((float)qRed(*(line+j)));
        }


        //将每一行加入矩阵中
        tmp.push_back(oneline);
    }
    vector<vector<float>> ltmp = tmp;

    for(int i =0;i<newWidth;++i)
    {
        for(int j=0;2*j<newHeight;++j)
        {
            //tmp.at(a).at(b)
            //a表示行，b表示列，a行b列
            ltmp.at(j).at(i) =(tmp.at(2*j).at(i)+tmp.at(2*j+1).at(i))/2;
            ltmp.at(j+newHeight/2).at(i) = (tmp.at(2*j).at(i)-tmp.at(2*j+1).at(i))/2;
        }
    }

    vector<vector<float>> result = ltmp;
    //对列进行哈尔小波变换

    for(int i = 0;i < newHeight;++i)
    {
        for(int j = 0;2*j<newWidth;++j){
            result.at(i).at(j) = (ltmp.at(i).at(2*j)+ltmp.at(i).at(2*j+1))/2;
            result.at(i).at(j+newWidth/2) =(ltmp.at(i).at(2*j)-ltmp.at(i).at(2*j+1))/2;
        }
    }
    //再将tmp矩阵的值赋回图像
    for(int i = 0;i < newHeight;++i)
    {
        QRgb *line = (QRgb*)newImg->scanLine(i);
        for(int j =0;j < newWidth;++j)
        {
            int grey = (int) result.at(i).at(j);
            line[j] = qRgb(grey,grey,grey);
        }
    }
    return newImg;
}


