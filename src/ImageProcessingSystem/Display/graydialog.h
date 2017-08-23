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
    GrayDialog(QWidget* parent);
    ~GrayDialog();
    int getGrayValue();

private:
    QGridLayout* layout;
    QLabel * inputNumLabel;
    QSpinBox * spinBox;
    QPushButton * confirm;
    QPushButton * cancel;


};

#endif // GRAYDIALOG_H
