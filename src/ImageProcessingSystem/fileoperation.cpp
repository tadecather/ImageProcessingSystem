#include<fileoperation.h>
#include<QImage>
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QWidget>
//打开文件函数，传递QImage对象指针，如返回为NULL，表示传递失败
static QImage * OP::open()
{
        QImage * img= new QImage();
        QString fileName = QFileDialog::getOpenFileName(
                    this, "open image file",
                    ".",
                    "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");

        if(fileName != "")
            {
                if(！img->load(fileName))
                {
                    delete img;
                    img=NULL;
                }
        }
        return img;
}
//重载open函数，通过文件名打开文件
static QImage * OP::open(QString opFileName)
{
    QFile fl(opFileName);
    if(!fl.exist){
        QMessageBox::Information(NULL,"fail","file does not exist",QMessageBox::Ok);
        return NULL;
    }
    else
    {
                if(！img->load(fileName))
                {
                    delete img;
                    img=NULL;
                }
        return img;
    }

}

//保存指定QImage,参数为一个Qiamge的常引用，成功返回true,失败返回false
static bool OP::save (const QImage & img)
{
    if(saveFileName.isEmpty()){
        return this->saveAsFileSlot();
    }
    return outputFile(img);
}
//另存为函数，保存指定Qimage,参数为一个Qiamge的常引用，成功返回true,失败返回false
static bool OP::saveAs ()
{
    saveFileName = QFileDialog::getSaveFileName(this, "save file", QDir::currentPath());
    if(saveFileName.isEmpty()){
        return false;
    }
   return outputFile();
}
//打印函数
static void OP::print ()
{
    QPrinter printer;
//    QString printerName = printer.printerName();
    QPrintDialog dlg(&printer, this);
    if(dlg.exec() == QDialog::Accepted){
        QSize s = QSize(printer.logicalDpiX()*2, printer.logicalDpiY()*6);
        printer.setOutputFormat(QPrinter::NativeFormat);
    }
    return;
}
//打印预览，需要一个槽 具体哪里实现不清楚，槽的代码在下面注释里
static void OP::printPreview(){
    QPrintPreviewDialog dlg;
    connect(&dlg, SIGNAL(paintRequested(QPrinter*)), this, SLOT(paintRequestedSlot(QPrinter*)));
    dlg.exec();
    return;
}

//void MainWindow::paintRequestedSlot(QPrinter *printer)
//{
//    QPainter painter(printer);
//    scene->render(&painter);
//}

static void OP::recentFile ()
{

}

//向外输出文件，成功返回true,失败返回false
static bool OP::outputFile(const QImage & image){
        QFile* file = new QFile;
        file->setFileName(saveFileName);
        bool ok =  file->open(QIODevice::WriteOnly);
        if(!ok){
            return false;
        }
            image->save(file,"JPG",100);
        return true;
}
