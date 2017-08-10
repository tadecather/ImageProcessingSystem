#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include <QImage>

namespace OP {
class FileOperation;
}
class FileOperation{
public:
    static QImage * open(QString opFileName);
    static bool save (const QImage & img);
    static bool saveAs ();
    static void print ();
    static void printPreview();
    static void printSetting();
    static void recentFile ();
    static void exit ();

private:
    static bool outputFile();
private:
    QString saveFileName;
};
#endif // FILEOPERATION_H
