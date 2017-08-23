#include "mediansmoothcommand.h"

MedianSmoothCommand::MedianSmoothCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, int size)
{
    name = new QString("中值平滑");

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
void MedianSmoothCommand::redo()
{
    if(firstTime)
    {
        this->imageAfter = ImageEnhancement::MedianSmoothing(this->imageAfter, size);
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
void MedianSmoothCommand::undo()
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
