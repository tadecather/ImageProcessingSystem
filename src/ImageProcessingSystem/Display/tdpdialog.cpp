#include "tdpdialog.h"

tdpDialog::tdpDialog(QWidget *parent, QString name, int min, int max):QDialog(parent)
{
    slider    = new QSlider(Qt::Horizontal,this);
    set       = new QPushButton("Set",this);
    preview   = new QPushButton("Preview",this);
    lab1      = new QLabel(name,this);
    editNum   = new QSpinBox(this);

//  设置滑块相关
    slider->setMinimum(min);
    slider->setMaximum(max);
    slider->setTickPosition(QSlider::TicksAbove);

//    设置spinbox相关
    editNum->setMinimum(min);
    editNum->setMaximum(max);

    connect(slider,&QSlider::valueChanged,this,&tdpDialog::valueChangedSlots);
    connect(editNum,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&tdpDialog::valueChangedSlots);
//    将关闭按钮与set相关联
//    connect(this->)
    connect(preview,&QPushButton::clicked,this,&QDialog::reject);
    connect(set    ,&QPushButton::clicked,this,&QDialog::accept);
    grdLayout = new QGridLayout(this);

    grdLayout->addWidget(slider,0,0,1,1);
    grdLayout->addWidget(lab1,0,1,1,1);
    grdLayout->addWidget(editNum,0,2,1,1);

    grdLayout->addWidget(preview,1,1,1,1);
    grdLayout->addWidget(set,1,2,1,1);

    grdLayout->setColumnStretch(0,3);
    grdLayout->setColumnStretch(1,1);
    grdLayout->setColumnStretch(2,1);
    this->setLayout(grdLayout);

}

tdpDialog::~tdpDialog()
{
    grdLayout->deleteLater();
    slider->deleteLater();
    set->deleteLater();
    preview->deleteLater();
    lab1->deleteLater();
    editNum->deleteLater();


}

int tdpDialog::getThreshold()
{
    return this->threshold;
}


void tdpDialog::valueChangedSlots(int newVal)
{
    this->editNum->setValue(newVal);
    this->slider->setValue(newVal);
}

//下面两个重载槽函数给我一个教训，重载的时候记得带上原函数的部分操作，如果你对原函数不是很清楚的话
void tdpDialog::accept()
{
    threshold = this->editNum->value();
    //关闭窗口
    QDialog::accept();

}

void tdpDialog::reject()
{
    threshold = this->editNum->value();
    QDialog::reject();
}


