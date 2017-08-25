#ifndef GRADIENTSHARPENDIALOG_H
#define GRADIENTSHARPENDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QRegExpValidator>
#include <QDebug>
#include <QComboBox>
#include <QDoubleSpinBox>

class GradientSharpenDialog : public QDialog
{
public:
    GradientSharpenDialog(QWidget* parent);
    ~GradientSharpenDialog();
    int getOperatorNo();
    double getMulti();
private:
    int operatorNo;
    double multi;
    QComboBox* box;
    QDoubleSpinBox* spin;
    QPushButton* confirm;
    QPushButton* cancel;
    QGridLayout* layout;
private slots:
    void operatorNoChanged();
    void multiChanged();
};

#endif // GRADIENTSHARPENDIALOG_H
