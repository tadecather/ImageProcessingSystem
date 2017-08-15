#include "negetivecommand.h"

NegetiveCommand::NegetiveCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index)
{
    name = new QString("反相");

    this->imageLeft = new QImage(*imageLeft);
    //this->imageRight = imageRight;
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
}

void NegetiveCommand::redo()
{
    //处理
    if(this->imageRight == NULL)
    {
        //处理左，结果放到右
        ImageGray::negetiveImage(*imageAfter);
        mainTab->setImage(index, 1, imageAfter);
    }
    else
    {
        ImageGray::negetiveImage(*imageAfter);
        mainTab->setImage(index, 0, imageRight);
        mainTab->setImage(index, 1, imageAfter);
    }
}

void NegetiveCommand::undo()
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
