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

