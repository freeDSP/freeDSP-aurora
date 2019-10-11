/****************************************************************************
** Meta object code from reading C++ file 'QPhase.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../auverdionControl/src/QPhase.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QPhase.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QPhase_t {
    QByteArrayData data[8];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QPhase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QPhase_t qt_meta_stringdata_QPhase = {
    {
QT_MOC_LITERAL(0, 0, 6), // "QPhase"
QT_MOC_LITERAL(1, 7, 31), // "on_doubleSpinBoxFc_valueChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 30), // "on_doubleSpinBoxQ_valueChanged"
QT_MOC_LITERAL(4, 71, 27), // "on_pushButtonBypass_clicked"
QT_MOC_LITERAL(5, 99, 30), // "on_checkBoxInvert_stateChanged"
QT_MOC_LITERAL(6, 130, 4), // "arg1"
QT_MOC_LITERAL(7, 135, 9) // "updateDsp"

    },
    "QPhase\0on_doubleSpinBoxFc_valueChanged\0"
    "\0on_doubleSpinBoxQ_valueChanged\0"
    "on_pushButtonBypass_clicked\0"
    "on_checkBoxInvert_stateChanged\0arg1\0"
    "updateDsp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QPhase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       3,    1,   42,    2, 0x08 /* Private */,
       4,    0,   45,    2, 0x08 /* Private */,
       5,    1,   46,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,

       0        // eod
};

void QPhase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QPhase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_doubleSpinBoxFc_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->on_doubleSpinBoxQ_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->on_pushButtonBypass_clicked(); break;
        case 3: _t->on_checkBoxInvert_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateDsp(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QPhase::staticMetaObject = { {
    &QDspBlock::staticMetaObject,
    qt_meta_stringdata_QPhase.data,
    qt_meta_data_QPhase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QPhase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QPhase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QPhase.stringdata0))
        return static_cast<void*>(this);
    return QDspBlock::qt_metacast(_clname);
}

int QPhase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDspBlock::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
