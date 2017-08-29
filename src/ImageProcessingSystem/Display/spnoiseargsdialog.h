#ifndef SPNOISEARGSDIALOG_H
#define SPNOISEARGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QRegExpValidator>
#include <QDoubleSpinBox>
#include <QDebug>

class SPNoiseArgsDialog : public QDialog
{
public:
    SPNoiseArgsDialog(QWidget* parent);
    ~SPNoiseArgsDialog();
    double getSnr();
private:
    double snr;
    QGridLayout* layout;
    QLabel* inputSnr;
    QDoubleSpinBox* snrSpin;
    QPushButton* confirm;
    QPushButton* cancel;

private slots:
    void snrChanged();
};

#endif // SPNOISEARGSDIALOG_H
