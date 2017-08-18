#ifndef MEANSMOOTHARGSDIALOG_H
#define MEANSMOOTHARGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QRegExpValidator>
#include <QDebug>
#include <QMessageBox>

class MeanSmoothArgsDialog : public QDialog
{
public:
    MeanSmoothArgsDialog(QWidget* parent);
    ~MeanSmoothArgsDialog();
    int getSize();
private:
    QGridLayout* layout;
    int size;
    QLabel* inputSize;
    QLineEdit* sizeEdit;
    QPushButton* confirm;
    QPushButton* cancel;
private slots:
    void sizeChanged();
public slots:
    void accept();
};

#endif // MEANSMOOTHARGSDIALOG_H
