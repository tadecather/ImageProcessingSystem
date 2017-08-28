#include "weightedsmoothcommand.h"

WeightedSmoothCommand::WeightedSmoothCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index, int size, double theta)
{
    {
        //这里填写指令名称，这个名称将显示在History里，如“灰度化”
    }
    name = new QString("加权平滑");

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
    this->size = size;
    this->theta = theta;
}

//redo方法
void WeightedSmoothCommand::redo()
{
    if(firstTime)
    {
        this->imageAfter = ImageEnhancement::GaussianSmoothing(imageAfter, size, theta);
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
void WeightedSmoothCommand::undo()
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

