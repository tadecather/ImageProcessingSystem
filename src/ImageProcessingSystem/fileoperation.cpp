#include<fileoperation.h>
#include<QImage>
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QWidget>
#include<QPrinter>
#include<QPrintDialog>
#include<QPrintPreviewDialog>
#include<QTextStream>
#include<QMenu>
//只保留一个open函数通过文件名打开


//向外输出文件，成功返回true,失败返回false
static bool outputFile(const QImage & image,QString saveFileName){
        QFile* file = new QFile;
        file->setFileName(saveFileName);
        bool ok =  file->open(QIODevice::WriteOnly);
        if(!ok){
            return false;
        }
            image.save(file,"JPG",100);
        return true;
}


//另存为函数，保存指定Qimage,参数为一个Qiamge的常引用，成功返回true,失败返回false
static bool saveAs (const QImage & image)
{
   QString saveFileName= QFileDialog::getSaveFileName(NULL, "save file", QDir::currentPath());
    if(saveFileName.isEmpty()){
        return false;
    }
   return outputFile(image,saveFileName);
}
//保存指定QImage,参数为一个Qiamge的常引用，成功返回true,失败返回false
static bool save (const QImage & img,QString saveFileName)
{
    if(saveFileName.isEmpty()){
        return saveAs(img);
    }
    return outputFile(img,saveFileName);
}

//打印函数
static void print (QWidget& qwid)
{
    QPrinter printer;
//    QString printerName = printer.printerName();
    QPrintDialog dlg(&printer, &qwid);
    if(dlg.exec() == QDialog::Accepted){
        QSize s = QSize(printer.logicalDpiX()*2, printer.logicalDpiY()*6);
        printer.setOutputFormat(QPrinter::NativeFormat);
    }
    return;
}
//打印预览，需要一个槽 具体哪里实现不清楚，槽的代码在下面注释里
//static void printPreview(QWidget& qwid){
//    QPrintPreviewDialog dlg;
//    connect(&dlg, SIGNAL(paintRequested(QPrinter*)), &qwid, SLOT(paintRequestedSlot(QPrinter*)));
//    dlg.exec();
//    return;
//}

//void MainWindow::paintRequestedSlot(QPrinter *printer)
//{
//    QPainter painter(printer);
//    scene->render(&painter);
//}


//保存最近打开的文件列表,当一开始运行程序的时候，先从文件中读取
void saveRecentFile( const QStringList & qsl)
{
    QFile file("./rctFile.txt");
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        for(int i=0;i<qsl.length();i++){
            out<<qsl.at(i)<<endl;
        }
        file.close();
    }
}
//从文件中读出来
void readFromRecentFile( QStringList & qsl)
{
      qsl.clear();
     QFile file("./rctFile.txt");
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

static void recentFileChanged(QList<QAction*> &qlqa,QMenu & menu,QStringList & qstrl)
{
    menu.clear();
    menu.addAction("clearAll");
    if(qstrl.length()>0){
        while(qstrl.length()>8){
             qstrl.takeFirst();
        }
        for(int i=0;i<qstrl.length();i++){
           menu.addAction(qstrl.at(i));
        }
    }
    qlqa=menu.actions();
    //qlqa为QList<QAction*>
    if(qlqa.length()==2){
//        qDebug()<<"发射信号"<<endl;
//        emit mySignal(false);
    }
    else{
//        emit mySignal(true);
    }

}
//openbyname
static QImage *  open(QString opFileName,QStringList& qstrl)
{
    QImage *image =new QImage();
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
        qstrl.append(opFileName);
//        ui->menurecent_file->addAction(opFileName);
//           recentFileChanged();
        return image;
    }
}


//这个函数直接操作ui,可以考虑放在mainWindow中,或者传递一个MainWindow指针

