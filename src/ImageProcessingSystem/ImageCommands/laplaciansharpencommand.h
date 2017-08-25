#ifndef LAPLACIANSHARPENCOMMAND_H
#define LAPLACIANSHARPENCOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imageenhancement.h"
#include "mytabwidget.h"

class LaplacianSharpenCommand : public ImageCommand
{
private:
    int index;
    double multi;
    MyTabWidget* mainTab;
public:
    LaplacianSharpenCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, double multi);
    void undo();
    void redo();
};


#endif // LAPLACIANSHARPENCOMMAND_H
