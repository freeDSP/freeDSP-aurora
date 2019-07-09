/****************************************************************************
** Meta object code from reading C++ file 'QPeq.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../auverdionControl/src/QPeq.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QPeq.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QPeq_t {
    QByteArrayData data[12];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QPeq_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QPeq_t qt_meta_stringdata_QPeq = {
    {
QT_MOC_LITERAL(0, 0, 4), // "QPeq"
QT_MOC_LITERAL(1, 5, 13), // "importRewPeqs"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "QWidget*"
QT_MOC_LITERAL(4, 29, 33), // "on_doubleSpinBoxGain_valueCha..."
QT_MOC_LITERAL(5, 63, 31), // "on_doubleSpinBoxFc_valueChanged"
QT_MOC_LITERAL(6, 95, 30), // "on_doubleSpinBoxQ_valueChanged"
QT_MOC_LITERAL(7, 126, 27), // "on_pushButtonBypass_clicked"
QT_MOC_LITERAL(8, 154, 18), // "on_showContextMenu"
QT_MOC_LITERAL(9, 173, 3), // "pos"
QT_MOC_LITERAL(10, 177, 16), // "on_importRewPeqs"
QT_MOC_LITERAL(11, 194, 9) // "updateDsp"

    },
    "QPeq\0importRewPeqs\0\0QWidget*\0"
    "on_doubleSpinBoxGain_valueChanged\0"
    "on_doubleSpinBoxFc_valueChanged\0"
    "on_doubleSpinBoxQ_valueChanged\0"
    "on_pushButtonBypass_clicked\0"
    "on_showContextMenu\0pos\0on_importRewPeqs\0"
    "updateDsp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QPeq[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   57,    2, 0x08 /* Private */,
       5,    1,   60,    2, 0x08 /* Private */,
       6,    1,   63,    2, 0x08 /* Private */,
       7,    0,   66,    2, 0x08 /* Private */,
       8,    1,   67,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    0,   71,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QPeq::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QPeq *_t = static_cast<QPeq *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->importRewPeqs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->on_doubleSpinBoxGain_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->on_doubleSpinBoxFc_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->on_doubleSpinBoxQ_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->on_pushButtonBypass_clicked(); break;
        case 5: _t->on_showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: _t->on_importRewPeqs(); break;
        case 7: _t->updateDsp(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QPeq::*)(QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QPeq::importRewPeqs)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QPeq::staticMetaObject = { {
    &QDspBlock::staticMetaObject,
    qt_meta_stringdata_QPeq.data,
    qt_meta_data_QPeq,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QPeq::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QPeq::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QPeq.stringdata0))
        return static_cast<void*>(this);
    return QDspBlock::qt_metacast(_clname);
}

int QPeq::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDspBlock::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QPeq::importRewPeqs(QWidget * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
