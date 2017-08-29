#include "spnoiseargsdialog.h"

SPNoiseArgsDialog::SPNoiseArgsDialog(QWidget *parent) : QDialog(parent)
{
    snr = 0.0;

    //输入标签
    inputSnr = new QLabel("信噪比", this);

    //输入框
    snrSpin = new QDoubleSpinBox(this);
    snrSpin->setRange(0.00, 1.00);
    snrSpin->setDecimals(2);
    snrSpin->setSingleStep(0.01);

    //确定按钮
    confirm = new QPushButton("确定", this);
    confirm->setDefault(true);

    //取消按钮
    cancel = new QPushButton("取消", this);

    //按钮connect
    connect(this->confirm, &QPushButton::clicked, this, &QDialog::accept);
    connect(this->cancel, &QPushButton::clicked, this, &QDialog::reject);

    //QLineEdit修改connect
    connect(snrSpin, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &SPNoiseArgsDialog::snrChanged);


    //布局
    layout = new QGridLayout();
    layout->addWidget(inputSnr, 0, 0, 1, 2);
    layout->addWidget(snrSpin, 0, 1, 1, 2);
    layout->addWidget(confirm, 1, 0, 1, 1);
    layout->addWidget(cancel, 1, 1, 1, 1);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);

    this->setLayout(layout);

}

SPNoiseArgsDialog::~SPNoiseArgsDialog()
{
    layout->deleteLater();
    inputSnr->deleteLater();
    snrSpin->deleteLater();
    confirm->deleteLater();
    cancel->deleteLater();
}

double SPNoiseArgsDialog::getSnr()
{
    return this->snr;
}

void SPNoiseArgsDialog::snrChanged()
{
    this->snr = snrSpin->value();
    qDebug()<<snr;
}
