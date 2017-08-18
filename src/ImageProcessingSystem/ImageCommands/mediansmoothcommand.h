#ifndef MEDIANSMOOTHCOMMAND_H
#define MEDIANSMOOTHCOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imageenhancement.h"
#include "mytabwidget.h"

class MedianSmoothCommand : public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
    int size;
public:
    MedianSmoothCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, int size);
    void undo();
    void redo();
};

#endif // MEDIANSMOOTHCOMMAND_H
