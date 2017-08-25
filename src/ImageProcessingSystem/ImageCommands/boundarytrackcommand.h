#ifndef BOUNDARYTRACKCOMMAND_H
#define BOUNDARYTRACKCOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imagesegmentation.h"
#include "mytabwidget.h"

class BoundaryTrackCommand : public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
public:
    BoundaryTrackCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index);
    void undo();
    void redo();
};


#endif // BOUNDARYTRACKCOMMAND_H
