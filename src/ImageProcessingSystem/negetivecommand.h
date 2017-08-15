#ifndef NEGETIVECOMMAND_H
#define NEGETIVECOMMAND_H

#include"imagecommand.h"
#include<QImage>
#include "imagegray.h"
#include"mytabwidget.h"

class NegetiveCommand : public ImageCommand
{

private:
    QImage * imageLeft;
    QImage * imageRight;
    QImage * imageAfter;
    int index;
    MyTabWidget* mainTab;

public:
    //记得检测图像是否已经灰度化。推荐：负相算法检测是否已灰度化，然后向上抛出异常
    NegetiveCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index);
    void undo();
    void redo();

};

#endif // NEGETIVECOMMAND_H
