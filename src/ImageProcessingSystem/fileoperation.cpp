#include<fileoperation.h>
#include<QImage>
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QWidget>
#include<QPrintDialog>
#include<QPrintPreviewDialog>
#include<QTextStream>
#include<QMenu>
#include <QDebug>

//只保留一个open函数通过文件名打开


//向外输出文件，成功返回true,失败返回false
bool FileOperation::outputFile(const QImage & image,QString saveFileName){
        QFile* file = new QFile;
        file->setFileName(saveFileName);
        bool ok = file->open(QIODevice::WriteOnly);
        if(!ok){
            return false;
        }
        image.save(file, "JPG", 100);

        file->close();
        return true;
}


//另存为函数，保存指定Qimage,参数为一个Qiamge的常引用，成功返回true,失败返回false
bool FileOperation::saveAs (const QImage & image)
{
   QString saveFileName= QFileDialog::getSaveFileName(NULL, "save file", QDir::currentPath());
    if(saveFileName.isEmpty()){
        return false;
    }
   return outputFile(image,saveFileName);
}
//保存指定QImage,参数为一个Qiamge的常引用，成功返回true,失败返回false
bool FileOperation::save (const QImage & img,QString saveFileName)
{
    if(saveFileName.isEmpty()){
        return saveAs(img);
    }
    return outputFile(img,saveFileName);
}

//打印函数
void FileOperation::print (QWidget * qwid)
{
    QPrinter printer;
//    QString printerName = printer.printerName();
    QPrintDialog dlg(&printer, qwid);
    if(dlg.exec() == QDialog::Accepted){
        QSize s = QSize(printer.logicalDpiX()*2, printer.logicalDpiY()*6);
        printer.setOutputFormat(QPrinter::NativeFormat);
    }
    return;
}

//打印预览，需要一个槽 具体哪里实现不清楚，槽的代码在下面注释里
//void FileOperation::printPreview(QWidget * qwid){
//    QPrintPreviewDialog dlg;
//    connect(&dlg, SIGNAL(paintRequested(QPrinter*)), qwid, SLOT(paintRequestedSlot(QPrinter*)));
//    dlg.exec();
//    return;
//}

//void FileOperation::paintRequestedSlot(QPrinter *printer)
//{

//    QPainter painter(printer);
//    scene->render(&painter);
//}


//保存最近打开的文件列表,当一开始运行程序的时候，先从文件中读取
void FileOperation::saveRecentFile( const QStringList & qsl)
{
    QFile file("./rctFile.txt");
    if(file.open(QIODevice::ReadWrite)){
        QTextStream out(&file);
        for(int i=0;i<qsl.length();i++){
            out<<qsl.at(i)<<endl;
        }
        file.close();
    }
}
//从文件中读出来
void FileOperation::readFromRecentFile( QStringList & qsl)
{
     qsl.clear();
     QFile file("./rctFile.txt");
     if(file.exists())
     {
         if(file.open(QIODevice::ReadOnly)){
             QTextStream in(&file);
             QString str;
             while((str=in.readLine())!=NULL)
             {
                qsl.append(str);
             }
             file.close();
        }
     }
}

void FileOperation::recentFileChanged(MainWindow *mainwindow,QMenu &menu, QStringList & qstrl)
{
//    connect(menu, &FileOperation::changgeRecentFileSignal, mainwindow, &MainWindow::setRecentFileEnableSlot);
    menu.clear();
//    if(qstrl.isEmpty()){
//        emit changgeRecentFileSignal();
//        disconnect(menu, &FileOperation::changgeRecentFileSignal, mainwindow, &MainWindow::setRecentFileEnableSlot);

//        return;
//    }
    QAction *subAction  = new QAction();
    subAction->setText("clearAll");
    connect(subAction, &QAction::triggered, mainwindow, &MainWindow::clearAllRecentSlot);
    menu.addAction(subAction);



    if(qstrl.length()>0){
        while(qstrl.length()>8){
             qstrl.takeFirst();
        }
        for(int i=0;i<qstrl.length();i++){

            subAction  = new QAction();
            subAction->setText(qstrl.at(i));
            connect(subAction, &QAction::triggered, mainwindow, &MainWindow::openRecentFile);
            menu.addAction(subAction);
        }
    }

//    qlqa=menu.actions();
//    //qlqa为QList<QAction*>
//    if(qlqa.length()==2){
////        qDebug()<<"发射信号"<<endl;
////        emit mySignal(false);
//    }
//    else{
////        emit mySignal(true);
//    }

}
//openbyname
QImage *  FileOperation::open(QString opFileName,QStringList& qstrl)
{
    QImage *image = new QImage();
    QFile fl(opFileName);
    if(!fl.exists()){
        QMessageBox::about(NULL,"fail","file does not exist");
        return NULL;
    }
    else
    {
        if(!image->load(opFileName))
        {
           return NULL;
        }
        if(!qstrl.contains(opFileName))
            qstrl.append(opFileName);
        return image;
    }
}


//这个函数直接操作ui,可以考虑放在mainWindow中,或者传递一个MainWindow指针





