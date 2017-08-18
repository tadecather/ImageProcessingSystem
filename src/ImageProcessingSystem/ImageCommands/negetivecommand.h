#ifndef NEGETIVECOMMAND_H
#define NEGETIVECOMMAND_H

#include"imagecommand.h"
#include<QImage>
#include "imagegray.h"
#include"mytabwidget.h"

class NegetiveCommand : public ImageCommand
{

private:
    int index;
    MyTabWidget* mainTab;

public:
    NegetiveCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index);
    void undo();
    void redo();

};

#endif // NEGETIVECOMMAND_H
