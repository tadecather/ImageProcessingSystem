#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileoperation.h"
#include "imagegray.h"

//请将include Command类写在这条注释以下，优化时全部丢到一个新建的.h中去
#include "graycommand.h"
#include "negetivecommand.h"
#include "binaryzationcommand.h"
#include "gnoisecommand.h"
//请将include Command类写在这条注释以上，优化时全部丢到一个新建的.h中去

//临时include 及时清空
#include "imageenhancement.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    recentFileList = new QStringList();
    image = NULL;

    ui->setupUi(this);
    //fileOp
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFileSlot);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFileSlot);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveAsFileSlot);
    connect(ui->actionPrint, &QAction::triggered, this, &MainWindow::printSlot);
    connect(ui->actionPrint_preview, &QAction::triggered, this, &MainWindow::printPreViewSlot);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitSlot);

    //grayOP 共9个操作
    connect(ui->actionGraying,&QAction::triggered,this,&MainWindow::graySlot);
    connect(ui->actionGray_to_Clolr,&QAction::triggered,this,&MainWindow::graySlot);
    connect(ui->actionNegetive,&QAction::triggered,this,&MainWindow::graySlot);
    connect(ui->actionBinaryzation,&QAction::triggered,this,&MainWindow::graySlot);
    connect(ui->actionLinear_Stretch,&QAction::triggered,this,&MainWindow::graySlot);
    connect(ui->actionExponential_Stretch,&QAction::triggered,this,&MainWindow::graySlot);
    connect(ui->actionLogarithmic_Stretch,&QAction::triggered,this,&MainWindow::graySlot);
    connect(ui->actionPlot_Histogram,&QAction::triggered,this,&MainWindow::graySlot);
    connect(ui->actionBalance_Histogram,&QAction::triggered,this,&MainWindow::graySlot);


    //transformation 共5个操作
    connect(ui->actionClockwise_Rotation,&QAction::triggered,this,&MainWindow::transformSlot);
    connect(ui->actionHorizontal_Inversion,&QAction::triggered,this,&MainWindow::transformSlot);
    connect(ui->actionVertical_Inversion,&QAction::triggered,this,&MainWindow::transformSlot);
    connect(ui->actionTranspose,&QAction::triggered,this,&MainWindow::transformSlot);
    connect(ui->actionAnticlockwise_Rotation,&QAction::triggered,this,&MainWindow::transformSlot);

    //Enhancement 共9个操作
    connect(ui->actionGaussian_Noise,&QAction::triggered,this,&MainWindow::enhancementSlot);
    connect(ui->actionSalt_and_Pepper_Noise,&QAction::triggered,this,&MainWindow::enhancementSlot);
    connect(ui->actionMean_Smoothing,&QAction::triggered,this,&MainWindow::enhancementSlot);
    connect(ui->actionMedian_Smoothing,&QAction::triggered,this,&MainWindow::enhancementSlot);
    connect(ui->actionWeighted_Smoothing,&QAction::triggered,this,&MainWindow::enhancementSlot);
    connect(ui->actionChoose_Mask_Smoothing,&QAction::triggered,this,&MainWindow::enhancementSlot);
    connect(ui->actionGradient_Sharpening,&QAction::triggered,this,&MainWindow::enhancementSlot);
    connect(ui->actionLaplacian_Sharpening,&QAction::triggered,this,&MainWindow::enhancementSlot);
    connect(ui->actionImage_Quality_Assessment,&QAction::triggered,this,&MainWindow::enhancementSlot);
    	
    //    TDP 共三个大模块
//    connect(ui->menuWavelet_Transform->action,&QAction::triggered,this,&MainWindow::transDomainProcessSlot);




    subMenu = new QMenu();
    FileOperation::readFromRecentFile(*recentFileList);
    FileOperation::recentFileChanged(this, *subMenu, *recentFileList);
    ui->actionRecent_file->setMenu(subMenu);

    //初始化command stack
    commandStack = new QUndoStack(this);
    QUndoView* view = new QUndoView(commandStack);
    //view->show();

    myTab = new MyTabWidget(this);
    MainWindow::setCentralWidget(myTab);

/*
    QImage *image = new QImage;
    QString fileName = QFileDialog::getOpenFileName(
                    this, "open image file",
                    ".",
                    "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
    image->load(fileName);

    MyTabWidget *tab = new MyTabWidget(this, image);
    MainWindow::setCentralWidget(tab);

    tab->newTab(image);
    tab->newTab(image);
    tab->newTab(image);

    delete image;
*/
}

MainWindow::~MainWindow()
{
    delete subMenu;
    if(image == NULL){
        delete image;
    }
    delete recentFileList;
    delete myTab;
    delete ui;
}


