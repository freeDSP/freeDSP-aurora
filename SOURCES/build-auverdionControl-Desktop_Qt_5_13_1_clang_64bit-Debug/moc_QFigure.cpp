/****************************************************************************
** Meta object code from reading C++ file 'QFigure.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../auverdionControl/src/figure/QFigure.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QFigure.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QFigure_t {
    QByteArrayData data[14];
    char stringdata0[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QFigure_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QFigure_t qt_meta_stringdata_QFigure = {
    {
QT_MOC_LITERAL(0, 0, 7), // "QFigure"
QT_MOC_LITERAL(1, 8, 15), // "showContextMenu"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 20), // "changeAxisProperties"
QT_MOC_LITERAL(4, 46, 19), // "setHorizontalMarker"
QT_MOC_LITERAL(5, 66, 17), // "setVerticalMarker"
QT_MOC_LITERAL(6, 84, 22), // "removeHorizontalMarker"
QT_MOC_LITERAL(7, 107, 20), // "removeVerticalMarker"
QT_MOC_LITERAL(8, 128, 15), // "backgroundColor"
QT_MOC_LITERAL(9, 144, 10), // "colorLabel"
QT_MOC_LITERAL(10, 155, 15), // "colorGridCoarse"
QT_MOC_LITERAL(11, 171, 13), // "colorGridFine"
QT_MOC_LITERAL(12, 185, 10), // "colorTitle"
QT_MOC_LITERAL(13, 196, 14) // "colorPlotFrame"

    },
    "QFigure\0showContextMenu\0\0changeAxisProperties\0"
    "setHorizontalMarker\0setVerticalMarker\0"
    "removeHorizontalMarker\0removeVerticalMarker\0"
    "backgroundColor\0colorLabel\0colorGridCoarse\0"
    "colorGridFine\0colorTitle\0colorPlotFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QFigure[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       6,   50, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::QColor, 0x00095103,
       9, QMetaType::QColor, 0x00095103,
      10, QMetaType::QColor, 0x00095103,
      11, QMetaType::QColor, 0x00095103,
      12, QMetaType::QColor, 0x00095103,
      13, QMetaType::QColor, 0x00095103,

       0        // eod
};

void QFigure::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QFigure *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showContextMenu(); break;
        case 1: _t->changeAxisProperties(); break;
        case 2: _t->setHorizontalMarker(); break;
        case 3: _t->setVerticalMarker(); break;
        case 4: _t->removeHorizontalMarker(); break;
        case 5: _t->removeVerticalMarker(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QFigure::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QFigure::showContextMenu)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QFigure *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->getBackgroundColor(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->getColorLabel(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->getColorGridCoarse(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->getColorGridFine(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->getColorTitle(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->getColorPlotFrame(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QFigure *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBackgroundColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setColorLabel(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setColorGridCoarse(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setColorGridFine(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->setColorTitle(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setColorPlotFrame(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QFigure::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_QFigure.data,
    qt_meta_data_QFigure,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QFigure::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QFigure::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QFigure.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QFigure::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QFigure::showContextMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
