/****************************************************************************
** Meta object code from reading C++ file 'mytabwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ImageProcessingSystem/Display/mytabwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyTabWidget_t {
    QByteArrayData data[9];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyTabWidget_t qt_meta_stringdata_MyTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MyTabWidget"
QT_MOC_LITERAL(1, 12, 12), // "closeTabSlot"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "index"
QT_MOC_LITERAL(4, 32, 18), // "scaleDisplayToView"
QT_MOC_LITERAL(5, 51, 10), // "addTabSlot"
QT_MOC_LITERAL(6, 62, 11), // "doToCommand"
QT_MOC_LITERAL(7, 74, 16), // "setReferenceSlot"
QT_MOC_LITERAL(8, 91, 17) // "asseccQualitySlot"

    },
    "MyTabWidget\0closeTabSlot\0\0index\0"
    "scaleDisplayToView\0addTabSlot\0doToCommand\0"
    "setReferenceSlot\0asseccQualitySlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyTabWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    1,   47,    2, 0x08 /* Private */,
       5,    0,   50,    2, 0x0a /* Public */,
       6,    0,   51,    2, 0x0a /* Public */,
       7,    0,   52,    2, 0x0a /* Public */,
       8,    0,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyTabWidget *_t = static_cast<MyTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeTabSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->scaleDisplayToView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->addTabSlot(); break;
        case 3: _t->doToCommand(); break;
        case 4: _t->setReferenceSlot(); break;
        case 5: _t->asseccQualitySlot(); break;
        default: ;
        }
    }
}

const QMetaObject MyTabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_MyTabWidget.data,
      qt_meta_data_MyTabWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyTabWidget.stringdata0))
        return static_cast<void*>(const_cast< MyTabWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int MyTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
