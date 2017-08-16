#include "commandlabel.h"

CommandLabel::CommandLabel(QString *name)
{
    this->setText(*name);
    this->setAlignment(Qt::AlignCenter);
    this->name = new QString(*name);
    this->setFixedWidth(200);
    QFont font ("Microsoft YaHei", 17, QFont::Light);
    this->setFont(font);
    this->setStyleSheet("color:white; border-radius:3px;background-color: #66ccff;");
    this->setAutoFillBackground(true);
    //this->setPalette(QPalette(QColor(102, 204, 255)));
}

QString* CommandLabel::getName()
{
    return this->name;
}
void CommandLabel::setGray()
{
    this->setStyleSheet("color:white; border-radius:3px;background-color: black");
}
void CommandLabel::setBlue()
{
    this->setStyleSheet("color:white; border-radius:3px;background-color: #66ccff");
}


void CommandLabel::mousePressEvent(QMouseEvent *ev)
{
    emit clicked();
}
