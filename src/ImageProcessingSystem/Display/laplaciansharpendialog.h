#ifndef LAPLACIANSHARPENDIALOG_H
#define LAPLACIANSHARPENDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QRegExpValidator>
#include <QDebug>
#include <QComboBox>
#include <QDoubleSpinBox>

class LaplacianSharpenDialog : public QDialog
{
public:
    LaplacianSharpenDialog(QWidget* parent);
    ~LaplacianSharpenDialog();
    double getMulti();
private:
    double multi;
    QDoubleSpinBox* spin;
    QPushButton* confirm;
    QPushButton* cancel;
    QGridLayout* layout;
private slots:
    void multiChanged();
};

#endif // LAPLACIANSHARPENDIALOG_H
