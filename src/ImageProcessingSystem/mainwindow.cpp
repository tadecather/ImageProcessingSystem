#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileoperation.h"
#include "imagegray.h"
#include "graycommand.h"
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


    subMenu = new QMenu();
    FileOperation::readFromRecentFile(*recentFileList);
    FileOperation::recentFileChanged(this, *subMenu, *recentFileList);
    ui->actionRecent_file->setMenu(subMenu);

    //初始化command stack
    commandStack = new QUndoStack(this);
    QUndoView* view = new QUndoView(commandStack);
    view->show();

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

    QString fileName = QFileDialog::getOpenFileName(
                    this, "open image file",
                    ".",
                    "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
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
    if(myTab->getFocusedImage() == NULL)
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





void MainWindow::graySlot(){

    if(ui->actionGraying==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        Gray2ColorCommand* command = new Gray2ColorCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex());
        commandStack->push(command);
    }


    if(ui->actionGray_to_Clolr==QObject::sender())
    {
        commandStack->undo();
    }

    if(ui->actionNegetive==QObject::sender())
    {
        //test
        image = ImageGray::negetiveImage(*(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage()));
        myTab->setImage(0, 1, image);
        qDebug()<<"actionNegetive operation...";
    }

    if(ui->actionBinaryzation==QObject::sender())
    {
        image = ImageGray::binaryzation(*(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage()));
        myTab->setImage(0, 1, image);
        qDebug()<<"actionBinaryzation operation...";
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


//两个问题
//1. save的文件不能再次打开，而saveas的可以
//2. 执行打开时，希望能记住上次的打开路径

// Question
//// 1. 第二个标签处理内容回到第一个标签内
//// 2. 双击选定直接保存图片容易覆盖原图，需要提示
//// 3. 双击选定 另存为 会直接保存原图，并不会保存选定的图片
// 4. 第二张图片灰度化负相 第一张再灰度化结果不对

//4. 新加： view中 鼠标拖动移动图片
//5. 新加： view中 按住ctrl滚轮缩放

//6. History类实现

