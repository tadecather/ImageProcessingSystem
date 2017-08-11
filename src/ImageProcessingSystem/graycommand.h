#ifndef GRAYCOMMAND_H
#define GRAYCOMMAND_H

#include<QUndoCommand>
#include<QImage>

#include"imagedisplay.h"
class GrayCommand : public QUndoCommand
{
private:
    QImage * imageLeft;
    QImage * imageRight;
    QImage * imageAfter;

//    ImageDisplay * imgDisplayLf;
//    ImageDisplay * imgDisplayRg;
public:

//     GrayCommand();
  //  QImage * color2Gray(QImage & img);
    // QUndoCommand interface
public:
    void undo();
    void redo();
    int id() const;
    bool mergeWith(const QUndoCommand *other);
};


#endif // GRAYCOMMAND_H
