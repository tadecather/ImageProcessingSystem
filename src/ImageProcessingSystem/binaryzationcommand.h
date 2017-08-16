#ifndef BINARYZATIONCOMMAND_H
#define BINARYZATIONCOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imagegray.h"

class MyTabWidget;

class BinaryzationCommand : public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
public:
    BinaryzationCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index);
    void undo();
    void redo();
};

#endif // BINARYZATIONCOMMAND_H
