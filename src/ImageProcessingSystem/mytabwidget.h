#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>
#include <iostream>
#include <Vector>
#include <QDebug>
#include "tabcontent.h"

//自定义的TabWidget类
class MyTabWidget : public QTabWidget
{
    Q_OBJECT
private:
    static int number;
    ImageDisplay *imageDisplayL;
    ImageDisplay *imageDisplayR;
    std::vector<TabContent*> contentVec;
public:
    MyTabWidget(QWidget *parent);
    MyTabWidget(QWidget *parent, QImage *image);
    ~MyTabWidget();
    bool isNullInitTab();
    void setLeftImage(QImage *image);
    void setRightImage(QImage *image);
    void newTab(QImage *image);
    static void incNumber();
    static void decNumber();
private slots:
    void closeTabSlot(int index);
public slots:
    void addTabSlot();

};

#endif // MYTABWIDGET_H
