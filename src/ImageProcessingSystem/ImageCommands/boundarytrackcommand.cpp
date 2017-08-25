#include "boundarytrackcommand.h"

//构造函数
BoundaryTrackCommand::BoundaryTrackCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index)
{
    name = new QString("边界追踪");

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
}

//redo方法
void BoundaryTrackCommand::redo()
{
    if(firstTime)
    {
        imageAfter = ImageSegmentation::BoundaryTracking(imageAfter);
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
    //标记为已经过处理
    firstTime = false;
}

//undo方法
void BoundaryTrackCommand::undo()
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
