#ifndef SEGMENTATIONCOMMAND_H
#define SEGMENTATIONCOMMAND_H

#include "imagecommand.h"
#include "imagesegmentation.h"
#include "mytabwidget.h"
/*
 * 0 ostu 大津阈值分割
 * 1 interactive threshold segmentation
 * 2 robert
 * 3 sobel
 * 4 PriWitt
 * 5 laplacian
 * 6 gauss_laplacian
 * 7 Krisch
 * 8 Custom Edge
 *
 * 9 Region Growing 区域生长
 * 10 Contour Extraction 轮廓提取
 * 11 Boundary Tracking 边界跟踪
 *
 * 12 Hough Transformation                  Hough变换
 * 13 Hough Transformation Line Detection    Hough变换做线检测
 */
enum CINDEX{
    Ostu =0,InteractiveThreshold,RobertOp,SobelOp,PrewittOp,LaplacianOp,
    GaussLaplacianOp,KrischOp,CustomEdge,RegionGrowing,ContourExtraction,
    BoundaryTracking,HoughTrans,HoughTransLineDetect
};

class SegmentationCommand:public ImageCommand
{
public:
    //预留两个参数位置给各条命令
    SegmentationCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, int commandIntdex, int *args1 =NULL);
    void undo();
    void redo();
    int getCommandIndex();

private:
    int index;
    int * selftemplate;
    int contourThreshold;
    MyTabWidget* mainTab;
    int commandIntdex;
    /*
     * 定义命令的索引号；
     * 0 ：哈尔小波变换
     * 1 ：哈尔小波逆变换
     * 2 ：设置高频分量为零
     * 3 ：硬阈值法
     * 4 ：软阈值法
     */
};

#endif // SEGMENTATIONCOMMAND_H
