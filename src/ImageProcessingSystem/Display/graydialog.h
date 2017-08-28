#ifndef GRAYDIALOG_H
#define GRAYDIALOG_H

#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QDialog>
#include <QGridLayout>

class GrayDialog : public QDialog
{
public:
    GrayDialog(QWidget* parent, int dialogType);
    ~GrayDialog();
    int getGrayValue();
    double getArgs1();
    double getArgs2();

private:

    int dialogType;
    QGridLayout* layout;

    QLabel * inputNumLabel;
    QSpinBox * spinBox;
    QLabel * args1Label;
    QLineEdit * args1Edit;
    QLabel * args2Label;
    QLineEdit * args2Edit;

    QPushButton * confirm;
    QPushButton * cancel;


};

#endif // GRAYDIALOG_H
