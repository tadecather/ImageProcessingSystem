#ifndef COMMANDLABEL_H
#define COMMANDLABEL_H

#include <QLabel>
#include <QDebug>

//标签类，供History显示
class CommandLabel : public QLabel
{
    Q_OBJECT
private:
    QString* name;

public:
    explicit CommandLabel(QString* name);
    QString* getName();
    //command undo之后，标签变灰
    void setGray();
    //command redo之后，标签变蓝，之后应该为enable/disable等名称
    void setBlue();

signals:
    clicked();
protected:
    void mousePressEvent(QMouseEvent *ev);
public slots:
};

#endif // COMMANDLABEL_H
