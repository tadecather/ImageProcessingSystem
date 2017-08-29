#include "grayscommand.h"

/*
 * 1. 灰度化
 * 2. 灰色转彩色
 * 3. 负相
 * 4. 二值化
 * 5. 线性变换
 * 6. 指数变换
 * 7. 对数变换
 * 8. 绘制直方图
 * 9. 直方图均衡
 */


GraysCommand::GraysCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab,
                            int index, int commandIndex,int args1,int args2)
{
    switch (commandIndex) {
    case 1:
        name = new QString("灰度化");
        break;
    case 2:
        name = new QString("灰色转彩色");
        break;
    case 3:
        name = new QString("负相");
        break;
    case 4:
        name = new QString("二值化");
        break;
    case 5:
        name = new QString("线性变换");
        break;
    case 6:
        name = new QString("指数变换");
        break;
    case 7:
        name = new QString("对数变换");
        break;
    case 8:
        name = new QString("绘制直方图");
        break;
    case 9:
        name = new QString("直方图均衡");
        break;
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

    this->args1 = args1;
    this->args2 = args2;

    this->mainTab = mainTab;
    this->index = index;
    this->commandIndex = commandIndex;
}

//每个命令的firstTime判断是为了区分下方label和上面菜单做的
void GraysCommand::redo()
{
    int comIndex = getCommandIndex();
    if(firstTime)
    {
        switch (comIndex) {
        case 1:
            this->imageAfter = ImageGray::colorToGrey(this->imageAfter);
            break;
        case 2:
        //预留
            break;
        case 3:
            this->imageAfter = ImageGray::negetiveImage(this->imageAfter);
            break;
        case 4:
            this->imageAfter = ImageGray::binaryzation(this->imageAfter, this->args1);
                break;
        case 5:
            this->imageAfter = ImageGray::linearStretch(this->imageAfter, this->args1, this->args2);
            break;
        case 6:
            this->imageAfter = ImageGray::exponentialStretch(this->imageAfter, this->args1, this->args2);
            break;
        case 7:
            this->imageAfter = ImageGray::logarithmicStretch(this->imageAfter, this->args1);
            break;
        case 8:
            this->imageAfter = ImageGray::plotHistogram(this->imageAfter);
            break;
        case 9:
            this->imageAfter = ImageGray::balanceHistogram(this->imageAfter);
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

void GraysCommand::undo()
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

int GraysCommand::getCommandIndex()
{
    return this->commandIndex;
}


