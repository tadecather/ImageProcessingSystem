/****************************************************************************
** Meta object code from reading C++ file 'imagedisplay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ImageProcessingSystem/Display/imagedisplay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagedisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ImageDisplay_t {
    QByteArrayData data[10];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageDisplay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageDisplay_t qt_meta_stringdata_ImageDisplay = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ImageDisplay"
QT_MOC_LITERAL(1, 13, 12), // "newTabSignal"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "focusOnSignal"
QT_MOC_LITERAL(4, 41, 18), // "setReferenceSignal"
QT_MOC_LITERAL(5, 60, 19), // "assessQualitySignal"
QT_MOC_LITERAL(6, 80, 14), // "emitNewTabSlot"
QT_MOC_LITERAL(7, 95, 20), // "emitSetReferenceSlot"
QT_MOC_LITERAL(8, 116, 21), // "emitAssessQualitySlot"
QT_MOC_LITERAL(9, 138, 10) // "mouseClick"

    },
    "ImageDisplay\0newTabSignal\0\0focusOnSignal\0"
    "setReferenceSignal\0assessQualitySignal\0"
    "emitNewTabSlot\0emitSetReferenceSlot\0"
    "emitAssessQualitySlot\0mouseClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageDisplay[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ImageDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageDisplay *_t = static_cast<ImageDisplay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newTabSignal(); break;
        case 1: _t->focusOnSignal(); break;
        case 2: _t->setReferenceSignal(); break;
        case 3: _t->assessQualitySignal(); break;
        case 4: _t->emitNewTabSlot(); break;
        case 5: _t->emitSetReferenceSlot(); break;
        case 6: _t->emitAssessQualitySlot(); break;
        case 7: _t->mouseClick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ImageDisplay::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageDisplay::newTabSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ImageDisplay::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageDisplay::focusOnSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ImageDisplay::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageDisplay::setReferenceSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ImageDisplay::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageDisplay::assessQualitySignal)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ImageDisplay::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_ImageDisplay.data,
      qt_meta_data_ImageDisplay,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageDisplay.stringdata0))
        return static_cast<void*>(const_cast< ImageDisplay*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int ImageDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ImageDisplay::newTabSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ImageDisplay::focusOnSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ImageDisplay::setReferenceSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ImageDisplay::assessQualitySignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
