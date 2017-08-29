#include "enhancementcommand.h"

/*
 * 定义命令的索引号；
 * 0 : 高斯噪声
 * 1 : 椒盐噪声
 * 2 : 均值平滑
 * 3 : 中值平滑
 * 4 : 加权平滑
 * 5 : 选择式掩模平滑
 * 6 : 梯度锐化
 * 7 : 拉普拉斯锐化
 */

EnhancementCommand::EnhancementCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index, int commandIndex, double arg1, double arg2, double arg3)
{
    switch(commandIndex){
    case commands::gNoise :
        name = new QString("高斯噪声");
        break;
    case commands::spNoise :
        name = new QString("椒盐噪声");
        break;
    case commands::meanSmooth :
        name = new QString("均值平滑");
        break;
    case commands::medianSmooth :
        name = new QString("中值平滑");
        break;
    case commands::weightedSmooth :
        name = new QString("加权平滑");
        break;
    case commands::maskSmooth :
        name = new QString("选择式掩模平滑");
        break;
    case commands::gradientSharpen :
        name = new QString("梯度锐化");
        break;
    case commands::laplacianSharpen :
        name = new QString("拉普拉斯锐化");
        break;
    }
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->arg3 = arg3;

    this->imageLeft = new QImage(*imageLeft);
    if(imageRight == NULL)
    {
        this->imageRight = NULL;
        this->imageAfter = new QImage(*imageLeft);
    }
    else
    {
        this->imageRight = new QImage(*imageRight);
        this->imageAfter = new QImage(*imageRight);
    }

    this->mainTab = mainTab;
    this->index = index;
    this->commandIndex = commandIndex;
}

void EnhancementCommand::undo()
{
    if(this->imageRight == NULL)
    {
        mainTab->setImage(index, 0, imageLeft);
        mainTab->setImage(index, 1, NULL);
    }
    else
    {
        mainTab->setImage(index, 0, imageLeft);
        mainTab->setImage(index, 1, imageRight);
    }
}

void EnhancementCommand::redo()
{
    if(firstTime)
    {
        switch(commandIndex){
        case commands::gNoise :
        {
            double mu = arg1;
            double sigma = arg2;
            double k = arg3;
            qDebug()<<mu<<sigma<<k;
            ImageEnhancement::AddGaussianNoise(imageAfter, mu, sigma, k);
            break;
        }
        case commands::spNoise :
        {
            double snr = arg1;
            ImageEnhancement::AddSaltPepperNoise(imageAfter, snr);
            break;
        }
        case commands::meanSmooth :
        {
            int meanSize = (int)arg1;
            this->imageAfter = ImageEnhancement::MeanSmoothing(this->imageAfter, meanSize);
            break;
        }
        case commands::medianSmooth :
        {
            int medianSize = (int)arg1;
            this->imageAfter = ImageEnhancement::MedianSmoothing(this->imageAfter, medianSize);
            break;
        }
        case commands::weightedSmooth :
        {
            int weightedSize = (int)arg1;
            double theta = arg2;
            this->imageAfter = ImageEnhancement::GaussianSmoothing(imageAfter, weightedSize, theta);
            break;
        }
        case commands::maskSmooth :
        {
            this->imageAfter = ImageEnhancement::SelectiveMaskSmoothing(this->imageAfter);
            break;
        }
        case commands::gradientSharpen :
        {
            int operatorNo = (int)arg1;
            double gradientMulti = arg2;
            imageAfter = ImageEnhancement::GradientSharpening(imageAfter, operatorNo, gradientMulti);
            break;
        }
        case commands::laplacianSharpen :
        {
            double lapMulti = arg1;
            imageAfter = ImageEnhancement::LaplacianSharpening(imageAfter, lapMulti);
            break;
        }
        }
    }

    if(this->imageRight == NULL)
    {
        mainTab->setImage(index, 1, imageAfter);
    }
    else
    {
        mainTab->setImage(index, 0, imageRight);
        mainTab->setImage(index, 1, imageAfter);
    }
    //置firstTime 为false
    firstTime = false;
}