void MainWindow::openFileSlot()
{
    // 如果第一次打开，会打开程序所在的文件夹，如果已经打开，那么会打开上次打开的文件夹
    QString fileName;
    if(currentPath.isEmpty()){
        fileName = QFileDialog::getOpenFileName(
                        this, "open image file",
                        ".",
                        "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
    } else{
        fileName = QFileDialog::getOpenFileName(
                        this, "open image file",
                        currentPath,
                        "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
    }

    QStringList filepath = fileName.split("/");

    filepath.removeLast();

    currentPath = filepath.join("/");
    qDebug() << currentPath;

    saveFileName = fileName;
    image = FileOperation::open(fileName, *recentFileList);

    FileOperation::recentFileChanged(this, *subMenu, *recentFileList);


    //如果没有打开文件，则不会创建标签页
    if(!image == NULL){
         myTab->newTab(image);
    }


}

void MainWindow::saveFileSlot()
{
    if(myTab->widget(myTab->currentIndex()) == NULL || myTab->getFocusedImage() == NULL)
    {
        QMessageBox::information(this, "没有图片被选中", "请打开或者选择一张图片！");
        return;
    }
    image = new QImage(*(myTab->getFocusedImage()));
    //保存容易出错 于是添加对话框，使用户确认
    QMessageBox::StandardButton result = QMessageBox::question(this, "保存确认", "这将会覆盖原图，确认保存吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(result == QMessageBox::No)
        return;
    if(!FileOperation::save(*image, saveFileName)){
        QMessageBox::information(this, "Save Error", "save file error!");
    }
}

void MainWindow::saveAsFileSlot()
{
    if(myTab->getFocusedImage() == NULL)
    {
        QMessageBox::information(this, "没有图片被选中", "请打开或者选择一张图片！");
        return;
    }
    image = new QImage(*(myTab->getFocusedImage()));
    if(!FileOperation::saveAs(*image)){
        QMessageBox::information(this, "Save Error", "save file error!(1)");
    }
}

void MainWindow::printSlot()
{
    if(image == NULL){
        QMessageBox::information(this, "没有图片被选中", "请打开或者选择一张图片！");
        return;
    }

    FileOperation::print(this);

}

void MainWindow::printPreViewSlot()
{
    if(image == NULL){
        QMessageBox::information(this, "没有图片被选中", "请打开或者选择一张图片！");
        return;
    }

    if(image->isNull())
    {
            return;
    }

    QPrinter printer(QPrinter::HighResolution);
    //自定义纸张大小
    printer.setPageSize(QPrinter::Custom);
    QPixmap pixmap = QPixmap::fromImage(*image);
    printer.setPaperSize(QSizeF(pixmap.height(), pixmap.width()),
                         QPrinter::Point);
    QPrintPreviewDialog preview(&printer, this);
    preview.setMinimumSize(1000,600);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreviewSlot(QPrinter*)));
    preview.exec ();


}


void MainWindow::exitSlot(){

    FileOperation::saveRecentFile(*recentFileList);
    exit(0);
}

void MainWindow::openRecentFile(){
    QAction * subAction = (QAction *)QObject::sender();
    qDebug()  << subAction->text();
    image = FileOperation::open(subAction->text(), *recentFileList);

    myTab->newTab(image);
}


void MainWindow::clearAllRecentSlot(){
    subMenu->clear();
    recentFileList->clear();
    ui->actionRecent_file->setEnabled(false);
}


void MainWindow::printPreviewSlot(QPrinter *printerPixmap)
{
    printerPixmap->setOrientation(QPrinter::Landscape);
    //获取界面的图片
    QPixmap pixmap = QPixmap::fromImage(*image);
    QPainter painterPixmap(this);
    painterPixmap.begin(printerPixmap);
    QRect rect = painterPixmap.viewport();
    int x = rect.width() / pixmap.width();
    int y = rect.height() / pixmap.height();
    painterPixmap.scale(x, y);
    painterPixmap.drawPixmap(0, 0, pixmap);
    painterPixmap.end();
}

void MainWindow::setRecentFileEnableSlot(){
    ui->actionRecent_file->setEnabled(false);
}

//调整窗口大小后 所有图片缩放到合适大小
void MainWindow::resizeEvent(QResizeEvent *event)
{
    ImageDisplay* displayL = myTab->getImageDisplay(myTab->currentIndex(), 0);
    ImageDisplay* displayR = myTab->getImageDisplay(myTab->currentIndex(), 1);
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


void MainWindow::graySlot(){

//    示例代码
//    //此行需改消息来源
//    if(ui->actionGraying==QObject::sender())
//    {
//        if(MyTabWidget::getNumber() == -1)
//        {
//            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
//            return;
//        }
//        //此行需要改command类名
//        Color2GrayCommand* command = new Color2GrayCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex());
//        myTab->pushCurrentStack(command);
//    }

    if(ui->actionGraying==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        Color2GrayCommand* command = new Color2GrayCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex());
        myTab->pushCurrentStack(command);
    }


    if(ui->actionGray_to_Clolr==QObject::sender())
    {

    }

    if(ui->actionNegetive==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        NegetiveCommand* command = new NegetiveCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex());
        myTab->pushCurrentStack(command);
    }

    if(ui->actionBinaryzation==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        BinaryzationCommand* command = new BinaryzationCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex());
        myTab->pushCurrentStack(command);
    }

    if(ui->actionLinear_Stretch==QObject::sender())
    {
        image = ImageGray::linearStretch(*(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage()));
        myTab->setImage(0, 1, image);
        qDebug()<<"actionLinear_Stretch operation...";
    }

    if(ui->actionExponential_Stretch==QObject::sender())
    {
        image = ImageGray::exponentialStretch(*(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage()));
        myTab->setImage(0, 1, image);
        qDebug()<<"actionExponential_Stretch operation...";
    }

    if(ui->actionLogarithmic_Stretch==QObject::sender())
    {
        image = ImageGray::logarithmicStretch(*(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage()));
        myTab->setImage(0, 1, image);
        qDebug()<<"actionLogarithmic_Stretch operation...";
    }

    if(ui->actionPlot_Histogram==QObject::sender())
    {
        //test
        ImageGray::plotHistogram(*(myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage()));
    }

    if(ui->actionBalance_Histogram==QObject::sender())
    {
        //test
        image = ImageGray::balanceHistogram(*(myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage()));
        ImageGray::plotHistogram(*image);
        qDebug()<<"actionBalance_Histogram operation...";
    }

}

