#ifndef SELECTIVEMASKSMOOOTHCOMMAND_H
#define SELECTIVEMASKSMOOOTHCOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imageenhancement.h"
#include "mytabwidget.h"

class SelectiveMaskSmooothCommand : public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
public:
    SelectiveMaskSmooothCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index);
    void undo();
    void redo();
};

#endif // SELECTIVEMASKSMOOOTHCOMMAND_H
