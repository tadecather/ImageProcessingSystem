#ifndef WAVELETDIALOG_H
#define WAVELETDIALOG_H
#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>

#include "mainwindow.h"

class tdpDialog :public QDialog
{
public:
    tdpDialog(QWidget *parent,QString name,int min =0,int max =255);
    ~tdpDialog();
    int getThreshold();
private:
    int threshold =0;
    QSlider * slider;
    QPushButton * set;
    QPushButton * preview;
    QSpinBox * editNum;
    QLabel * lab1;
    QGridLayout * grdLayout;
    //用于判断是preview还是set
private slots:
    void  valueChangedSlots(int newVal);
    //用于和关闭窗口连接
    int cancelSlots();
public slots:
    void accept() override;
    void reject() override;
};

#endif // WAVELETDIALOG_H
