#include "dct.h"

#include <QDebug>
#include <math.h>

QImage *DCT::dctImage(QImage &image)
{
    int width = image.width();
    int height = image.height();


    // 得到图片的灰度表示矩阵
    QVector<QVector<double>> grayImage = getGrayImageMatrix(image);
    qDebug() <<grayImage[20][20];
    // 得到进行变换的系数矩阵
    QVector<QVector<double>> translateMatrixW = getTranslateMatrix(image.width());
    QVector<QVector<double>> translateMatrixH = getTranslateMatrix(image.height());
    QVector<QVector<double>> translateMatrixHT = matrixTranslate(translateMatrixH);

    qDebug() << translateMatrixH[20][20];
    // 得到进行变换的系数矩阵的转置

    // 进行DCT 变换（矩阵的乘法）
    QVector<QVector<double> > matrixtemp = mulityMatrix(translateMatrixW, grayImage);
    QVector<QVector<double> > matrixtemp1 = mulityMatrix(matrixtemp, translateMatrixHT);
    qDebug() << matrixtemp1.length() << matrixtemp1[0].length();
    // 返回变换后的图片
    QImage * newImage = new QImage(image.width(), image.height(), QImage::Format_RGB888);


    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            double gray = matrixtemp1[i][j];
            QRgb pixel = qRgb(gray, gray, gray);
            newImage->setPixel(i, j, pixel);
        }
    }
    return newImage;
}


// dct 变换，分块 8 * 8
QImage *DCT::dctNewImage(QImage &image)
{
//    double ** imageMatrix = new double * [];
    QVector<QVector<double>> grayImage = getGrayImageMatrix(image);

    // 将数据进行分块，传入参数为 图像灰度表示矩阵，以及分块的参数
    QVector<QVector<QVector <double>>> grayImageDivoded = getDivodedImage(grayImage, 8);

    // 获取处理系数矩阵与转置矩阵
    QVector<QVector<double>> translateMatrix = getTranslateMatrix(8);
    QVector<QVector<double>> translateMatrixT = matrixTranslate(translateMatrix);

    //矩阵相乘得到DCT 变换结果
    for(int i = 0; i < grayImageDivoded.length(); i++){
        QVector<QVector<double>> tempMatrix = mulityMatrix(translateMatrix, grayImageDivoded[i]);
        QVector<QVector<double>> tempMatrix0 = mulityMatrix(tempMatrix, translateMatrixT);
        grayImageDivoded[i] = tempMatrix0;
        if( i % 1000 == 0){
            qDebug() << i;
        }
    }

    qDebug() << grayImageDivoded[0][0];

    int newWidth = image.width() + ((8 - (image.width() % 8)) % 8);
    int newHeight = image.height() + ((8 - (image.height() % 8)) % 8);

    QImage * dctImage = new QImage(newWidth, newHeight, QImage::Format_RGB888);
    for(int i = 0; i < newWidth; i++){
        for( int j = 0; j < newHeight; j++){
               double grayDCT = grayImageDivoded[(i/8)*(newHeight/8)+j/8][i%8][j%8];
               QRgb pixel = qRgb(grayDCT, grayDCT, grayDCT);
               dctImage->setPixel(i , j, pixel);
        }
    }


    // 恢复DCT



    QImage *dctedImage = dctINewImage(grayImageDivoded);





    return dctedImage;
}

// 分块逆DCT
QImage *DCT::dctINewImage(QImage &image){

    QVector<QVector<double>> grayImage = getGrayImageMatrix(image);
    qDebug() << grayImage[1];

    QVector<QVector<QVector <double>>> grayImageDivoded = getDivodedImage(grayImage, 8);

    QVector<QVector<double>> translateMatrix = getTranslateMatrix(8);
    QVector<QVector<double>> translateMatrixT = matrixTranslate(translateMatrix);

    for(int i = 0; i < grayImageDivoded.length(); i++){
        QVector<QVector<double>> tempMatrix = mulityMatrix(translateMatrixT, grayImageDivoded[i]);
        QVector<QVector<double>> tempMatrix0 = mulityMatrix(tempMatrix, translateMatrix);
        grayImageDivoded[i] = tempMatrix0;

        if( i % 1000 == 0){
            qDebug() << i;
        }
    }

    int newWidth = image.width();
    int newHeight = image.height();


    QImage * dctImage = new QImage(newWidth, newHeight, QImage::Format_RGB888);
    for(int i = 0; i < newWidth; i++){
        for( int j = 0; j < newHeight; j++){
               double grayDCT = grayImageDivoded[(i/8)*(newHeight/8)+j/8][i%8][j%8];
               QRgb pixel = qRgb(grayDCT, grayDCT, grayDCT);
               dctImage->setPixel(i , j, pixel);
        }
    }
    return dctImage;
}


// 分块逆DCT
QImage *DCT::dctINewImage(QVector<QVector<QVector <double>>> dctData){



    QVector<QVector<double>> translateMatrix = getTranslateMatrix(8);
    QVector<QVector<double>> translateMatrixT = matrixTranslate(translateMatrix);

    for(int i = 0; i < dctData.length(); i++){
        QVector<QVector<double>> tempMatrix = mulityMatrix(translateMatrixT, dctData[i]);
        QVector<QVector<double>> tempMatrix0 = mulityMatrix(tempMatrix, translateMatrix);
        dctData[i] = tempMatrix0;

        if( i % 1000 == 0){
            qDebug() << i;
        }
    }

    int newWidth = dctData.length();
    int newHeight = dctData[0].length();


    QImage * dctImage = new QImage(newWidth, newHeight, QImage::Format_RGB888);
    for(int i = 0; i < newWidth; i++){
        for( int j = 0; j < newHeight; j++){
               double grayDCT = dctData[(i/8)*(newHeight/8)+j/8][i%8][j%8] * 255;
               QRgb pixel = qRgb(grayDCT, grayDCT, grayDCT);
               dctImage->setPixel(i , j, pixel);
        }
    }
    return dctImage;
}


