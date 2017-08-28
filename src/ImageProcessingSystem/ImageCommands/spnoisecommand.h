#ifndef SPNOISECOMMAND_H
#define SPNOISECOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imageenhancement.h"
#include "mytabwidget.h"

class SpNoiseCommand : public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
    double snr;
public:
    SpNoiseCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, double snr);
    void undo();
    void redo();
};

#endif // SPNOISECOMMAND_H
