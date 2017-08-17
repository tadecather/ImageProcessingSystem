#ifndef MSMOOTHCOMMAND_H
#define MSMOOTHCOMMAND_H


#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imageenhancement.h"
#include "mytabwidget.h"


//这是一个command样例类，实现见ExampleCommand.cpp
//下面的声明只能多不能少
class MSmoothCommand : public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
public:
    MSmoothCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index);
    void undo();
    void redo();
};

#endif // MSMOOTHCOMMAND_H
