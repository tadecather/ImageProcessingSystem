#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>
#include <iostream>
#include <Vector>
#include <QDebug>
#include <QUndoGroup>
#include <QUndoStack>
#include <algorithm>
#include "tabcontent.h"
#include "imagecommand.h"
//因为enhancement中的图像评估算法需要在右键菜单直接调用
#include "imageenhancement.h"

//自定义的TabWidget类
class MyTabWidget : public QTabWidget
{
    Q_OBJECT
private:
    static int number;
    ImageDisplay *imageDisplayL;
    ImageDisplay *imageDisplayR;
    std::vector<TabContent*> contentVec;
    QUndoGroup* commandGroup;
    QImage* referenceImage;
    QImage* assessImage;
public:
    MyTabWidget(QWidget *parent);
    //MyTabWidget(QWidget *parent, QImage *image);
    ~MyTabWidget();
    //使用int .currentIndex()来获得当前页面
    ImageDisplay* getImageDisplay(int index, int LR);
    void setImage(int index, int LR, QImage* image);
    void newTab(QImage *image);
    QImage* getFocusedImage();
    QUndoStack* getCurrentStack();
    TabContent* getCurrentContent();
    void pushCurrentStack(ImageCommand* command);
    void popCurrentStack();
    void redoCurrentStack();
    static void incNumber();
    static void decNumber();
    static int getNumber();
private slots:
    void closeTabSlot(int index);
    void scaleDisplayToView(int index);
public slots:
    void addTabSlot();
    void doToCommand();
    void setReferenceSlot();
    void asseccQualitySlot();

};

#endif // MYTABWIDGET_H
