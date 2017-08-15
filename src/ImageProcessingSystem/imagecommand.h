#ifndef IMAGECOMMAND_H
#define IMAGECOMMAND_H

#include <QUndoCommand>

class ImageCommand : public QUndoCommand
{
public:
    ImageCommand();
    QString* getName();
protected:
    QString* name;
    bool firstTime = true;
};

#endif // IMAGECOMMAND_H
