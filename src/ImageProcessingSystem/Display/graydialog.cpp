#include "graydialog.h"

GrayDialog::GrayDialog(QWidget* parent) : QDialog(parent)
{
    inputNumLabel = new QLabel("输入均值", this);

    spinBox = new QSpinBox(this);
    spinBox->setMaximum(255);
    spinBox->setMinimum(0);
    spinBox->autoFillBackground();

    //确定按钮
    confirm = new QPushButton("确定", this);
    confirm->setDefault(true);

    //取消按钮
    cancel = new QPushButton("取消", this);

    //按钮connect
    connect(this->confirm, &QPushButton::clicked, this, &QDialog::accept);
    connect(this->cancel, &QPushButton::clicked, this, &QDialog::reject);

    layout = new QGridLayout();

    layout->addWidget(inputNumLabel, 0, 0, 1, 2);
    layout->addWidget(spinBox, 0, 1, 1, 2);
    layout->addWidget(cancel, 2, 0, 1, 1);
    layout->addWidget(confirm, 2, 1, 1, 1);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 0);

    this->setLayout(layout);

}

GrayDialog::~GrayDialog()
{
    inputNumLabel->deleteLater();
    spinBox->deleteLater();
    cancel->deleteLater();
    confirm->deleteLater();

}

// 返回获得的灰度数值
int GrayDialog::getGrayValue()
{
    return this->spinBox->value();
}


