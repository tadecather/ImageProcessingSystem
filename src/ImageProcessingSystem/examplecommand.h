#ifndef EXAMPLECOMMAND_H
#define EXAMPLECOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imagegray.h"

//为了避免互相引用，作MyTabWidget类声明
class MyTabWidget;

//这是一个command样例类，实现见ExampleCommand.cpp
//下面的声明只能多不能少
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
