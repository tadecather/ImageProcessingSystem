﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileoperation.h"
#include "imagegray.h"

//请将include Command类写在这条注释以下，优化时全部丢到一个新建的.h中去

#include "gnoisecommand.h"
#include "spnoisecommand.h"
#include "meansmoothcommand.h"
#include "mediansmoothcommand.h"
#include "weightedsmoothcommand.h"
#include "selectivemasksmooothcommand.h"
#include "grayscommand.h"
#include "tdpcommand.h"
#include "segmentationcommand.h"
#include "gradientsharpencommand.h"
#include "laplaciansharpencommand.h"
#include "boundarytrackcommand.h"

//请将include Command类写在这条注释以上，优化时全部丢到一个新建的.h中去


//临时include 及时清空
#include "imageenhancement.h"
#include "dct.h"
#include "imagesegmentation.h"
//请将include display类写在以下
#include "gnoiseargsdialog.h"
#include "graydialog.h"
#include "spnoiseargsdialog.h"
#include "weightedsmoothargsdialog.h"
#include "meansmoothargsdialog.h"
#include "tdpdialog.h"
#include "customedge.h"
#include "gradientsharpendialog.h"
#include "laplaciansharpendialog.h"

#include <QLabel>
#include <QPixmap>

#include "mytabwidget.h"
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


            //小波变换5个子菜单
            connect(ui->actionHaar_Wavelet,&QAction::triggered,this,&MainWindow::transDomainProcessSlot);
            connect(ui->actionHaar_Wavelet_Inversion,&QAction::triggered,this,&MainWindow::transDomainProcessSlot);
            connect(ui->actionset_whf_coeffecient_zero,&QAction::triggered,this,&MainWindow::transDomainProcessSlot);
            connect(ui->actionHard_Threshold_Method,&QAction::triggered,this,&MainWindow::transDomainProcessSlot);
            connect(ui->actionSoft_Threshold_Method,&QAction::triggered,this,&MainWindow::transDomainProcessSlot);

    connect(ui->actionDCT,&QAction::triggered,this,&MainWindow::transDomainProcessSlot);
    connect(ui->actionDCTI,&QAction::triggered,this,&MainWindow::transDomainProcessSlot);

    //  Segmentation 模块 14个操作
    connect(ui->actionOtsu_Law_Threshold_Segmentation,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionInteractive_Threshold_Segmentation,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionRobert_Operator,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionSobel_Operator,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionPrewitt_Operator,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionLaplacian_Operator,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionGauss_Laplacian_Operator,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionKrisch_Operator,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionCustom_Edges,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionRegion_Grow,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionContour_Extraction,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionBoundary_Tracking,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionHough_Transformation,&QAction::triggered,this,&MainWindow::segmentationSlot);
    connect(ui->actionHough_Transformation_Line_Detection,&QAction::triggered,this,&MainWindow::segmentationSlot);




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

    //测试代码


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

