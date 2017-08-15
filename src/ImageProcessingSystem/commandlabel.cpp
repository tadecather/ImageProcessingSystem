#include "commandlabel.h"

CommandLabel::CommandLabel(QString *name, QWidget *parent) : QWidget(parent)
{
    this->name = new QString(*name);
    this->resize(10, 20);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 255, 0)));
}

QString* CommandLabel::getName()
{
    return this->name;
}
