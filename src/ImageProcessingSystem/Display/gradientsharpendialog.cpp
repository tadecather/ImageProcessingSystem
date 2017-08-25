#include "gradientsharpendialog.h"

GradientSharpenDialog::GradientSharpenDialog(QWidget* parent) : QDialog(parent)
{
    operatorNo = 0;
    multi = 1.0;

    //下拉列表，选择三种算法
    box = new QComboBox(this);
    box->addItem("Roberts");
    box->addItem("Sobel");
    box->addItem("Prewitt");

    //currentIndexChanged信号重载过了，使用qt5的connect语法，需要声明函数指针或者显式转换一下，下QDoubleSpinBox同
    connect(box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GradientSharpenDialog::operatorNoChanged);

    //doublespinbox，设定乘数
    spin = new QDoubleSpinBox(this);
    spin->setRange(0.00, 2.00);
    spin->setDecimals(2);
    spin->setSingleStep(0.05);

    connect(spin, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &GradientSharpenDialog::multiChanged);

    //确定、取消
    confirm = new QPushButton("确定", this);
    confirm->setDefault(true);
    cancel = new QPushButton("取消", this);

    connect(confirm, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);

    //布局
    layout = new QGridLayout(this);
    layout->addWidget(box, 0, 0, 1, 1);
    layout->addWidget(spin, 0, 1, 1, 1);
    layout->addWidget(confirm, 1, 0, 1, 1);
    layout->addWidget(cancel, 1, 1, 1, 1);

    this->setLayout(layout);
}

GradientSharpenDialog::~GradientSharpenDialog()
{
    box->deleteLater();
    spin->deleteLater();
    confirm->deleteLater();
    cancel->deleteLater();
    layout->deleteLater();
}

int GradientSharpenDialog::getOperatorNo()
{
    return this->operatorNo;
}

double GradientSharpenDialog::getMulti()
{
    return this->multi;
}

void GradientSharpenDialog::operatorNoChanged()
{
    this->operatorNo = box->currentIndex();
}

void GradientSharpenDialog::multiChanged()
{
    this->multi = spin->value();
}
