#include "spnoisecommand.h"

//构造函数
SpNoiseCommand::SpNoiseCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index, double snr)
{
    name = new QString("椒盐噪声");

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
    this->snr = snr;
    qDebug()<<snr;
}

//redo方法
void SpNoiseCommand::redo()
{
    if(firstTime)
    {
        ImageEnhancement::AddSaltPepperNoise(imageAfter, snr);
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
void SpNoiseCommand::undo()
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
