
#ifndef GRAYCOMMAND_H
#define GRAYCOMMAND_H

#include<QUndoCommand>
#include<QImage>
#include "imagegray.h"
#include"mytabwidget.h"

class Gray2ColorCommand : public QUndoCommand
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
    // QUndoCommand interface
public:
    Gray2ColorCommand(QImage* imageLeft, QImage* imageRight, MyTabWidget* mainTab, int index);
    void undo();
    void redo();
    //bool mergeWith(const QUndoCommand *other);
};


#endif // GRAYCOMMAND_H
