#include "tabcontent.h"

//构造两个空imagedisplay并使用image参数初始化左边的imagedisplay
TabContent::TabContent(QWidget *parent, QImage *image) : QWidget(parent)
{
    commandStack = new QUndoStack(this);
    commandHistory = new QWidget(this);

    historyLayout = new QHBoxLayout();
    commandHistory->setLayout(historyLayout);

    this->imageDisplayL = new ImageDisplay(this);
    imageDisplayL->setImage(image);

    this->imageDisplayR = new ImageDisplay(this);

    //当前聚焦的imagedispy，0左1右
    focusOn = 0;

    connect(imageDisplayL, &ImageDisplay::focusOnSignal, this, &TabContent::changeFocusImageDisplaySlot);
    connect(imageDisplayR, &ImageDisplay::focusOnSignal, this, &TabContent::changeFocusImageDisplaySlot);

    QGridLayout *layout = new QGridLayout();

    layout->addWidget(imageDisplayL, 0, 0, 1, 1);
    layout->addWidget(imageDisplayR, 0, 1, 1, 1);
    layout->addWidget(commandHistory, 1, 0, 1, 2);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(0, 2);
    layout->setRowStretch(1, 1);

    this->setLayout(layout);
}

TabContent::~TabContent()
{
    if(this->imageDisplayL != NULL)
        imageDisplayL->deleteLater();
    if(this->imageDisplayR != NULL)
        imageDisplayR->deleteLater();
    if(this->commandStack != NULL)
        commandStack->deleteLater();
}

ImageDisplay* TabContent::getImageDisplayL()
{
    return this->imageDisplayL;
}

ImageDisplay* TabContent::getImageDisplayR()
{
    return this->imageDisplayR;
}

void TabContent::setImage(int LR, QImage* image)
{
    if(LR)
    {
        //右
        this->imageDisplayR->setImage(image);
        //scale
        qDebug()<<imageDisplayR->width()<<imageDisplayR->height();
        this->imageDisplayR->scaleToView(imageDisplayR->width(), imageDisplayR->height());
        qDebug()<<"after scale";
    }
    else
    {
        //左
        this->imageDisplayL->setImage(image);
        //scale
        this->imageDisplayL->scaleToView(imageDisplayL->width(), imageDisplayL->height());
    }
}

//获取当前聚焦的ImageDisplay指针
ImageDisplay* TabContent::getFocusedImageDisplay()
{
    if(focusOn == 0)
        return imageDisplayL;
    else
        return imageDisplayR;
}

QImage* TabContent::getFocusedImage()
{
    if(focusOn == 0)
        return imageDisplayL->getImage();
    else
        return imageDisplayR->getImage();
}

//槽函数，改变当前聚焦的imagedisplay对象
void TabContent::changeFocusImageDisplaySlot()
{
    ImageDisplay* sender = (ImageDisplay*)QObject::sender();
    //左边imagedisplay聚焦
    if(sender == imageDisplayL)
    {
        this->focusOn = 0;
        imageDisplayL->setFocusBorder(1);
        imageDisplayR->setFocusBorder(0);
    }
    //右边imagedisplay聚焦
    else
    {
        this->focusOn = 1;
        imageDisplayL->setFocusBorder(0);
        imageDisplayR->setFocusBorder(1);
    }
}

void TabContent::updateCommandHistory()
{
    //重绘当前history
    //QMessageBox::information(NULL, "重绘当前history", "重绘");
    commandHistory->repaint();
    commandHistory->show();
}

int TabContent::getFocus()
{
    return this->focusOn;
}


QUndoStack* TabContent::getStack()
{
    return this->commandStack;
}


void TabContent::addLabel(QString* name)
{
    CommandLabel* label = new CommandLabel(name);
    labels.push_back(label);
    historyLayout->addWidget(label);
    commandHistory->show();
    commandHistory->repaint();
}

//删掉最后一个label
void TabContent::removeLabel()
{
    if(labels.size() == 0)
        return;
    //历史记录里删掉、vector里删掉
    historyLayout->removeWidget(labels[labels.size()-1]);
    delete labels[labels.size()-1];
    labels.erase(labels.end()-1);
    commandHistory->show();
    commandHistory->repaint();
}