// 整体逆DCT
QImage *DCT::dctIImage(QImage &image)
{
    // 得到图像的灰度表示矩阵
    QVector<QVector<double>> grayImage = getGrayImageMatrix(image);
    int width = grayImage.length();
    int height = grayImage[0].length();
    qDebug() << "GrayT" << grayImage.length() << grayImage[0].length();
    // 得到处理系数矩阵
    QVector<QVector<double>> translateMatrixW = getTranslateMatrix(width);
    QVector<QVector<double>> translateMatrixH = getTranslateMatrix(height);
    QVector<QVector<double>> translateMatrixWT = matrixTranslate(translateMatrixW);
//    qDebug() <<"TTT" <<translateMatrixW[28][17];
//    qDebug() << translateMatrixWT[17][28];

    qDebug() << "GrayT" << translateMatrixH.length() << translateMatrixH[0].length();
    qDebug() << "GrayT" << translateMatrixW.length() << translateMatrixW[0].length();

    // 进行DCT 变换（矩阵的乘法）
    QVector<QVector<double> > matrixtemp = mulityMatrix(translateMatrixWT, grayImage);
    QVector<QVector<double> > matrixtemp1 = mulityMatrix(matrixtemp, translateMatrixH);
    QImage * newImage = new QImage(image.width(), image.height(), QImage::Format_RGB888);

    qDebug() << height << width;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            double gray = matrixtemp1[i][j];
            QRgb pixel = qRgb(gray, gray, gray);
            newImage->setPixel(j, i, pixel);
        }
    }

    return newImage;

}



// 获得图片灰度矩阵
QVector<QVector<double>> DCT::getGrayImageMatrix(QImage &image)
{
    QVector<QVector<double>> * grayImage = new QVector<QVector<double>>();
    for(int i = 0; i < image.width(); i++){
        QVector<double> *subList = new QVector<double>();
        for(int j = 0; j < image.height(); j++){
            double gray = qRed(image.pixel(i,j)) * 1.0 / 255;
            subList->append(gray);
        }
        grayImage->append(*subList);
    }

    return *grayImage;
}

// 获得DCT系数矩阵为n*n
QVector<QVector<double> > DCT::getTranslateMatrix(int n)
{
     QVector<QVector<double>> * matrix= new QVector<QVector<double>>();

     for(int i = 0; i < n; i++){
         QVector<double> *subList = new QVector<double>();
         for(int j = 0; j < n; j++){
             double temp = 0;
             if(i ==0){
                temp = sqrt(1.0/n)*cos(((2*j+1)*i*M_PI)/(2*n));
             } else{
                temp = sqrt(2.0/n)*cos(((2*j+1)*i*M_PI)/(2*n));
             }
             subList->append(temp);
         }
        matrix->append(*subList);
     }
     return *matrix;
}

// 矩阵相乘
QVector<QVector<double> >  DCT::mulityMatrix(QVector<QVector<double> > matrix1, QVector<QVector<double> > matrix2)
{
    int datalengthW = matrix1.length();
    int datalengthH = matrix1[0].length();
    int datalengthK = matrix2[0].length();

    QVector<QVector<double>>  newMatrix(8, QVector<double>(8));

    for(int i = 0; i < datalengthW; i++){
        for(int j = 0; j < datalengthK; j++){
            double sum = 0;
            for(int k = 0; k < datalengthH; k++){
                sum += matrix1[i][k] * matrix2[k][j];
            }
            newMatrix[i][j] = sum;
        }
    }
    return newMatrix;
}


// 实现矩阵的转置
QVector<QVector<double> > DCT::matrixTranslate(QVector<QVector<double> > matrix)
{

    int datalengthW = matrix.length();
    int datalengthH = matrix[0].length();

    QVector<QVector<double>>  newMatrix(datalengthH, QVector<double>(datalengthW));

    for(int i = 0; i < datalengthW; i++){
        for(int j = 0; j < datalengthH; j++){
            newMatrix[j][i] = matrix[i][j];
        }
    }
    return newMatrix;
}


// 图片灰度矩阵进行划分为 n*n 的小块
QVector<QVector<QVector<double> > > DCT::getDivodedImage(QVector<QVector<double> > grayImage, int n)
{
    int width = grayImage.length();
    int height = grayImage[0].length();

    // 图像的宽 高 补为 n 的倍数，以方便划分
    int newWidth = width + ((n - (width % n)) % n);
    int newHeight = height + ((n - (height % n)) % n);

    QVector<QVector<double>> newImageMatrix(newWidth, QVector<double>(newHeight));

    // 图形矩阵进行重新赋值，超过原图部分用0补足
    for(int i = 0; i < newWidth; i++){
        for(int j = 0; j < newHeight; j++){
            if(i < width && j < height){
                newImageMatrix[i][j] = grayImage[i][j];
            } else {
                newImageMatrix[i][j] = 0;
            }
        }
    }
    QVector<QVector<QVector<double> > >  divodedImageMatrix(newWidth*newHeight/(n * n), QVector<QVector<double>>(n, QVector<double>(n)));

    int num = 0;
    for(int i = 0; i < newWidth; i = i + 8){
        for(int j = 0; j < newHeight; j= j + 8){

            for(int m = 0; m < 8; m++){
                for(int n = 0; n < 8; n++){
                    divodedImageMatrix[num][m][n]= newImageMatrix[i+m][j+n];
                }
            }
            num++;
        }
    }
    return divodedImageMatrix;
}

































