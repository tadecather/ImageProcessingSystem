
#ifndef GRAYCOMMAND_H
#define GRAYCOMMAND_H

#include"imagecommand.h"
#include<QImage>
#include <QString>
#include "imagegray.h"
#include"mytabwidget.h"

class Color2GrayCommand : public ImageCommand
{
private:
    QImage * imageLeft;
    QImage * imageRight;
    QImage * imageAfter;
    int index;
    MyTabWidget* mainTab;

public:

//     GrayCommand();
        QImage * color2Gray(QImage * img);
public:
    Color2GrayCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index);
    void undo();
    void redo();
    QString* getName();
    //bool mergeWith(const QUndoCommand *other);
};


#endif // GRAYCOMMAND_H
