#ifndef TRANSCOMMAND_H
#define TRANSCOMMAND_H

#include "imagecommand.h"
#include "imagetrans.h"
#include "mytabwidget.h"
/*
 * 0 Transpose 转置
 * 1 HorizontalInversion 水平镜像
 * 2 VerticalInversion 竖直镜像
 * 3 ClockwiseRotation 顺时针旋转
 * 4 AutoclockwiseRotation 逆时针旋转
 */
enum TINDEX{
    Transpose=0,HorizontalInversion,VerticalInversion,ClockwiseRotation,AnticlockwiseRotation
};
class TransCommand:public ImageCommand
{
public:
    TransCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index,
                        int commandIndex);
    void undo();
    void redo();
    int getCommandIndex();

private:
    int index;
    int grayValue;
    int * selftemplate;
    int contourThreshold;
    MyTabWidget* mainTab;
    int commandIntdex;
};

#endif // TRANSCOMMAND_H
