#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#include "mainwindow.h"

#include <QImage>
#include <QAction>
#include<QPrinter>

class FileOperation:QObject{
    Q_OBJECT
public:
    static QImage * open(QString opFileName, QStringList& qstrl);
    static bool save(const QImage & img,QString saveFileName);
    static bool saveAs(const QImage & image);
    static void print(QWidget *  qwid);
    static void printPreview(QWidget * qwid);
    static void printSetting();
    static void recentFile( const QStringList & qsl);
    static void exit();
    static void recentFileChanged(MainWindow *mainWindow, QMenu &menu,QStringList & qstrl);
    static void readFromRecentFile( QStringList & qsl);
    static void saveRecentFile( const QStringList & qsl);
private:

    void openRecentFile();
    static bool outputFile(const QImage & image, QString saveFileName);
signals:
    //void changgeRecentFileSignal();
private slots:
    //void paintRequestedSlot(QPrinter *printer);
};
#endif // FILEOPERATION_H
