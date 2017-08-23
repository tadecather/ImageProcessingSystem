
#ifndef GRAYCOMMAND_H
#define GRAYCOMMAND_H

#include"imagecommand.h"
#include<QImage>
#include <QString>
#include "imagegray.h"

class MyTabWidget;

class Color2GrayCommand : public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;

public:
        QImage * color2Gray(QImage * img);
public:
    Color2GrayCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index);
    void undo();
    void redo();
    QString* getName();
};


#endif // GRAYCOMMAND_H
