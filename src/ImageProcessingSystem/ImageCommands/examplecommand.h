#ifndef EXAMPLECOMMAND_H
#define EXAMPLECOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imagegray.h"
#include "mytabwidget.h"

class ExampleCommand : public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
public:
    ExampleCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index);
    void undo();
    void redo();
};

#endif // EXAMPLECOMMAND_H
