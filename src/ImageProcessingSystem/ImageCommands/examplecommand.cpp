#include "examplecommand.h"

//这是样例command的实现


//构造函数
ExampleCommand::ExampleCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index)
{
    //这里填写指令名称，这个名称将显示在History里，如“灰度化”
    name = new QString("名称");

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
void ExampleCommand::redo()
{
    //此处firstTime为bool类型变量
    //用于标识此command是否为新建（第一次执行redo）
    //因为撤销后的指令再执行"重做"操作会再次调用redo，导致处理两次
    if(firstTime)
    {
        //此处调用算法类的静态算法处理*ImageAfter
        //类似于
        //ImageGray::negetiveImage(*imageAfter);
        //如果你的算法有返回值...比如一张新图片，请用这样的调用
        //this->imageAfter = 算法类::算法(this->imageAfter);
        //并且！！在你的算法里，最后return之前，将传入的参数(其实就是这里的imageAfter)delete并赋NULL
        //这是为了防止内存泄漏，不删倒是也没什么危险，因为已经访问不到了
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
void ExampleCommand::undo()
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
