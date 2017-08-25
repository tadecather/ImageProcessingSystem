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
    this->scaleRatio = 1;
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setStyleSheet(QString::fromUtf8("border:2px solid gray"));
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
    this->scaleRatio = 1;
    this->setDragMode(QGraphicsView::ScrollHandDrag);
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
    delete scene;
    scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(*image));
    this->setScene(scene);
    this->show();
}

//展示一行“然而什么也没有”的字
void ImageDisplay::showNULL()
{
    if(scene != NULL)
        delete scene;
    this->scene = new QGraphicsScene;
    //scene->addText("然而什么也没有",QFont("Microsoft YaHei", 12, QFont::Normal));
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
    if(image != NULL)
    {
        if(this->image != NULL)
            delete this->image;
        this->image = new QImage(*image);
        this->updateImage();
    }
    else
    {
        if(this->image != NULL)
            delete this->image;
        this->image = NULL;
        this->showNULL();
    }

}

//缩放view内的图片至合适大小
void ImageDisplay::scaleToView(int viewWidth, int viewHeight)
{
    //小图就别放大了撒
    if(this->image->width()<viewWidth && this->image->height()<viewHeight)
        return;

    double dx = (double)viewWidth/(double)this->image->width();
    double dy = (double)viewHeight/(double)this->image->height();

    //如果缩放过了
    if(dx == scaleRatio || dy == scaleRatio)
    {
        return;
    }

    this->resetTransform();
    if(image->width() >= image->height())
    {
        //按宽度缩放
        this->scaleRatio = dx;
        this->scale(dx, dx);
        this->show();
    }
    else
    {
        //按高度缩放
        this->scaleRatio = dy;
        this->scale(dy, dy);
        this->show();
    }
}

//鼠标按下的时间，内timer用于区分单击双击，建议值200到300
void ImageDisplay::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
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
        this->setStyleSheet(QString::fromUtf8("border:2px solid black"));
    else
        this->setStyleSheet(QString::fromUtf8("border:2px solid gray"));
}

//初始化右键菜单
void ImageDisplay::createMenuActions()
{
    menu = new QMenu;
    newTabAction = new QAction("创建新选项卡", this);
    connect(newTabAction, &QAction::triggered, this, &ImageDisplay::emitNewTabSlot);
    setReferenceAction = new QAction("设为参考图", this);
    connect(setReferenceAction, &QAction::triggered, this, &ImageDisplay::emitSetReferenceSlot);
    assessQualityAction = new QAction("图像质量评价", this);
    connect(assessQualityAction, &QAction::triggered, this, &ImageDisplay::emitAssessQualitySlot);

}

//设置右键菜单内容
void ImageDisplay::contextMenuEvent(QContextMenuEvent *event)
{
    menu->clear();
    menu->addAction(newTabAction);
    menu->addAction(setReferenceAction);
    menu->addAction(assessQualityAction);
    menu->exec(QCursor::pos());
}

void ImageDisplay::wheelEvent(QWheelEvent* event)
{
    if(event->delta()<0)
    {
        if(scaleRatio <= 0.1)
            return;
        this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        this->scale(0.93, 0.93);
        scaleRatio-=0.07;
    }
    if(event->delta()>0)
    {
        if(scaleRatio >= 5)
            return;
        this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        this->scale(1.07, 1.07);
        scaleRatio+=0.07;
    }
}

double ImageDisplay::getScaleRatio()
{
    return this->scaleRatio;
}

void ImageDisplay::setScaleRatio(double s)
{
    this->scaleRatio = s;
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

//对当前图片判空，然后发射“设置这张图片为参考图”的signal
void ImageDisplay::emitSetReferenceSlot()
{
    if(this->image != NULL)
    {
        emit setReferenceSignal();
        return;
    }
    QMessageBox::warning(this, "错误", "参考图片不能为空");
}

//对当前图片判空，然后发射“评估这张图片”的signal
void ImageDisplay::emitAssessQualitySlot()
{
    if(this->image != NULL)
    {
        emit assessQualitySignal();
        return;
    }
    QMessageBox::warning(this, "错误", "评估图片不能为空");
}
