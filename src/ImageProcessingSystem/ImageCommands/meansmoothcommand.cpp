#include "meansmoothcommand.h"

MeanSmoothCommand::MeanSmoothCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, int size)
{
    name = new QString("均值平滑");

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
}



//redo方法
void MeanSmoothCommand::redo()
{
    if(firstTime)
    {
        this->imageAfter = ImageEnhancement::MeanSmoothing(this->imageAfter, size);
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
void MeanSmoothCommand::undo()
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
