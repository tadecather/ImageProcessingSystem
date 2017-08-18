#include "meansmoothargsdialog.h"

MeanSmoothArgsDialog::MeanSmoothArgsDialog(QWidget *parent) : QDialog(parent)
{
    //size默认为3
    this->size = 3;

    //标签
    inputSize = new QLabel("矩阵边长", this);
    //输入框
    sizeEdit = new QLineEdit("3", this);
    //按钮
    confirm = new QPushButton("确定", this);
    confirm->setDefault(true);
    cancel = new QPushButton("取消", this);

    connect(sizeEdit, &QLineEdit::textChanged, this, &MeanSmoothArgsDialog::sizeChanged);

    connect(confirm, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);

    layout = new QGridLayout();
    layout->addWidget(inputSize, 0, 0, 1, 1);
    layout->addWidget(sizeEdit, 0, 1, 1, 1);
    layout->addWidget(confirm, 1, 0, 1, 1);
    layout->addWidget(cancel, 1, 1, 1, 1);

    this->setLayout(layout);
}

MeanSmoothArgsDialog::~MeanSmoothArgsDialog()
{
    inputSize->deleteLater();
    sizeEdit->deleteLater();
    confirm->deleteLater();
    cancel->deleteLater();
    layout->deleteLater();
}

int MeanSmoothArgsDialog::getSize()
{
    return this->size;
}

void MeanSmoothArgsDialog::sizeChanged()
{
    this->size = sizeEdit->text().toInt();
}

void MeanSmoothArgsDialog::accept()
{
    if(size%2 == 1&&size > 1)
    {
        this->setVisible(false);
        this->setResult(1);
    }
    else
    {
        QMessageBox::information(this, "输入不合要求", "矩阵边长应为大于1的奇数");
    }
}
