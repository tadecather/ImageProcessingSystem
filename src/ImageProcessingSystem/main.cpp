#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow* w = new MainWindow;
    w->setWindowTitle("图像处理算法演示系统 Ver0.3");
    w->showMaximized();


    return a.exec();
}
