#include "imagedisplay.h"

//初始化一个空ImageDisplay对象，QWidget *parent用于初始化其父类QGraphicsView
ImageDisplay::ImageDisplay(QWidget *parent):QGraphicsView(parent)
{
    //每个构造函数中都需初始化右键菜单
    this->createMenuActions();
    //每个构造函数中都需初始化Timer用于区分单击双击
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ImageDisplay::mouseClick);
    //用NULL初始化内容
    this->image = NULL;
    this->scene = new QGraphicsScene;
    this->showNULL();
}

//使用现有的image对象初始化一个ImageDisplay对象，QWidget *parent用于初始化其父类QGraphicsView
//注意，此构造函数不接受image对象为空，留作备用
ImageDisplay::ImageDisplay(QWidget *parent, QImage* image):QGraphicsView(parent)
{
    //每个构造函数中都需初始化右键菜单
    this->createMenuActions();
    //每个构造函数中都需初始化Timer用于区分单击双击
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ImageDisplay::mouseClick);

    this->scene = new QGraphicsScene;

    //使用参数image的拷贝构造函数构造新的QImage对象，并使指针指向它
    if(image!=NULL)
    {
        this->image = new QImage(*image);
        this->updateImage();
    }
    else
    {
        //如果传入image对象为空
    }

}

ImageDisplay::~ImageDisplay()
{
    if(this->image != NULL)
        delete image;
    scene->deleteLater();
}

//展示当前image
void ImageDisplay::updateImage()
{
    scene->addPixmap(QPixmap::fromImage(*image));
    this->setScene(scene);
    this->show();
}

//展示一行“然而什么也没有”的字
void ImageDisplay::showNULL()
{
    scene->addText("然而什么也没有",QFont("Microsoft YaHei", 12, QFont::Normal));
    this->setScene(scene);
    this->show();
}

//获得当前image指针
QImage* ImageDisplay::getImage()
{
    return this->image;
}

//使用现有image重置内部image并显示
void ImageDisplay::setImage(QImage *image)
{
    if(this->image != NULL)
        delete this->image;
    this->image = new QImage(*image);
    this->updateImage();
}

//改变内部scence的大小
void ImageDisplay::resizeScene(int x, int y)
{
    this->scene->setSceneRect(0,0,x,y);
}

//鼠标按下的时间，内timer用于区分单击双击，建议值200到300
void ImageDisplay::mousePressEvent(QMouseEvent *event)
{
    timer->start(200);
}

//双击，发射改变当前聚焦的信号，该信号目前由上一级的TabContent对象接收
void ImageDisplay::mouseDoubleClickEvent(QMouseEvent *event)
{
    timer->stop();
    emit focusOnSignal();
}

//单击
void ImageDisplay::mouseClick()
{
    timer->stop();
    //单击要做的事
}

//b为1 绘制聚焦边框；b为0 取消聚焦边框
void ImageDisplay::setFocusBorder(bool b)
{
    if(b)
        this->setStyleSheet(QString::fromUtf8("border:1px solid black"));
    else
        this->setStyleSheet(QString::fromUtf8("border:1px solid gray"));
}

//初始化右键菜单
void ImageDisplay::createMenuActions()
{
    menu = new QMenu;
    newTabAction = new QAction("创建新选项卡", this);
    connect(newTabAction, &QAction::triggered, this, &ImageDisplay::emitNewTabSlot);
}

//设置右键菜单内容
void ImageDisplay::contextMenuEvent(QContextMenuEvent *event)
{
    menu->clear();
    menu->addAction(newTabAction);
    menu->exec(QCursor::pos());
}

//发射根据当前图片新建Tab信号
void ImageDisplay::emitNewTabSlot()
{
    if(this->image != NULL)
    {
        emit newTabSignal();
        return;
    }
    QMessageBox::warning(this, "错误", "空图片无法创建新选项卡！");
}
