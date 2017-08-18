#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>
//以下四个头文件已在tabcontent包含，适时删除此处头文件
#include <QUndoCommand>
#include <QUndoStack>
#include <QUndoGroup>
#include <QUndoView>
#include "imagedisplay.h"
#include "MyTabWidget.h"
#include "imagetrans.h"
#include "imgtransformdomainprocessing.h"
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //判断当前图片有没有经过灰度化
    bool afterGray();


private:
    QMenu *subMenu;
    QImage * image;
    //暂时定义图片的高和宽
    int imageHeight, imagewidth;
    int waveCount =0;
    QString saveFileName;
    QString currentPath;
    QStringList* recentFileList;
    MyTabWidget* myTab;
    QUndoStack* commandStack;
    Ui::MainWindow *ui;
private slots:
    void openFileSlot();
    void saveFileSlot();
    void saveAsFileSlot();
    void printSlot();
    void printPreViewSlot();
    void exitSlot();
    void printPreviewSlot(QPrinter *printerPixmap);
    void graySlot();
    void transformSlot();
    void enhancementSlot();
    void transDomainProcessSlot();
    void segmentationSlot();

public slots:
    void setRecentFileEnableSlot();
    void openRecentFile();
    void clearAllRecentSlot();

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // MAINWINDOW_H
