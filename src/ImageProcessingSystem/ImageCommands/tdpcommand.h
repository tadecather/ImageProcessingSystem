#ifndef TDPCOMMAND_H
#define TDPCOMMAND_H

#include "imagecommand.h"
#include "imgtransformdomainprocessing.h"

class TDPCommand:public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
    int commandIntdex;
    int waveCount =0;
    int lambda = 0;
    int times = 0;
    /*
     * 定义命令的索引号；
     * 0 ：哈尔小波变换
     * 1 ：哈尔小波逆变换
     * 2 ：设置高频分量为零
     * 3 ：硬阈值法
     * 4 ：软阈值法
     */
public:
    //预留两个参数位置给各条命令
    TDPCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, int commandIntdex, int args1 =0,int lambda =0);
    void undo();
    void redo();
    int getCommandIndex();
    int getWaveCount();
};

#endif // TDPCOMMAND_H