void MainWindow::transformSlot()
{

    if(ui->actionClockwise_Rotation==QObject::sender())
    {
        //test
        image = imagetrans::imgClockwiseRotate90(*image);
        myTab->setImage(0, 1, image);
        qDebug()<<"actiontransformation operation...";
    }
    if(ui->actionAnticlockwise_Rotation==QObject::sender())
    {
        //test
        image = imagetrans::imgAnticlockwiseRotate90(*image);
        myTab->setImage(0, 1, image);
        qDebug()<<"actiontransformation operation...";
    }
    if(ui->actionHorizontal_Inversion==QObject::sender())
    {
        image = imagetrans::imgHorizontalInversion(*image);
        myTab->setImage(0, 1, image);
        qDebug()<<"actiontransformation operation...";
    }
    if(ui->actionVertical_Inversion==QObject::sender())
    {
        image = imagetrans::imgVerticalInversion(*image);
        myTab->setImage(0, 1, image);
        qDebug()<<"actiontransformation operation...";
    }
    if(ui->actionTranspose==QObject::sender())
    {
        image = imagetrans::imgTranspose(*image);
        myTab->setImage(0, 1, image);
        qDebug()<<"actiontransformation operation...";
    }
}

void MainWindow::enhancementSlot()
{
    if(ui->actionGaussian_Noise==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        //对话框输入三个值：mu, sigma, k

        GNoiseCommand* command = new GNoiseCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex());
        myTab->pushCurrentStack(command);
    }
    if(ui->actionSalt_and_Pepper_Noise==QObject::sender())
    {

    }
    if(ui->actionMean_Smoothing==QObject::sender())
    {

    }
    if(ui->actionMedian_Smoothing==QObject::sender())
    {

    }
    if(ui->actionWeighted_Smoothing==QObject::sender())
    {

    }
    if(ui->actionChoose_Mask_Smoothing==QObject::sender())
    {

    }
    if(ui->actionGradient_Sharpening==QObject::sender())
    {

    }
    if(ui->actionLaplacian_Sharpening==QObject::sender())
    {

    }
    if(ui->actionImage_Quality_Assessment==QObject::sender())
    {

    }
}

void MainWindow::transDomainProcessSlot()
{

    if(ui->menuWavelet_Transform==QObject::sender())
    {
        qDebug()<<"width:"<<image->width()<<"height:"<<image->height();
        image = imgTransformdomainprocessing
                ::imgSetValidPic(*image);
        qDebug()<<"width:"<<image->width()<<"height:"<<image->height();
        myTab->setImage(0, 1, image);
        qDebug()<<"actiontransformation operation...";
    }
}




//Questions:
//1. 所有（静态）算法均应直接在传入的指针上进行修改，不用return

//注意，如需关联已实现的算法和mainwindow，示例已经做好（请确保算法已经实现上面的第一个question）：
//ExampleCommand类为command的示例类，只需复制代码，改改名字，添加一句实现即可
//mainwindow.cpp中，command的多重if判断区，头部也有示例，复制粘贴 改改就行



//content中的history改为qscrollarea

//新需求：每个commandlabel颜色不同，比如多种蓝色。可以全局枚举变量。
