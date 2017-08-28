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

    referenceImage = NULL;
    assessImage = NULL;
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
//需要连接更多槽函数，参考下面的构造方法

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

    this->addTab(contentVec[MyTabWidget::number], "Label");


    //连接新建标签页内TabContent内两个imagedisplay的newTabSignal信号与增加Tab槽函数
    connect(content->getImageDisplayL(), &ImageDisplay::newTabSignal, this, &MyTabWidget::addTabSlot);
    connect(content->getImageDisplayR(), &ImageDisplay::newTabSignal, this, &MyTabWidget::addTabSlot);
    //这是设置当前图片为参考图片的connect
    connect(content->getImageDisplayL(), &ImageDisplay::setReferenceSignal, this, &MyTabWidget::setReferenceSlot);
    connect(content->getImageDisplayR(), &ImageDisplay::setReferenceSignal, this, &MyTabWidget::setReferenceSlot);
    //这是进行图像质量评估的connect
    connect(content->getImageDisplayL(), &ImageDisplay::assessQualitySignal, this, &MyTabWidget::asseccQualitySlot);
    connect(content->getImageDisplayR(), &ImageDisplay::assessQualitySignal, this, &MyTabWidget::asseccQualitySlot);
    //连接切换tab页面和tabcontent重绘history
    //connect(this, &QTabWidget::currentChanged, content, &TabContent::updateCommandHistory);
    this->setCurrentIndex(MyTabWidget::number);

    //第一次新建页面，立刻重绘选项卡左边的图片
    if(this->currentIndex() == 0)
    {
        int viewWidth = this->getImageDisplay(MyTabWidget::number, 0)->width();
        int viewHeight = this->getImageDisplay(MyTabWidget::number, 0)->height();
        this->getImageDisplay(MyTabWidget::number, 0)->scaleToView(viewWidth, viewHeight);
    }

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

TabContent* MyTabWidget::getCurrentContent()
{
    return (TabContent*)this->widget(this->currentIndex());
}

//执行一条command，并加到history里
void MyTabWidget::pushCurrentStack(ImageCommand* command)
{
    TabContent* currentTabContent = (TabContent*)this->currentWidget();

    if(this->getCurrentStack()->canRedo())
    {
        //如果做指令之前，有已undo未redo的指令，不管几条，将其label全部删掉，保证栈顶的command未undo
        //这种情况下 undoFramework会自动删掉已undo未redo的所有指令本身，因此只要删label即可
        currentTabContent->removeLabelAfterIndex(this->getCurrentStack()->index());
    }

    //push该条command，自动调用redo
    this->getCurrentStack()->push(command);

    //新建一个标签，传给tabContent进行处理，即添加到history中并显示
    CommandLabel* label = new CommandLabel(command->getName());
    //连接该标签的单击事件和doToCommand方法
    connect(label, &CommandLabel::clicked, this, &MyTabWidget::doToCommand);
    currentTabContent->addLabel(label);
}

//undo Stack栈顶的指令，并将label从history里置灰、显示
void MyTabWidget::popCurrentStack()
{
    this->getCurrentStack()->undo();
    TabContent* currentTabContent = (TabContent*)this->currentWidget();
    currentTabContent->popLabel();
}

//redo Stack栈顶的指令，并将label从history里还原成蓝色、显示
void MyTabWidget::redoCurrentStack()
{
    this->getCurrentStack()->redo();
    TabContent* currentTabContent = (TabContent*)this->currentWidget();
    currentTabContent->redoLabel();
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

//此number用于存储标签页数量，从0开始
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
    if(this->number == 0)
        return;
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

//重要槽函数
//undo/redo to 被点击的command
void MyTabWidget::doToCommand()
{
    CommandLabel* label = (CommandLabel*)QObject::sender();
    std::vector<CommandLabel*> labels = this->getCurrentContent()->getLabels();
    //该label在labels中的序号，即它对应的command在stack中的序号
    //序号：
    int commandIndex = -1;
    for(unsigned int i = 0; i < labels.size(); i++)
    {
        if(label == labels[i])
        {
            commandIndex = i;
            break;
        }
    }
    if(commandIndex == -1)
    {
        qDebug()<<"为什么 为什么不存在这条指令";
        return;
    }

    //该command有两种情况:
    //1. 未undo(蓝色)，则：从currentCommand undo至这条command的
    //判断能否undo，只需判断它在stack中的序号，即刚刚求得的commandIndex，和stack.index的大小即可
    if(commandIndex < this->getCurrentContent()->getStack()->index())
    {
        //从currentCommand undo到这
        int commandNeedToUndo = this->getCurrentContent()->getStack()->index() - commandIndex -1;
        qDebug()<<commandNeedToUndo;
        //第一条command也得支持撤销（致刚打开图片的状态）
        if(commandNeedToUndo == 0)
            this->popCurrentStack();
        for(int i = 0; i < commandNeedToUndo; i++)
        {
            this->popCurrentStack();
        }
    }
    //2. 已undo 则从currentCommand redo至这条command
    //即commandIndex >= this->getCurrentContent()->getStack()->index()
    else
    {
        int commandNeedToRedo = commandIndex - this->getCurrentContent()->getStack()->index()+1;
        for(int i = 0; i < commandNeedToRedo; i++)
        {
            this->redoCurrentStack();
        }
    }
}

void MyTabWidget::setReferenceSlot()
{
    ImageDisplay* sender = (ImageDisplay*)QObject::sender();
    //将当前图片设置为参考图片
    if(referenceImage != NULL)
        delete referenceImage;
    referenceImage = new QImage(*sender->getImage());
}

void MyTabWidget::asseccQualitySlot()
{
    ImageDisplay* sender = (ImageDisplay*)QObject::sender();
    //对当前图片进行质量评估
    if(assessImage != NULL)
        delete assessImage;
    assessImage = new QImage(*sender->getImage());
    //相对于referenceImage,对assessImage进行图片质量评估
    double mse = ImageEnhancement::ImageQualityAssessment(referenceImage, assessImage);
    if(mse == -1.0)
    {
        //图像大小不合要求
        QMessageBox::information(this, "图片大小不正确", "要评估的图像不能比原图小");
    }
    double PSNR = 10.0*log10(255*255/mse);
    QMessageBox::information(this, "result", QString("均方误差：")+QString::number(mse)+QString("<br>")+QString("峰值信噪比：")+QString::number(PSNR));
}
