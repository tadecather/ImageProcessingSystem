#include "customedge.h"


CustomEdgeDialog::CustomEdgeDialog(QWidget *parent):QDialog(parent)
{
    confirm        = new QPushButton("Confirm",this);
    listOfLineEdit = new QList<QLineEdit*>;
    grdLayOut      = new QGridLayout(this);
    QRegExp regx("^(0|[1-9][0-9]*|-[1-9][0-9]*)$");

    QValidator *validator = new QRegExpValidator(regx, this);
    for(int i=0;i<9;++i)
    {
        listOfLineEdit->append(new QLineEdit(this));
        listOfLineEdit->at(i)->setValidator(validator);
        grdLayOut->addWidget(listOfLineEdit->at(i),i/3,i%3,1,1);
    }
    grdLayOut->addWidget(confirm,3,2,1,1);
    this->setLayout(grdLayOut);
    connect(confirm,&QPushButton::clicked,this,&QDialog::accept);

}

CustomEdgeDialog::~CustomEdgeDialog()
{
    confirm->deleteLater();
    for(int i=0;i<9;++i){
        listOfLineEdit->at(i)->deleteLater();
    }
    grdLayOut->deleteLater();

}

int *CustomEdgeDialog::getTemplate()
{
 return selfTemplate;
}

void CustomEdgeDialog::accept()
{
    for(int i = 0;i<9;++i)
    {
        selfTemplate[i] = listOfLineEdit->at(i)->text().toInt();
        qDebug()<<selfTemplate[i];
    }

    QDialog::accept();
}
