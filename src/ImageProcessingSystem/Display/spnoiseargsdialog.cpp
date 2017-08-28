#include "spnoiseargsdialog.h"

SPNoiseArgsDialog::SPNoiseArgsDialog(QWidget *parent) : QDialog(parent)
{
    snr = 0.0;

    //输入标签
    inputSnr = new QLabel("信噪比", this);

    //输入框
    snrEdit = new QLineEdit("0.0", this);

    //输入限制
    QRegExp regx("^[0].[0-9][0-9]$");
    QValidator *validator = new QRegExpValidator(regx, this);
    snrEdit->setValidator(validator);

    //确定按钮
    confirm = new QPushButton("确定", this);
    confirm->setDefault(true);

    //取消按钮
    cancel = new QPushButton("取消", this);

    //按钮connect
    connect(this->confirm, &QPushButton::clicked, this, &QDialog::accept);
    connect(this->cancel, &QPushButton::clicked, this, &QDialog::reject);

    //QLineEdit修改connect
    connect(this->snrEdit, &QLineEdit::textChanged, this, &SPNoiseArgsDialog::snrChanged);

    //布局
    layout = new QGridLayout();
    layout->addWidget(inputSnr, 0, 0, 1, 2);
    layout->addWidget(snrEdit, 0, 1, 1, 2);
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
    snrEdit->deleteLater();
    confirm->deleteLater();
    cancel->deleteLater();
}

double SPNoiseArgsDialog::getSnr()
{
    return this->snr;
}

void SPNoiseArgsDialog::snrChanged()
{
    this->snr = snrEdit->text().toDouble();
    qDebug()<<snr;
}
