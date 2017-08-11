#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include "imagedisplay.h"
#include "MyTabWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setImage(QImage *newImg);

private:
    QMenu *subMenu;
    QImage * image;
    //暂时定义图片的高和宽
    int imageHeight, imagewidth;
    QString saveFileName;
    QStringList* recentFileList;
    MyTabWidget* myTab;
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
public slots:
    void setRecentFileEnableSlot();
    void openRecentFile();
    void clearAllRecentSlot();
};

#endif // MAINWINDOW_H
