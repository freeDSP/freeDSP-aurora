/****************************************************************************
** Meta object code from reading C++ file 'QLowShelv.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../auverdionControl/src/QLowShelv.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QLowShelv.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QLowShelv_t {
    QByteArrayData data[6];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QLowShelv_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QLowShelv_t qt_meta_stringdata_QLowShelv = {
    {
QT_MOC_LITERAL(0, 0, 9), // "QLowShelv"
QT_MOC_LITERAL(1, 10, 33), // "on_doubleSpinBoxGain_valueCha..."
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 31), // "on_doubleSpinBoxFc_valueChanged"
QT_MOC_LITERAL(4, 77, 30), // "on_doubleSpinBoxS_valueChanged"
QT_MOC_LITERAL(5, 108, 27) // "on_pushButtonBypass_clicked"

    },
    "QLowShelv\0on_doubleSpinBoxGain_valueChanged\0"
    "\0on_doubleSpinBoxFc_valueChanged\0"
    "on_doubleSpinBoxS_valueChanged\0"
    "on_pushButtonBypass_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QLowShelv[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       3,    1,   37,    2, 0x08 /* Private */,
       4,    1,   40,    2, 0x08 /* Private */,
       5,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,

       0        // eod
};

void QLowShelv::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QLowShelv *_t = static_cast<QLowShelv *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_doubleSpinBoxGain_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->on_doubleSpinBoxFc_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->on_doubleSpinBoxS_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->on_pushButtonBypass_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QLowShelv::staticMetaObject = { {
    &QDspBlock::staticMetaObject,
    qt_meta_stringdata_QLowShelv.data,
    qt_meta_data_QLowShelv,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QLowShelv::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QLowShelv::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QLowShelv.stringdata0))
        return static_cast<void*>(this);
    return QDspBlock::qt_metacast(_clname);
}

int QLowShelv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDspBlock::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
