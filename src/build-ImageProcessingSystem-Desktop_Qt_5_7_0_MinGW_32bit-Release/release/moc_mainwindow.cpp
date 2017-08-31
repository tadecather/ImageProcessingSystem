/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ImageProcessingSystem/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[322];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "openFileSlot"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "saveFileSlot"
QT_MOC_LITERAL(4, 38, 14), // "saveAsFileSlot"
QT_MOC_LITERAL(5, 53, 9), // "printSlot"
QT_MOC_LITERAL(6, 63, 16), // "printPreViewSlot"
QT_MOC_LITERAL(7, 80, 8), // "exitSlot"
QT_MOC_LITERAL(8, 89, 10), // "closeEvent"
QT_MOC_LITERAL(9, 100, 12), // "QCloseEvent*"
QT_MOC_LITERAL(10, 113, 5), // "event"
QT_MOC_LITERAL(11, 119, 16), // "printPreviewSlot"
QT_MOC_LITERAL(12, 136, 9), // "QPrinter*"
QT_MOC_LITERAL(13, 146, 13), // "printerPixmap"
QT_MOC_LITERAL(14, 160, 8), // "graySlot"
QT_MOC_LITERAL(15, 169, 13), // "transformSlot"
QT_MOC_LITERAL(16, 183, 15), // "enhancementSlot"
QT_MOC_LITERAL(17, 199, 22), // "transDomainProcessSlot"
QT_MOC_LITERAL(18, 222, 16), // "segmentationSlot"
QT_MOC_LITERAL(19, 239, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(20, 264, 23), // "setRecentFileEnableSlot"
QT_MOC_LITERAL(21, 288, 14), // "openRecentFile"
QT_MOC_LITERAL(22, 303, 18) // "clearAllRecentSlot"

    },
    "MainWindow\0openFileSlot\0\0saveFileSlot\0"
    "saveAsFileSlot\0printSlot\0printPreViewSlot\0"
    "exitSlot\0closeEvent\0QCloseEvent*\0event\0"
    "printPreviewSlot\0QPrinter*\0printerPixmap\0"
    "graySlot\0transformSlot\0enhancementSlot\0"
    "transDomainProcessSlot\0segmentationSlot\0"
    "on_actionAbout_triggered\0"
    "setRecentFileEnableSlot\0openRecentFile\0"
    "clearAllRecentSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    1,  105,    2, 0x08 /* Private */,
      11,    1,  108,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,
      19,    0,  116,    2, 0x08 /* Private */,
      20,    0,  117,    2, 0x0a /* Public */,
      21,    0,  118,    2, 0x0a /* Public */,
      22,    0,  119,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFileSlot(); break;
        case 1: _t->saveFileSlot(); break;
        case 2: _t->saveAsFileSlot(); break;
        case 3: _t->printSlot(); break;
        case 4: _t->printPreViewSlot(); break;
        case 5: _t->exitSlot(); break;
        case 6: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 7: _t->printPreviewSlot((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 8: _t->graySlot(); break;
        case 9: _t->transformSlot(); break;
        case 10: _t->enhancementSlot(); break;
        case 11: _t->transDomainProcessSlot(); break;
        case 12: _t->segmentationSlot(); break;
        case 13: _t->on_actionAbout_triggered(); break;
        case 14: _t->setRecentFileEnableSlot(); break;
        case 15: _t->openRecentFile(); break;
        case 16: _t->clearAllRecentSlot(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
