#ifndef MSMOOTHCOMMAND_H
#define MSMOOTHCOMMAND_H


#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imageenhancement.h"
#include "mytabwidget.h"


class MeanSmoothCommand : public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
    int size;
public:
    MeanSmoothCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, int size);
    void undo();
    void redo();
};

#endif // MSMOOTHCOMMAND_H
