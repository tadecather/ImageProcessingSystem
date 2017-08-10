#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#include<QImage>
//namespace OP {
//class FileOperation;
//}
class FileOperation:QObject{
    Q_OBJECT
public:
    static QImage * open(QString opFileName);
    static void save (const QImage & img);
    static bool saveAs ();
    static void print ();
    static void printPreview();
    static void printSetting();
    static void recentFile ();
    static void exit ();
    static void recentFileChanged(QList<QAction*> &qlqa,QMenu & menu,QStringList & qstrl);
    static void readFromRecentFile( QStringList & qsl);
    static void saveRecentFile( const QStringList & qsl);
private:
    static bool outputFile();
private:
//    static QString saveFileName;
};
#endif // FILEOPERATION_H
