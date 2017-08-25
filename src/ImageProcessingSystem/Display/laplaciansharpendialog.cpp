#include "laplaciansharpendialog.h"

LaplacianSharpenDialog::LaplacianSharpenDialog(QWidget* parent) : QDialog(parent)
{
    multi = 1.0;

    //doublespinbox，设定乘数
    spin = new QDoubleSpinBox(this);
    spin->setRange(0.00, 2.00);
    spin->setDecimals(2);
    spin->setSingleStep(0.05);

    connect(spin, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &LaplacianSharpenDialog::multiChanged);

    //确定、取消
    confirm = new QPushButton("确定", this);
    confirm->setDefault(true);
    cancel = new QPushButton("取消", this);

    connect(confirm, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);

    //布局
    layout = new QGridLayout(this);
    layout->addWidget(spin, 0, 0, 1, 2);
    layout->addWidget(confirm, 1, 0, 1, 1);
    layout->addWidget(cancel, 1, 1, 1, 1);

    this->setLayout(layout);
}

LaplacianSharpenDialog::~LaplacianSharpenDialog()
{
    spin->deleteLater();
    confirm->deleteLater();
    cancel->deleteLater();
    layout->deleteLater();
}

double LaplacianSharpenDialog::getMulti()
{
    return this->multi;
}

void LaplacianSharpenDialog::multiChanged()
{
    this->multi = spin->value();
}

