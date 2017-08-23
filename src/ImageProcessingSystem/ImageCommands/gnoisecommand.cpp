#include "gnoisecommand.h"

//mu为均值，sigma为方差，k为系数
GNoiseCommand::GNoiseCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, double mu, double sigma, double k)
{
    name = new QString("高斯噪声");

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
    this->mu = mu;
    this->sigma = sigma;
    this->k = k;
}


//redo方法
void GNoiseCommand::redo()
{
    if(firstTime)
    {
        ImageEnhancement::AddGaussianNoise(imageAfter, mu, sigma, k);
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
    firstTime = false;
}

//undo方法
void GNoiseCommand::undo()
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
