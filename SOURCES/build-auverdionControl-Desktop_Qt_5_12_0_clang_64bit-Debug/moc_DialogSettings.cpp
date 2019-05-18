/****************************************************************************
** Meta object code from reading C++ file 'DialogSettings.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../auverdionControl/src/DialogSettings.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DialogSettings.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogSettings_t {
    QByteArrayData data[10];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogSettings_t qt_meta_stringdata_DialogSettings = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DialogSettings"
QT_MOC_LITERAL(1, 15, 34), // "on_pushButtonInstallPlugin_cl..."
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 33), // "on_pushButtonVerifyPlugin_cli..."
QT_MOC_LITERAL(4, 85, 36), // "on_pushButtonStoreWiFiConfig_..."
QT_MOC_LITERAL(5, 122, 25), // "on_pushButtonPing_clicked"
QT_MOC_LITERAL(6, 148, 24), // "on_radioButtonAP_toggled"
QT_MOC_LITERAL(7, 173, 7), // "checked"
QT_MOC_LITERAL(8, 181, 31), // "on_radioButtonLocalWifi_toggled"
QT_MOC_LITERAL(9, 213, 36) // "on_lineEditIpAddress_editingF..."

    },
    "DialogSettings\0on_pushButtonInstallPlugin_clicked\0"
    "\0on_pushButtonVerifyPlugin_clicked\0"
    "on_pushButtonStoreWiFiConfig_clicked\0"
    "on_pushButtonPing_clicked\0"
    "on_radioButtonAP_toggled\0checked\0"
    "on_radioButtonLocalWifi_toggled\0"
    "on_lineEditIpAddress_editingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    1,   53,    2, 0x08 /* Private */,
       8,    1,   56,    2, 0x08 /* Private */,
       9,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,

       0        // eod
};

void DialogSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogSettings *_t = static_cast<DialogSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonInstallPlugin_clicked(); break;
        case 1: _t->on_pushButtonVerifyPlugin_clicked(); break;
        case 2: _t->on_pushButtonStoreWiFiConfig_clicked(); break;
        case 3: _t->on_pushButtonPing_clicked(); break;
        case 4: _t->on_radioButtonAP_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_radioButtonLocalWifi_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_lineEditIpAddress_editingFinished(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DialogSettings::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_DialogSettings.data,
    qt_meta_data_DialogSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DialogSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogSettings.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DialogSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
