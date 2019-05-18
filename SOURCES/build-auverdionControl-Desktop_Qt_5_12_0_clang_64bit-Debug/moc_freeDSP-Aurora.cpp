/****************************************************************************
** Meta object code from reading C++ file 'freeDSP-Aurora.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../auverdionControl/src/dsp/freeDSP-Aurora.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'freeDSP-Aurora.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CFreeDspAurora_t {
    QByteArrayData data[11];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CFreeDspAurora_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CFreeDspAurora_t qt_meta_stringdata_CFreeDspAurora = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CFreeDspAurora"
QT_MOC_LITERAL(1, 15, 13), // "haveReplyWifi"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "bytesWrittenWifi"
QT_MOC_LITERAL(4, 47, 5), // "bytes"
QT_MOC_LITERAL(5, 53, 16), // "disconnectedWifi"
QT_MOC_LITERAL(6, 70, 9), // "errorWifi"
QT_MOC_LITERAL(7, 80, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(8, 109, 11), // "socketError"
QT_MOC_LITERAL(9, 121, 13), // "hostFoundWifi"
QT_MOC_LITERAL(10, 135, 13) // "readyReadWifi"

    },
    "CFreeDspAurora\0haveReplyWifi\0\0"
    "bytesWrittenWifi\0bytes\0disconnectedWifi\0"
    "errorWifi\0QAbstractSocket::SocketError\0"
    "socketError\0hostFoundWifi\0readyReadWifi"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CFreeDspAurora[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x08 /* Private */,
       5,    0,   48,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,
       9,    0,   52,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CFreeDspAurora::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CFreeDspAurora *_t = static_cast<CFreeDspAurora *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->haveReplyWifi(); break;
        case 1: _t->bytesWrittenWifi((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 2: _t->disconnectedWifi(); break;
        case 3: _t->errorWifi((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->hostFoundWifi(); break;
        case 5: _t->readyReadWifi(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CFreeDspAurora::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CFreeDspAurora::haveReplyWifi)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CFreeDspAurora::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CFreeDspAurora.data,
    qt_meta_data_CFreeDspAurora,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CFreeDspAurora::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CFreeDspAurora::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CFreeDspAurora.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CFreeDspAurora::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CFreeDspAurora::haveReplyWifi()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
