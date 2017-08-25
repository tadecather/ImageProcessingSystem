#ifndef GRAYSCOMMAND_H
#define GRAYSCOMMAND_H

#include "imagecommand.h"
#include "imagegray.h"
#include "mainwindow.h"

class GraysCommand:public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
    int commandIndex;
    double args1;
    double args2;
    /*
     * 1. 灰度化
     * 2. 灰色转彩色
     * 3. 负相
     * 4. 二值化
     * 5. 线性变换
     * 6. 指数变换
     * 7. 对数变换
     * 8. 绘制直方图
     * 9. 直方图均衡
     */
public:
    //预留两个参数位置给各条命令
    GraysCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, int commandIntdex, int args1 =0,int args2 = 0);
    void undo();
    void redo();
    QString* getName();
    int getCommandIndex();
    int getWaveCount();
};

#endif
