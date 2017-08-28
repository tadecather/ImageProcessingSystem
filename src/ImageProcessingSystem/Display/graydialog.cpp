#include "graydialog.h"
#include <QLineEdit>

GrayDialog::GrayDialog(QWidget* parent, int dialogType) : QDialog(parent)
{
    this->dialogType = dialogType;

    //确定按钮
    confirm = new QPushButton("确定", this);
    confirm->setDefault(true);

    //取消按钮
    cancel = new QPushButton("取消", this);

    //按钮connect
    connect(this->confirm, &QPushButton::clicked, this, &QDialog::accept);
    connect(this->cancel, &QPushButton::clicked, this, &QDialog::reject);

    layout = new QGridLayout();

    switch (dialogType) {
    case 0:{
        inputNumLabel = new QLabel("输入灰度值", this);
        spinBox = new QSpinBox(this);
        spinBox->setMaximum(255);
        spinBox->setMinimum(0);
        spinBox->autoFillBackground();

        layout->addWidget(inputNumLabel, 0, 0, 1, 2);
        layout->addWidget(spinBox, 0, 1, 1, 2);
        layout->addWidget(cancel, 2, 0, 1, 1);
        layout->addWidget(confirm, 2, 1, 1, 1);


        break;
    }
    case 1:{
        args1Label = new QLabel("输入K值", this);
        args2Label = new QLabel("输入D值", this);
        args1Edit = new QLineEdit("0.0", this);
        args2Edit = new QLineEdit("0.0", this);

        layout->addWidget(args1Label, 0, 0, 1, 1);
        layout->addWidget(args1Edit, 0, 1, 1, 1);
        layout->addWidget(args2Label, 1, 0, 1, 1);
        layout->addWidget(args2Edit, 1, 1, 1, 1);
        break;

    }
    case 2:{
        args1Label = new QLabel("输入C值", this);
        args2Label = new QLabel("输入R值", this);
        args1Edit = new QLineEdit("0.0", this);
        args2Edit = new QLineEdit("0.0", this);

        layout->addWidget(args1Label, 0, 0, 1, 1);
        layout->addWidget(args1Edit, 0, 1, 1, 1);
        layout->addWidget(args2Label, 1, 0, 1, 1);
        layout->addWidget(args2Edit, 1, 1, 1, 1);
        break;

    }
    case 3:{
        args1Label = new QLabel("输入V值", this);
        args1Edit = new QLineEdit("0.0", this);

        layout->addWidget(args1Label, 0, 0, 1, 2);
        layout->addWidget(args1Edit, 0, 1, 1, 2);
        break;
    }

    case 4:{
        args1Label = new QLabel("输入选取阈值方法", this);
        args1Edit = new QLineEdit("0", this);

        layout->addWidget(args1Label, 0, 0, 1, 2);
        layout->addWidget(args1Edit, 0, 1, 1, 2);
        break;
    }

    default:
        break;
    }


    layout->addWidget(cancel, 2, 0, 1, 1);
    layout->addWidget(confirm, 2, 1, 1, 1);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 1);

    this->setLayout(layout);

}

GrayDialog::~GrayDialog()
{
    if(dialogType == 0){
        inputNumLabel->deleteLater();
        spinBox->deleteLater();
    }else if( dialogType == 1 || dialogType == 2){
        args1Label->deleteLater();
        args1Edit->deleteLater();
        args2Edit->deleteLater();
        args2Label->deleteLater();
    }else if(dialogType == 3 || dialogType == 4){
        args1Label->deleteLater();
        args1Edit->deleteLater();
    }

    cancel->deleteLater();
    confirm->deleteLater();
    layout->deleteLater();

}

// 返回获得的灰度数值
int GrayDialog::getGrayValue()
{
    return this->spinBox->value();
}

double GrayDialog::getArgs1(){
    return this->args1Edit->text().toDouble();
}

double GrayDialog::getArgs2(){
    return this->args2Edit->text().toDouble();
}


