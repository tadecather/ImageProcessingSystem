#ifndef COMMANDLABEL_H
#define COMMANDLABEL_H

#include <QWidget>

class CommandLabel : public QWidget
{
    Q_OBJECT
private:
    QString* name;

public:
    explicit CommandLabel(QString* name, QWidget *parent = 0);
    QString* getName();

signals:

public slots:
};

#endif // COMMANDLABEL_H