//判断当前图片是否经过灰度化
bool MainWindow::afterGray()
{
//    QUndoStack* currStack = myTab->getCurrentStack();
//    for(int i = 0; i < currStack->index(); i++)
//    {
//        ImageCommand* command = (ImageCommand*)currStack->command(i);
//        if(*(command->getName()) == "灰度化")
//            return true;
//    }
//    return false;
    QImage* image;
    //优先获取当前选项卡右边图片，为NULL则获取左边图片
    if(myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage()!=NULL)
    {
        image = myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage();
    }
    else
    {
        image = myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage();
    }

    for(int i = 0; i < image->width(); i++)
    {
        for(int j = 0; j < image->height(); j++)
        {
            if(qRed(image->pixel(i, j))==qGreen(image->pixel(i, j))&&qGreen(image->pixel(i, j))==qBlue(image->pixel(i, j)))
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

bool MainWindow::afterBin()
{
    if(!this->afterGray())
    {
        return false;
    }
    QImage* image;
    //优先获取当前选项卡右边图片，为NULL则获取左边图片
    if(myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage()!=NULL)
    {
        image = myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage();
    }
    else
    {
        image = myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage();
    }

    for(int i = 0; i < image->width(); i++)
    {
        for(int j = 0; j < image->height(); j++)
        {
            if(qRed(image->pixel(i, j))!=255||qRed(image->pixel(i, j))!=0)
            {
                continue;
            }
            else
            {
                qDebug()<<i<<j<<qRed(image->pixel(i, j));
                return false;
            }
        }
    }
    return true;
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    exitSlot();

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

    if(MyTabWidget::getNumber() == -1)
    {
        QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
        return;
    }

    if(ui->actionGraying==QObject::sender())
    {
        GraysCommand * command = new GraysCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             1);
        myTab->pushCurrentStack(command);
        return;

    }


    if(ui->actionGray_to_Clolr==QObject::sender())
    {

    }

    if(ui->actionNegetive==QObject::sender())
    {
        GraysCommand * command = new GraysCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             3);
        myTab->pushCurrentStack(command);
        return;
    }

    if(ui->actionBinaryzation==QObject::sender())
    {
    	 if(!this->afterGray())
        {
            QMessageBox::about(this, "图片不符合要求", "二值化处理需要灰度图片");
            return;
        }

        GrayDialog * dialog = new GrayDialog(this, 4);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        GraysCommand * command = new GraysCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             4,
                                            dialog->getArgs1()); // 还可以有一个参数

        myTab->pushCurrentStack(command);
        dialog->deleteLater();
        return;
    }

    if(ui->actionLinear_Stretch==QObject::sender())
    {
        GrayDialog * dialog = new GrayDialog(this, 1);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }

        GraysCommand * command = new GraysCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                                 myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                                 this->myTab,
                                                 myTab->currentIndex(),
                                                 5,
                                                 dialog->getArgs1(),
                                                 dialog->getArgs2());
        myTab->pushCurrentStack(command);
        dialog->deleteLater();
        return;
    }

    if(ui->actionExponential_Stretch==QObject::sender())
    {
        GrayDialog * dialog = new GrayDialog(this, 2);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        GraysCommand * command = new GraysCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             6,
                                              dialog->getArgs1(),
                                              dialog->getArgs2());
        myTab->pushCurrentStack(command);
        dialog->deleteLater();
        return;

    }

    if(ui->actionLogarithmic_Stretch==QObject::sender())
    {
        GrayDialog * dialog = new GrayDialog(this, 3);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        GraysCommand * command = new GraysCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             7,
                                            dialog->getArgs1());
        myTab->pushCurrentStack(command);
        dialog->deleteLater();
        return;

    }

    if(ui->actionPlot_Histogram==QObject::sender())
    {
        GraysCommand * command = new GraysCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             8); // 还可以有两个参数
        myTab->pushCurrentStack(command);
        return;
    }

    if(ui->actionBalance_Histogram==QObject::sender())
    {
        GraysCommand * command = new GraysCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             9); // 还可以有两个参数
        myTab->pushCurrentStack(command);

        QDialog * dialog = new QDialog(this);
        QImage * newImage = FileOperation::open("balanceHist.jpg", *recentFileList);

        dialog->setFixedSize(newImage->width(), image->height());
        QLabel * balancedHist = new QLabel(dialog);
        balancedHist->setPixmap(QPixmap::fromImage(*newImage));

        if( dialog->exec() == QDialog::Rejected){
            balancedHist->deleteLater();
            dialog->deleteLater();
        }


        return;
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
        GNoiseArgsDialog* dialog = new GNoiseArgsDialog(this);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        GNoiseCommand* command = new GNoiseCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex(), dialog->getMu(), dialog->getSigma(), dialog->getK());
        dialog->deleteLater();
        myTab->pushCurrentStack(command);
    }
    if(ui->actionSalt_and_Pepper_Noise==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        //对话框输入一个值：snr
        SPNoiseArgsDialog* dialog = new SPNoiseArgsDialog(this);
        //qDebug()<<dialog->getSnr();
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        SpNoiseCommand* command = new SpNoiseCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex(), dialog->getSnr());
        dialog->deleteLater();
        myTab->pushCurrentStack(command);
    }
    if(ui->actionMean_Smoothing==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        if(!this->afterGray())
        {
            QMessageBox::about(this, "需要前置条件", "一般要灰度化后才能均值平滑你知道不啦？");
            return;
        }
        MeanSmoothArgsDialog* dialog = new MeanSmoothArgsDialog(this);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        MeanSmoothCommand* command = new MeanSmoothCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex(), dialog->getSize());
        dialog->deleteLater();
        myTab->pushCurrentStack(command);
    }
    if(ui->actionMedian_Smoothing==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        if(!this->afterGray())
        {
            QMessageBox::about(this, "需要前置条件", "一般要灰度化后才能中值平滑你知道不啦？");
            return;
        }
        //中值平滑跟均值平滑一样，参数只有一个矩阵大小，因此使用均值平滑的dialog
        MeanSmoothArgsDialog* dialog = new MeanSmoothArgsDialog(this);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        MedianSmoothCommand* command = new MedianSmoothCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex(), dialog->getSize());
        dialog->deleteLater();
        myTab->pushCurrentStack(command);
    }
    if(ui->actionWeighted_Smoothing==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        if(!this->afterGray())
        {
            QMessageBox::about(this, "需要前置条件", "一般要灰度化后才能加权平滑你知道不啦？");
            return;
        }
        //对话框输入两个值：size, theta
        WeightedSmoothArgsDialog* dialog = new WeightedSmoothArgsDialog(this);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        WeightedSmoothCommand* command = new WeightedSmoothCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex(), dialog->getSize(), dialog->getTheta());
        dialog->deleteLater();
        myTab->pushCurrentStack(command);
    }
    if(ui->actionChoose_Mask_Smoothing==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        if(!this->afterGray())
        {
            QMessageBox::about(this, "需要前置条件", "一般要灰度化后才能掩模平滑你知道不啦？");
            return;
        }
        SelectiveMaskSmooothCommand* command = new SelectiveMaskSmooothCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex());
        myTab->pushCurrentStack(command);
    }
    if(ui->actionGradient_Sharpening==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        if(!this->afterGray())
        {
            QMessageBox::about(this, "图片不符合要求", "梯度锐化需要灰度图");
            return;
        }
        GradientSharpenDialog* dialog = new GradientSharpenDialog(this);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        GradientSharpenCommand* command = new GradientSharpenCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex(), dialog->getOperatorNo(), dialog->getMulti());
        dialog->deleteLater();
        myTab->pushCurrentStack(command);
    }
    if(ui->actionLaplacian_Sharpening==QObject::sender())
    {
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        if(!this->afterGray())
        {
            QMessageBox::about(this, "图片不符合要求", "拉普拉斯锐化需要灰度图");
            return;
        }
        LaplacianSharpenDialog* dialog = new LaplacianSharpenDialog(this);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        LaplacianSharpenCommand* command = new LaplacianSharpenCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex(), dialog->getMulti());
        dialog->deleteLater();
        myTab->pushCurrentStack(command);
    }
    if(ui->actionImage_Quality_Assessment==QObject::sender())
    {

    }
}


