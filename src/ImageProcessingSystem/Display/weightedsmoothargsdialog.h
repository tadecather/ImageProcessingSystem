#ifndef WEIGHTEDSMOOTHARGSDIALOG_H
#define WEIGHTEDSMOOTHARGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QRegExpValidator>
#include <QDebug>
#include <QMessageBox>

class WeightedSmoothArgsDialog : public QDialog
{
public:
    WeightedSmoothArgsDialog(QWidget* parent);
    ~WeightedSmoothArgsDialog();
    int getSize();
    double getTheta();
private:
    QGridLayout* layout;
    int size;
    double theta;
    QLabel* inputSize;
    QLabel* inputTheta;
    QLineEdit* sizeEdit;
    QLineEdit* thetaEdit;
    QPushButton* confirm;
    QPushButton* cancel;
private slots:
    void sizeChanged();
    void thetaChanged();
public slots:
    void accept();
};

#endif // WEIGHTEDSMOOTHARGSDIALOG_H
