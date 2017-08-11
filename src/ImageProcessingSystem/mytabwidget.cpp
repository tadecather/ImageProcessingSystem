#include "mytabwidget.h"

//当前有几个打开Tab标签
int MyTabWidget::number = -1;

//空标签内容
MyTabWidget::MyTabWidget(QWidget *parent):QTabWidget(parent)
{
    //显示关闭按钮并连接槽函数
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTabSlot(int)));
}

//现无用
MyTabWidget::MyTabWidget(QWidget *parent, QImage *image):QTabWidget(parent)
{

    //初始化TabContentVector（用于存放每个Tab的内容）以及第一个元素
    TabContent* initContent = new TabContent(this, image);
    this->contentVec.push_back(initContent);

    //初始化第一个标签，此时不增加静态变量的值，因为从0开始
    this->addTab(contentVec[0], "Label");

    //连接newTabSignal信号与增加Ta槽函数
    connect(initContent->getImageDisplayL(), &ImageDisplay::newTabSignal, this, &MyTabWidget::addTabSlot);
    connect(initContent->getImageDisplayR(), &ImageDisplay::newTabSignal, this, &MyTabWidget::addTabSlot);

    //显示关闭按钮并连接槽函数
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTabSlot(int)));
}

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
    //将此TabContent推入contentVec
    this->contentVec.push_back(content);
    //增加静态变量的值
    MyTabWidget::incNumber();

    this->addTab(contentVec[MyTabWidget::number], "Label");
    //连接新建标签页内TabContent内两个imagedisplay的newTabSignal信号与增加Tab槽函数
    connect(content->getImageDisplayL(), &ImageDisplay::newTabSignal, this, &MyTabWidget::addTabSlot);
    connect(content->getImageDisplayR(), &ImageDisplay::newTabSignal, this, &MyTabWidget::addTabSlot);
}

//程序打开时的初始tab，左边ImageDisplay为空
bool MyTabWidget::isNullInitTab()
{
    if(this->imageDisplayL->isNULL())
        return true;
    return false;
}

void MyTabWidget::setLeftImage(QImage *image)
{
    imageDisplayL->setImage(image);
}

void MyTabWidget::setRightImage(QImage *image)
{
    imageDisplayR->setImage(image);
}

void MyTabWidget::incNumber()
{
    MyTabWidget::number++;
}

void MyTabWidget::decNumber()
{
    MyTabWidget::number--;
}

//关闭一个Tab标签页
void MyTabWidget::closeTabSlot(int index)
{
    this->widget(index)->deleteLater();
    contentVec.erase(contentVec.begin() + index);
    contentVec[index] = NULL;
    MyTabWidget::decNumber();
}

//增加Tab槽函数
void MyTabWidget::addTabSlot()
{
    ImageDisplay* sender = (ImageDisplay*)QObject::sender();
    this->newTab(sender->getImage());
}

