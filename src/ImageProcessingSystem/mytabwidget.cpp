#include "mytabwidget.h"

//当前有几个打开Tab标签
int MyTabWidget::number = -1;

//空标签内容
MyTabWidget::MyTabWidget(QWidget *parent):QTabWidget(parent)
{
    commandGroup = new QUndoGroup(this);

    //显示关闭按钮并连接槽函数
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTabSlot(int)));
}

////现无用
//MyTabWidget::MyTabWidget(QWidget *parent, QImage *image):QTabWidget(parent)
//{

//    commandGroup = NULL;

//    //初始化TabContentVector（用于存放每个Tab的内容）以及第一个元素
//    TabContent* initContent = new TabContent(this, image);
//    this->contentVec.push_back(initContent);

//    //初始化第一个标签，此时不增加静态变量的值，因为从0开始
//    this->addTab(contentVec[0], "Label");

//    //连接newTabSignal信号与增加Ta槽函数
//    connect(initContent->getImageDisplayL(), &ImageDisplay::newTabSignal, this, &MyTabWidget::addTabSlot);
//    connect(initContent->getImageDisplayR(), &ImageDisplay::newTabSignal, this, &MyTabWidget::addTabSlot);

//    //显示关闭按钮并连接槽函数
//    this->setTabsClosable(true);
//    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTabSlot(int)));

//}

MyTabWidget::~MyTabWidget()
{
    //删除所有不为NULL的Tab标签的内容，注意 删除Tab时，系统自动迭代删除其内容物（调用析构函数）
    for(int i = 0; i < MyTabWidget::number; i++)
    {
        if(contentVec[i]!=NULL)
        {
            delete contentVec[i];
            contentVec[i] = NULL;
        }
    }
    MyTabWidget::number = 0;
}

//新建一个标签页
void MyTabWidget::newTab(QImage *image)
{

    //新建一个TabContent，用来初始化一个新Tab
    TabContent* content = new TabContent(this, image);

    commandGroup->addStack(content->getStack());

    //将此TabContent推入contentVec
    this->contentVec.push_back(content);

    //增加静态变量的值
    MyTabWidget::incNumber();

    //qDebug()<<contentVec[0]->width();

    this->addTab(contentVec[MyTabWidget::number], "Label");


    //连接新建标签页内TabContent内两个imagedisplay的newTabSignal信号与增加Tab槽函数
    connect(content->getImageDisplayL(), &ImageDisplay::newTabSignal, this, &MyTabWidget::addTabSlot);
    connect(content->getImageDisplayR(), &ImageDisplay::newTabSignal, this, &MyTabWidget::addTabSlot);
    //连接切换tab页面和tabcontent重绘history
    connect(this, &QTabWidget::currentChanged, content, &TabContent::updateCommandHistory);
    this->setCurrentIndex(MyTabWidget::number);

    //如果是第一次新建页面，应该立刻重绘
    if(this->currentIndex() == 0)
    {
        TabContent* currTab = (TabContent*)this->widget(this->currentIndex());

    }


    //重绘结束

    //第一次新建页面，立刻重绘选项卡左边的图片
    if(this->currentIndex() == 0)
    {
        double dx = (double)this->getImageDisplay(MyTabWidget::number, 0)->width()/(double)this->getImageDisplay(MyTabWidget::number, 0)->getImage()->width();
        this->getImageDisplay(MyTabWidget::number, 0)->scale(dx, dx);
    }
    //重绘结束

    connect(this, &QTabWidget::currentChanged, this, &MyTabWidget::scaleDisplayToView);
}

QImage* MyTabWidget::getFocusedImage()
{
    TabContent* currentTabContent = (TabContent*)this->widget(MyTabWidget::getNumber());
    return currentTabContent->getFocusedImage();
}

QUndoStack* MyTabWidget::getCurrentStack()
{
    TabContent* currentTabContent = (TabContent*)this->currentWidget();
    return currentTabContent->getStack();
}

//执行一条command，顺便加到history里
void MyTabWidget::pushCurrentStack(ImageCommand* command)
{
    this->getCurrentStack()->push(command);
    //并添加到历史列表中
    TabContent* currentTabContent = (TabContent*)this->currentWidget();
    currentTabContent->addLabel(command->getName());
}

//撤销一条指令，顺便从history里删除
void MyTabWidget::popCurrentStack()
{
    this->getCurrentStack()->undo();
    TabContent* currentTabContent = (TabContent*)this->currentWidget();
    currentTabContent->removeLabel();
}

//获得某一页的左右ImageDisplay，参数为Tab页数、左右ImageDisplay（0左1右）
ImageDisplay* MyTabWidget::getImageDisplay(int index, int LR)
{
    if(index >= 0 && index <= number)
    {
        if(LR == 0)
            return contentVec[index]->getImageDisplayL();
        else
            return contentVec[index]->getImageDisplayR();
    }
    return NULL;
}

//设置某一页的ImageDisplay，参数为Tab页数、左右ImageDisplay（0左1右）
void MyTabWidget::setImage(int index, int LR, QImage *image)
{
    if(image == NULL)
    {
        contentVec[index]->getImageDisplayR()->setImage(NULL);
        return;
    }
    if(index >= 0 && index <= number)
    {
        contentVec[index]->setImage(LR, image);
    }
}

void MyTabWidget::incNumber()
{
    MyTabWidget::number++;
}

void MyTabWidget::decNumber()
{
    MyTabWidget::number--;
}

int MyTabWidget::getNumber()
{
    return MyTabWidget::number;
}

//关闭一个Tab标签页
void MyTabWidget::closeTabSlot(int index)
{
    this->widget(index)->deleteLater();
    contentVec.erase(contentVec.begin() + index);
    //contentVec[index] = NULL;
    MyTabWidget::decNumber();
}

void MyTabWidget::scaleDisplayToView(int index)
{
    ImageDisplay* displayL = getImageDisplay(currentIndex(), 0);
    ImageDisplay* displayR = getImageDisplay(currentIndex(), 1);
    if(displayL != NULL)
    {
        if(displayL->getImage() == NULL) return;
        int viewWidth = displayL->width();
        int viewHeight = displayL->height();
        qDebug()<<viewWidth<<viewHeight;
        displayL->scaleToView(viewWidth, viewHeight);
    }
    if(displayR != NULL)
    {
        if(displayR->getImage() == NULL) return;
        int viewWidth = displayR->width();
        int viewHeight = displayR->height();
        qDebug()<<viewWidth<<viewHeight;
        displayR->scaleToView(viewWidth, viewHeight);
    }
}

//增加Tab槽函数
void MyTabWidget::addTabSlot()
{
    ImageDisplay* sender = (ImageDisplay*)QObject::sender();
    this->newTab(sender->getImage());
}

