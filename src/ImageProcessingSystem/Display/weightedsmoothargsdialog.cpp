#include "weightedsmoothargsdialog.h"

WeightedSmoothArgsDialog::WeightedSmoothArgsDialog(QWidget *parent) : QDialog(parent)
{
    size = 3;
    theta = 1.0;

    //标签
    inputSize = new QLabel("矩阵边长", this);
    inputTheta = new QLabel("标准差", this);

    //输入框
    sizeEdit = new QLineEdit("3", this);
    thetaEdit = new QLineEdit("1", this);

    //输入过滤
    QRegExp regx("[1-9][0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this);
    sizeEdit->setValidator(validator);
    thetaEdit->setValidator(validator);

    //按钮
    confirm = new QPushButton("确定", this);
    confirm->setDefault(true);
    cancel = new QPushButton("取消", this);

    connect(sizeEdit, &QLineEdit::textChanged, this, &WeightedSmoothArgsDialog::sizeChanged);
    connect(thetaEdit, &QLineEdit::textChanged, this, &WeightedSmoothArgsDialog::thetaChanged);

    connect(confirm, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);

    layout = new QGridLayout();
    layout->addWidget(inputSize, 0, 0, 1, 1);
    layout->addWidget(sizeEdit, 0, 1, 1, 1);
    layout->addWidget(inputTheta, 1, 0, 1, 1);
    layout->addWidget(thetaEdit, 1, 1, 1, 1);
    layout->addWidget(confirm, 2, 0, 1, 1);
    layout->addWidget(cancel, 2, 1, 1, 1);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 1);

    this->setLayout(layout);

}

WeightedSmoothArgsDialog::~WeightedSmoothArgsDialog()
{
    inputSize->deleteLater();
    inputTheta->deleteLater();
    sizeEdit->deleteLater();
    thetaEdit->deleteLater();
    confirm->deleteLater();
    cancel->deleteLater();
    layout->deleteLater();
}

int WeightedSmoothArgsDialog::getSize()
{
    return this->size;
}

double WeightedSmoothArgsDialog::getTheta()
{
    return this->theta;
}

void WeightedSmoothArgsDialog::sizeChanged()
{
    this->size = sizeEdit->text().toInt();
}

void WeightedSmoothArgsDialog::thetaChanged()
{
    this->theta = thetaEdit->text().toDouble();
}

void WeightedSmoothArgsDialog::accept()
{
    if(size%2 == 1&&size > 0&&theta>0)
    {
        //结果符合要求
        this->setVisible(false);
        this->setResult(1);
    }
    else
    {
        //结果不符合要求
        QMessageBox::information(this, "输入不合要求", "矩阵大小应为大于0的奇数\n标准差应大于0");

    }
}
