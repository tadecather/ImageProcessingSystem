#include "tdpcommand.h"


/*
 * 定义命令的索引号；
 * 0 ：哈尔小波变换
 * 1 ：哈尔小波逆变换
 * 2 ：设置高频分量为零
 * 3 ：硬阈值法
 * 4 ：软阈值法
 */

TDPCommand::TDPCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab,
                            int index, int commandIntdex,int args1,int lambda)
{
    switch (commandIntdex) {
    case 0:
        //这里args1是次数
        name = new QString("哈尔小波变换");
        this->times = args1;
        break;
    case 1:
        name = new QString("哈尔小波逆变换");
        this->waveCount = args1;
        break;
    case 2:
        name = new QString("设置高频分量为零");
        this->waveCount = args1;
        break;
    case 3:
        name = new QString("硬阈值法:"+QString::number(lambda));
        this->waveCount = args1;
        this->lambda = lambda;
        break;
    case 4:
        name = new QString("软阈值法"+QString::number(lambda));
        this->waveCount = args1;
        this->lambda = lambda;
        break;
    }
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
    this->commandIntdex = commandIntdex;
}

//每个命令的firstTime判断是为了区分下方label和上面菜单做的
void TDPCommand::redo()
{
    int comIndex = getCommandIndex();
    if(firstTime)
    {
        switch (comIndex) {
        case 0:
            //哈尔小波中arg1表示进行小波变换层数
            this->imageAfter = imgTransformdomainprocessing::imgHaar(this->imageAfter,times,waveCount);
            break;
        case 1:
            //哈尔小波逆变换中arg1
            imgTransformdomainprocessing::imgHaarInversion(this->imageAfter,waveCount);
            break;
        case 2:
            imgTransformdomainprocessing::imgSetWHFCoefficientZero(this->imageAfter,waveCount);
            break;
        case 3:
            imgTransformdomainprocessing::imgHardThreshold(this->imageAfter,waveCount,lambda);
            break;
        case 4:
             imgTransformdomainprocessing::imgSoftThreshold(this->imageAfter,waveCount,lambda);
            break;
        }
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
    //置firstTime 为false
    firstTime = false;
}

void TDPCommand::undo()
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

int TDPCommand::getCommandIndex()
{
    return this->commandIntdex;
}

int TDPCommand::getWaveCount()
{
    return this->waveCount;
}
