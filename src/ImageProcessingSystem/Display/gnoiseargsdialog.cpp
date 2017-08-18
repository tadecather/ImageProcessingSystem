#include "gnoiseargsdialog.h"

GNoiseArgsDialog::GNoiseArgsDialog(QWidget* parent) : QDialog(parent)
{
    mu = 0;
    sigma = 1;
    k = 0;

    //标签
    inputMu = new QLabel("均值", this);
    inputSigma = new QLabel("方差", this);
    inputK = new QLabel("K值", this);

    //输入框
    muEdit = new QLineEdit("0", this);
    sigmaEdit = new QLineEdit("1", this);
    kEdit = new QLineEdit("0", this);

    //输入框只准输入数字
    QRegExp regx("[1-9][0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this);
    muEdit->setValidator(validator);
    sigmaEdit->setValidator(validator);
    kEdit->setValidator(validator);

    //确定按钮
    confirm = new QPushButton("确定", this);
    confirm->setDefault(true);

    //取消按钮
    cancel = new QPushButton("取消", this);

    //按钮connect
    connect(this->confirm, &QPushButton::clicked, this, &QDialog::accept);
    connect(this->cancel, &QPushButton::clicked, this, &QDialog::reject);

    //QLineEdit修改connect
    connect(this->muEdit, &QLineEdit::textChanged, this, &GNoiseArgsDialog::muChanged);
    connect(this->sigmaEdit, &QLineEdit::textChanged, this, &GNoiseArgsDialog::sigmaChanged);
    connect(this->kEdit, &QLineEdit::textChanged, this, &GNoiseArgsDialog::kChanged);

    layout = new QGridLayout();
    layout->addWidget(inputMu, 0, 0, 1, 1);
    layout->addWidget(muEdit, 0, 1, 1, 1);
    layout->addWidget(inputSigma, 1, 0, 1, 1);
    layout->addWidget(sigmaEdit, 1, 1, 1, 1);
    layout->addWidget(inputK, 2, 0, 1, 1);
    layout->addWidget(kEdit, 2, 1, 1, 1);
    layout->addWidget(confirm, 3, 0, 1, 1);
    layout->addWidget(cancel, 3, 1, 1, 1);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(3, 1);


    this->setLayout(layout);
}

GNoiseArgsDialog::~GNoiseArgsDialog()
{
    layout->deleteLater();
    inputMu->deleteLater();
    inputSigma->deleteLater();
    inputK->deleteLater();
    muEdit->deleteLater();
    sigmaEdit->deleteLater();
    kEdit->deleteLater();
    confirm->deleteLater();
    cancel->deleteLater();
}

double GNoiseArgsDialog::getMu()
{
    return this->mu;
}

double GNoiseArgsDialog::getSigma()
{
    return this->sigma;
}

double GNoiseArgsDialog::getK()
{
    return this->k;
}

void GNoiseArgsDialog::muChanged()
{
    this->mu = muEdit->text().toDouble();
}

void GNoiseArgsDialog::sigmaChanged()
{
    this->sigma = sigmaEdit->text().toDouble();
}

void GNoiseArgsDialog::kChanged()
{
    this->k = kEdit->text().toDouble();
}
