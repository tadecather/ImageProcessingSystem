#ifndef IMAGECOMMAND_H
#define IMAGECOMMAND_H

#include <QUndoCommand>

class ImageCommand : public QUndoCommand
{
public:
    ImageCommand();
    QString* getName();
    QImage* getImageAfter();
protected:
    QString* name;
    bool firstTime = true;
    QImage * imageLeft;
    QImage * imageRight;
    QImage * imageAfter;
};

#endif // IMAGECOMMAND_H
