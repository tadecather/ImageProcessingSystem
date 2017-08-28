#ifndef GNOISECOMMAND_H
#define GNOISECOMMAND_H

#include "imagecommand.h"
#include <QImage>
#include <QString>
#include "imageenhancement.h"
#include "mytabwidget.h"


class GNoiseCommand : public ImageCommand
{
private:
    int index;
    MyTabWidget* mainTab;
    double mu;
    double sigma;
    double k;
public:
    GNoiseCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index, double mu, double sigma, double k);
    void undo();
    void redo();
};

#endif // GNOISECOMMAND_H