/*
 * 定义transform命令的索引号commandIndex；
 * 0 ：哈尔小波变换
 * 1 ：哈尔小波逆变换
 * 2 ：设置高频分量为零
 * 3 ：硬阈值法
 * 4 ：软阈值法
 *
 * 3，4 输入阈值后，先不压入command栈。
 */
void MainWindow::transDomainProcessSlot()
{
    if(MyTabWidget::getNumber() == -1)
    {
        QMessageBox::about(this, "请先打开图片", "没图片（负责这部分的不是粗鄙之人！）");
        return;
    }
    //小波变换5个子操作
    if(ui->actionHaar_Wavelet==QObject::sender())
    {
        TDPCommand* command = new TDPCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             0,
                                             3);//这里3可以通过对话框提取出来
        myTab->pushCurrentStack(command);
        waveCount = command->getWaveCount();
        return;
    }
    if(ui->actionHaar_Wavelet_Inversion==QObject::sender())
    {
        TDPCommand* command = new TDPCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             1,
                                             waveCount);
        myTab->pushCurrentStack(command);
        qDebug()<<"wavecount:"<<waveCount;
        return;
    }
    if(ui->actionset_whf_coeffecient_zero==QObject::sender())
    {
        TDPCommand* command = new TDPCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             2,
                                             waveCount);
        myTab->pushCurrentStack(command);
    }
    if(ui->actionHard_Threshold_Method==QObject::sender())
    {
        int lambda = -1;
        tdpDialog *tdialog = new tdpDialog(this,"threshold");
        QImage * tmp;
        //下面这么写是为了少写个mainWindow的槽函数
        if(myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage() == NULL)
        {
            tmp = new QImage(*myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage());
        }
        else
        {
            tmp = new QImage(*myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage());
        }
        while (true)
        {
            if(tdialog->exec() == QDialog::Rejected)
            {
                if(lambda != tdialog->getThreshold()){
                    lambda = tdialog->getThreshold();
                    //每一次循环复制一个新的tmp ，因为下面两个函数会对原图像造成改变
                    QImage * loopTmp = new QImage(*tmp);
                    int tmpcount = waveCount;
                    imgTransformdomainprocessing::imgHardThreshold(loopTmp,tmpcount,lambda);
                    //进行逆变换观察效果
                    imgTransformdomainprocessing::imgHaarInversion(loopTmp,tmpcount);
                    myTab->setImage(myTab->currentIndex(),1,loopTmp);
                    delete loopTmp;
                    loopTmp = NULL;
                }
                continue;
            }
            lambda = tdialog->getThreshold();
            break;
        }
        TDPCommand* command = new TDPCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             tmp,
                                             this->myTab,
                                             myTab->currentIndex(),
                                             3,
                                             waveCount,
                                             lambda);
        myTab->pushCurrentStack(command);
        tdialog->deleteLater();
    }
    if(ui->actionSoft_Threshold_Method==QObject::sender())
    {
        int lambda = -1;
        tdpDialog *tdialog = new tdpDialog(this,"threshold");
        QImage * tmp;
        //下面这么写是为了少写个mainWindow的槽函数
        if(myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage() == NULL)
        {
            tmp = new QImage(*myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage());
        }
        else
        {
            tmp = new QImage(*myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage());
        }


        while (true)
        {
            if(tdialog->exec() == QDialog::Rejected)
            {
                if(lambda != tdialog->getThreshold()){
                    lambda = tdialog->getThreshold();
                    //每一次循环复制一个新的tmp ，因为下面两个函数会对原图像造成改变
                    QImage * loopTmp = new QImage(*tmp);
                    int tmpcount = waveCount;
                    imgTransformdomainprocessing::imgSoftThreshold(loopTmp,tmpcount,lambda);
                    //进行逆变换观察效果
                    imgTransformdomainprocessing::imgHaarInversion(loopTmp,tmpcount);
                    myTab->setImage(myTab->currentIndex(),1,loopTmp);
                    delete loopTmp;
                    loopTmp = NULL;
                }
                continue;
            }
            lambda = tdialog->getThreshold();
            break;
        }
        TDPCommand* command = new TDPCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             tmp,
                                             this->myTab,
                                             myTab->currentIndex(),
                                             4,
                                             waveCount,
                                             lambda);
        myTab->pushCurrentStack(command);
        tdialog->deleteLater();
    }

    if(ui->actionDCT==QObject::sender())
    {
        TDPCommand* command = new TDPCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             5);
        myTab->pushCurrentStack(command);
    }

    if(ui->actionDCTI==QObject::sender())
    {

    }
}

