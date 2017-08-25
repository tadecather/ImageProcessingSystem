#ifndef GRADIENTSHARPENCOMMAND_H
#define GRADIENTSHARPENCOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imageenhancement.h"
#include "mytabwidget.h"

class GradientSharpenCommand : public ImageCommand
{
private:
    int index;
    int operatorNo;
    double multi;
    MyTabWidget* mainTab;
public:
    GradientSharpenCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, int operatorNo, double multi);
    void undo();
    void redo();
};


#endif // GRADIENTSHARPENCOMMAND_H
