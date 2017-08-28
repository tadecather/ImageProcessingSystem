#ifndef CUSTOMEDGE_H
#define CUSTOMEDGE_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include <QGridLayout>
#include <QRegExpValidator>
#include <QDebug>
class CustomEdgeDialog:public QDialog
{
public:
    CustomEdgeDialog(QWidget *parent);
    ~CustomEdgeDialog();
    int * getTemplate();
private:
    int  selfTemplate[9];
    QPushButton * confirm;
    QList<QLineEdit * > * listOfLineEdit;
    QGridLayout * grdLayOut;
public slots:
    void accept();

};

#endif // CUSTOMEDGE_H
