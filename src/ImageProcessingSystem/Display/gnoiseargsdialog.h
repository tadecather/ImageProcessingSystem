#ifndef GNOISEARGSDIALOG_H
#define GNOISEARGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QRegExpValidator>
#include <QDebug>

class GNoiseArgsDialog : public QDialog
{
public:
    GNoiseArgsDialog(QWidget* parent);
    ~GNoiseArgsDialog();
    double getMu();
    double getSigma();
    double getK();
private:
    QGridLayout* layout;
    double mu;
    double sigma;
    double k;
    QLabel* inputMu;
    QLabel* inputSigma;
    QLabel* inputK;
    QLineEdit* muEdit;
    QLineEdit* sigmaEdit;
    QLineEdit* kEdit;
    QPushButton* confirm;
    QPushButton* cancel;
private slots:
    void muChanged();
    void sigmaChanged();
    void kChanged();
};

#endif // GNOISEARGSDIALOG_H
