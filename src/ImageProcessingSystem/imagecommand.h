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
};

#endif // IMAGECOMMAND_H
