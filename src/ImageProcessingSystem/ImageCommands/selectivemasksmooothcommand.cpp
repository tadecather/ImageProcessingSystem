#include "selectivemasksmooothcommand.h"

//构造函数
SelectiveMaskSmooothCommand::SelectiveMaskSmooothCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index)
{
    name = new QString("选择性掩模平滑");

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
void SelectiveMaskSmooothCommand::redo()
{
    if(firstTime)
    {
        this->imageAfter = ImageEnhancement::SelectiveMaskSmoothing(this->imageAfter);
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
void SelectiveMaskSmooothCommand::undo()
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
