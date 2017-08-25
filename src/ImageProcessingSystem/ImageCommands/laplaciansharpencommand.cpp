#include "laplaciansharpencommand.h"

//构造函数
LaplacianSharpenCommand::LaplacianSharpenCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index, double multi)
{
    name = new QString("拉普拉斯锐化");

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
    this->multi = multi;
}

//redo方法
void LaplacianSharpenCommand::redo()
{
    if(firstTime)
    {
        imageAfter = ImageEnhancement::LaplacianSharpening(imageAfter, multi);
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
void LaplacianSharpenCommand::undo()
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