//ImaegSegmentation 模块
/*
 * 0 ostu
 * 1 interactive threshold segmentation
 * 2 robert
 * 3 sobel
 * 4 PriWitt
 * 5 laplacian
 * 6 gauss_laplacian
 * 7 Krisch
 * 8 Custom Edge
 *
 * 9 Region Growing 区域生长
 * 10 Contour Extraction 轮廓提取
 * 11 Boundary Tracking 边界跟踪
 *
 * 12 Hough Transformation                  Hough变换
 * 13 Hough Transformation Line Detection    Hough变换做线检测
 */
void MainWindow::segmentationSlot()
{
    if(MyTabWidget::getNumber() == -1)
    {
        QMessageBox::about(this, "请先打开图片", "没图片（负责这部分的不是粗鄙之人！）");
        return;
    }
    if(MyTabWidget::getNumber() == -1)
    {
        QMessageBox::about(this, "请先打开图片", "没图片（负责这部分的不是粗鄙之人！）");
        return;
    }

    //    大津阈值
    if(ui->actionOtsu_Law_Threshold_Segmentation == QObject::sender())
    {
        image = ImageSegmentation::ostu(*(myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage()));
        myTab->setImage(0, 1, image);
    }

    //交互式阈值分割


    if(ui->actionInteractive_Threshold_Segmentation == QObject::sender())
    {
        GrayDialog * dialog = new GrayDialog(this, 0);

        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        QImage * newImage = ImageGray::binaryzation(myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), dialog->getGrayValue());
//        myTab->setImage(myTab->currentIndex(), 1, newImage);
        dialog->deleteLater();

    }
    //Robert算子
    if(ui->actionRobert_Operator == QObject::sender()){
        SegmentationCommand* command = new SegmentationCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             RobertOp);
        myTab->pushCurrentStack(command);
        return;
    }
    //Sobel算子
    if(ui->actionSobel_Operator == QObject::sender()){
        SegmentationCommand* command = new SegmentationCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             SobelOp);
        myTab->pushCurrentStack(command);
        return;
    }
    //Prewitt算子
    if(ui->actionPrewitt_Operator == QObject::sender()){
        SegmentationCommand* command = new SegmentationCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             PrewittOp);
        myTab->pushCurrentStack(command);
        return;
    }
    //Laplacian算子
    if(ui->actionLaplacian_Operator == QObject::sender()){
        SegmentationCommand* command = new SegmentationCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             LaplacianOp);
        myTab->pushCurrentStack(command);
        return;
    }
    //Gauss-Laplacian算子
    if(ui->actionGauss_Laplacian_Operator == QObject::sender()){
        SegmentationCommand* command = new SegmentationCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             GaussLaplacianOp);
        myTab->pushCurrentStack(command);
        return;
    }
    //Krisch算子
    if(ui->actionKrisch_Operator == QObject::sender()){
        SegmentationCommand* command = new SegmentationCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             KrischOp);
        myTab->pushCurrentStack(command);
        return;
    }
    //自定义模板边缘
    if(ui->actionCustom_Edges == QObject::sender()){
        CustomEdgeDialog * dialog = new CustomEdgeDialog(this);
        if(dialog->exec() == QDialog::Rejected)
        {
            dialog->deleteLater();
            return;
        }
        SegmentationCommand* command = new SegmentationCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                             myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(),
                                             this->myTab,
                                             myTab->currentIndex(),
                                             CINDEX::CustomEdge,dialog->getTemplate());
        dialog->deleteLater();
        myTab->pushCurrentStack(command);
        return;
    }
    //区域生长
    if(ui->actionRegion_Grow == QObject::sender()){
        image = ImageSegmentation::regionGrowing(myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage());
        myTab->setImage(myTab->currentIndex(), 1, image);
    }
    //轮廓提取
    if(ui->actionContour_Extraction == QObject::sender()){
        int lambda = -1;
        tdpDialog *tdialog = new tdpDialog(this,"threshold");
        QImage * tmp;
        if(myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage() == NULL)
        {
            tmp = new QImage(*myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage());
        }
        else
        {
            tmp = new QImage(*myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage());
        }
        while (true)
        {
            if(tdialog->exec() == QDialog::Rejected)
            {
                if(lambda != tdialog->getThreshold()){
                    lambda = tdialog->getThreshold();
                    //每一次循环复制一个新的tmp ，因为下面两个函数会对原图像造成改变
                    QImage * loopTmp = new QImage(*tmp);
                    loopTmp = ImageSegmentation::ContourExtraction(loopTmp,3,1,lambda);
                    myTab->setImage(myTab->currentIndex(),1,loopTmp);
                    delete loopTmp;
                    loopTmp = NULL;
                }
                continue;
            }
            lambda = tdialog->getThreshold();
            break;
        }
        SegmentationCommand* command = new SegmentationCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
                                                               tmp,
                                                               this->myTab,
                                                               myTab->currentIndex(),
                                                               CINDEX::ContourExtraction,
                                                               &lambda);

        myTab->pushCurrentStack(command);
        tdialog->deleteLater();

