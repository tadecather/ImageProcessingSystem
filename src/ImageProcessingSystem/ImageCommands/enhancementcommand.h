#ifndef ENHANCEMENTCOMMAND_H
#define ENHANCEMENTCOMMAND_H

#include "imagecommand.h"
#include "imageenhancement.h"
#include "mytabwidget.h"

enum commands{gNoise = 0, spNoise, meanSmooth, medianSmooth, weightedSmooth,
              maskSmooth, gradientSharpen, laplacianSharpen};

class EnhancementCommand:public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
    //区分多个command
    int commandIndex;
    double arg1;
    double arg2;
    double arg3;
    /*
     * 定义命令的索引号；
     * 0 : 高斯噪声
     * 1 : 椒盐噪声
     * 2 : 均值平滑
     * 3 : 中值平滑
     * 4 : 加权平滑
     * 5 : 选择式掩模平滑
     * 6 : 梯度锐化
     * 7 : 拉普拉斯锐化
     */
public:
    //预留两个参数位置给各条命令
    EnhancementCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, int commandIndex, double arg1 =-1, double arg2 =-1, double arg3=-1);
    void undo();
    void redo();
};


#endif // ENHANCEMENTCOMMAND_H
