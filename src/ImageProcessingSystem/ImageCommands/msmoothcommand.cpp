#include "msmoothcommand.h"

MSmoothCommand::MSmoothCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index)
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
}



//redo方法
void MSmoothCommand::redo()
{
    //此处firstTime为bool类型变量
    //用于标识此command是否为新建（第一次执行redo）
    //因为撤销后的指令再执行"重做"操作会再次调用redo，导致处理两次
    if(firstTime)
    {
        //此处调用算法类的静态方法处理*ImageAfter
        //类似于
        //ImageGray::negetiveImage(*imageAfter);
        this->imageAfter = ImageEnhancement::MeanSmoothing(this->imageAfter);
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
void MSmoothCommand::undo()
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
