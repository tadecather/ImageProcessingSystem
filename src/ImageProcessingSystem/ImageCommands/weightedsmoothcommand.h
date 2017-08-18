#ifndef WEIGHTEDSMOOTHCOMMAND_H
#define WEIGHTEDSMOOTHCOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imageenhancement.h"
#include "mytabwidget.h"

class WeightedSmoothCommand : public ImageCommand
{
private:
    int index;
    int size;
    double theta;
    MyTabWidget* mainTab;
public:
    WeightedSmoothCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, int size, double theta);
    void undo();
    void redo();
};

#endif // WEIGHTEDSMOOTHCOMMAND_H
