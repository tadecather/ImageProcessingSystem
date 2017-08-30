#include "transcommand.h"

/*
 * 0 Transpose 转置
 * 1 HorizontalInversion 水平镜像
 * 2 VerticalInversion 竖直镜像
 * 3 ClockwiseRotation 顺时针旋转
 * 4 AutoclockwiseRotation 逆时针旋转
 */
TransCommand::TransCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index,
                           int commandIndex)
{
    switch (commandIndex) {
    case Transpose:
        name = new QString("图像转置");
        break;
    case HorizontalInversion:
        name = new QString("水平镜像");
        break;
    case VerticalInversion:
        name = new QString("竖直镜像");
        break;
    case ClockwiseRotation:
        name = new QString("顺时针旋转:90°");
        break;
    case AnticlockwiseRotation:
        name = new QString("逆时针旋转:90°");
    }
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
    this->commandIntdex = commandIndex;
}
void TransCommand::redo()
{
    int comIndex = getCommandIndex();
    if(firstTime)
    {
        QImage * tmp;
        switch (comIndex) {
        case Transpose:
            tmp = this->imageAfter;
            this->imageAfter = imagetrans::imgTranspose(*tmp);
            delete tmp;
            tmp = NULL;
            break;
        case HorizontalInversion:
            tmp = this->imageAfter;
            this->imageAfter = imagetrans::imgHorizontalInversion(*tmp);
            delete tmp;
            tmp = NULL;
            break;
        case VerticalInversion:
            tmp = this->imageAfter;
            this->imageAfter = imagetrans::imgVerticalInversion(*tmp);
            delete tmp;
            tmp = NULL;
            break;
        case ClockwiseRotation:
            tmp = this->imageAfter;
            this->imageAfter = imagetrans::imgClockwiseRotate90(*tmp);
            delete tmp;
            tmp = NULL;
            break;
        case AnticlockwiseRotation:
            tmp = this->imageAfter;
            this->imageAfter = imagetrans::imgAnticlockwiseRotate90(*tmp);
            delete tmp;
            tmp = NULL;
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

void TransCommand::undo()
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


int TransCommand::getCommandIndex()
{
     return this->commandIntdex;
}
