#ifndef FILEOPERATION_H
#define FILEOPERATION_H


namespace Op {
class FileOperation;
}
class FileOperation{
public:
    static QImage open();
    static QImage * open(QString opFileName);
    static void save ();
    static bool saveAs ();
    static void print ();
    static void printPreview();
    static void printSetting();
    static void recentFile ();
    static void exit ();

private:
    static bool outputFile();
private:
    QString saveFileName,
}
#endif // FILEOPERATION_H
