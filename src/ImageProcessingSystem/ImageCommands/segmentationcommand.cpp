#include "segmentationcommand.h"


/*
 * InteractiveThreshold,RobertOp,SobelOp,PriwittOp,LaplacianOp,
    GaussLaplacianOp,KrischOp,CustomEdge,RegionGrowing,ContourExtraction,
    BoundaryTracking,HoughTrans,HoughTransLineDetect
 */
SegmentationCommand::SegmentationCommand(QImage *imageLeft, QImage *imageRight, MyTabWidget *mainTab, int index, int commandIntdex, int *args1)
{

    switch (commandIntdex) {
    case Ostu:
        name = new QString("大津阈值分割");
        break;
    case InteractiveThreshold:
        name = new QString("交互式阈值分割");
        break;
    case RobertOp:
        name = new QString("Robert算子");
        break;
    case SobelOp:
        name = new QString("Sobel算子:");

        break;
    case PrewittOp:
        name = new QString("Priwitt算子");
        break;
    case LaplacianOp:
        name = new QString("Laplacian算子");
        break;
    case GaussLaplacianOp:
        name = new QString("Gauss-Laplacian算子");
        break;
    case KrischOp:
        name = new QString("Krisch算子");
        break;
    case CustomEdge:
        name = new QString("自定义模板边缘");
        selftemplate = args1;
        break;
    case RegionGrowing:
        name = new QString("区域生长");
        break;
    case ContourExtraction:
        name = new QString("轮廓提取");
        contourThreshold = *args1;
        break;
    case BoundaryTracking:
        name = new QString("边界追踪");
        break;
    case HoughTrans:
        name = new QString("Hough变换");
        break;
    case HoughTransLineDetect:
        name = new QString("Hough变换做线检测");
        break;
    }
    this->imageLeft = new QImage(*imageLeft);
    if(imageRight == NULL)
    {
        this->imageRight = NULL;
        this->imageAfter = new QImage(*imageLeft);
    }
    else
    {
        this->imageRight = new QImage(*imageRight);
        this->imageAfter = new QImage(*imageRight);
    }
    this->mainTab = mainTab;
    this->index = index;
    this->commandIntdex = commandIntdex;
}
void SegmentationCommand::redo()
{
    int comIndex = getCommandIndex();
    if(firstTime)
    {
        switch (comIndex) {
        case Ostu:
//            this->imageAfter = ImageSegmentation::
            break;
        case InteractiveThreshold:
//            this->imageAfter = ImageSegmentation::
            break;
        case RobertOp:
            this->imageAfter = ImageSegmentation::RobertOperator(this->imageAfter);
            break;
        case SobelOp:
            this->imageAfter = ImageSegmentation::SobelOperator(this->imageAfter);
            break;
        case PrewittOp:
            this->imageAfter = ImageSegmentation::PrewittOperator(this->imageAfter);
            break;
        case LaplacianOp:
            this->imageAfter = ImageSegmentation::LaplacianOperator(this->imageAfter);
            break;
        case GaussLaplacianOp:
            this->imageAfter = ImageSegmentation::GaussLaplacianOperator(this->imageAfter);
            break;
        case KrischOp:
            this->imageAfter = ImageSegmentation::KrischOperator(this->imageAfter);
            break;
        case CustomEdge:
            this->imageAfter = ImageSegmentation::CustomEdge(this->imageAfter,selftemplate);
            break;
        case RegionGrowing:
//            this->imageAfter = ImageSegmentation::
            break;
        case ContourExtraction:
            //这里默认高斯平滑矩阵为3，1
            this->imageAfter = ImageSegmentation::ContourExtraction(this->imageAfter,3,1,contourThreshold);
            break;
        case BoundaryTracking:
//            this->imageAfter = ImageSegmentation::
            break;
        case HoughTrans:
//            this->imageAfter = ImageSegmentation::
            break;
        case HoughTransLineDetect:
//            this->imageAfter = ImageSegmentation::
            break;
        }
     }
    if(this->imageRight == NULL)
    {
        mainTab->setImage(index, 1, imageAfter);
    }
    else
    {
        mainTab->setImage(index, 0, imageRight);
        mainTab->setImage(index, 1, imageAfter);
    }
    //置firstTime 为false
    firstTime = false;
}

void SegmentationCommand::undo()
{
    if(this->imageRight == NULL)
    {
        mainTab->setImage(index, 0, imageLeft);
        mainTab->setImage(index, 1, NULL);
    }
    else
    {
        mainTab->setImage(index, 0, imageLeft);
        mainTab->setImage(index, 1, imageRight);
    }
}

int SegmentationCommand::getCommandIndex()
{
    return this->commandIntdex;
}