//        image = ImageSegmentation::ContourExtraction(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(),
//                                                      3,1,164);
//        myTab->setImage(myTab->currentIndex(), 1, image);
    }
    //边界追踪
    if(ui->actionBoundary_Tracking == QObject::sender()){
        if(MyTabWidget::getNumber() == -1)
        {
            QMessageBox::about(this, "请先打开图片", "没图片处理个奶子哟（粗鄙之人！）");
            return;
        }
        if(!afterBin())
        {
            QMessageBox::about(this, "图片不符合要求", "需要二值化后才可以进行边界追踪");
            return;
        }
        BoundaryTrackCommand* command = new BoundaryTrackCommand(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage(), myTab->getImageDisplay(myTab->currentIndex(), 1)->getImage(), this->myTab, myTab->currentIndex());
        myTab->pushCurrentStack(command);
    }
    //Hough变换
    if(ui->actionHough_Transformation == QObject::sender()){

    }
    //Hough变换线性检测
    if(ui->actionHough_Transformation_Line_Detection == QObject::sender()){
        image = ImageSegmentation::houghTran(*(myTab->getImageDisplay(myTab->currentIndex(), 0)->getImage()));
        myTab->setImage(myTab->currentIndex(), 1, image);
    }


}




//注意
//现静态算法可以有返回值，具体调用变化，见exampleCommand类中,redo方法的注释
//只是有一点，一定记得在算法的最后delete掉传入的参数并赋NULL，这是为了防止内存泄漏


//新需求：每个commandlabel颜色不同，比如多种蓝色。可以全局枚举变量。

//在硬阈值法和软阈值法点击事件处提供类似音量调节条类似的控件

//bug
//打开一张图片后，再次选择“打开文件”但并不打开，弹出file does not exist, 此时全局Image已经为空
