/****************************************************************************
** Meta object code from reading C++ file 'base_cmd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../base_cmd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'base_cmd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_c_base_cmd_t {
    QByteArrayData data[5];
    char stringdata[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_base_cmd_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_base_cmd_t qt_meta_stringdata_c_base_cmd = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 10),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 10),
QT_MOC_LITERAL(4, 34, 9)
    },
    "c_base_cmd\0slot_write\0\0slot_start\0"
    "slot_stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_base_cmd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void c_base_cmd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        c_base_cmd *_t = static_cast<c_base_cmd *>(_o);
        switch (_id) {
        case 0: _t->slot_write(); break;
        case 1: _t->slot_start(); break;
        case 2: _t->slot_stop(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject c_base_cmd::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_c_base_cmd.data,
      qt_meta_data_c_base_cmd,  qt_static_metacall, 0, 0}
};


const QMetaObject *c_base_cmd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_base_cmd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_c_base_cmd.stringdata))
        return static_cast<void*>(const_cast< c_base_cmd*>(this));
    return QObject::qt_metacast(_clname);
}

int c_base_cmd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
