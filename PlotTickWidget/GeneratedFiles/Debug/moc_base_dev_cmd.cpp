/****************************************************************************
** Meta object code from reading C++ file 'base_dev_cmd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../base_dev_cmd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'base_dev_cmd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_c_base_dev_cmd_t {
    QByteArrayData data[6];
    char stringdata[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_base_dev_cmd_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_base_dev_cmd_t qt_meta_stringdata_c_base_dev_cmd = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 12),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 12),
QT_MOC_LITERAL(4, 42, 12),
QT_MOC_LITERAL(5, 55, 11)
    },
    "c_base_dev_cmd\0signal_write\0\0NoConnection\0"
    "signal_start\0signal_stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_base_dev_cmd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void c_base_dev_cmd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        c_base_dev_cmd *_t = static_cast<c_base_dev_cmd *>(_o);
        switch (_id) {
        case 0: _t->signal_write(); break;
        case 1: _t->NoConnection(); break;
        case 2: _t->signal_start(); break;
        case 3: _t->signal_stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (c_base_dev_cmd::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_base_dev_cmd::signal_write)) {
                *result = 0;
            }
        }
        {
            typedef void (c_base_dev_cmd::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_base_dev_cmd::NoConnection)) {
                *result = 1;
            }
        }
        {
            typedef void (c_base_dev_cmd::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_base_dev_cmd::signal_start)) {
                *result = 2;
            }
        }
        {
            typedef void (c_base_dev_cmd::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_base_dev_cmd::signal_stop)) {
                *result = 3;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject c_base_dev_cmd::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_c_base_dev_cmd.data,
      qt_meta_data_c_base_dev_cmd,  qt_static_metacall, 0, 0}
};


const QMetaObject *c_base_dev_cmd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_base_dev_cmd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_c_base_dev_cmd.stringdata))
        return static_cast<void*>(const_cast< c_base_dev_cmd*>(this));
    return QObject::qt_metacast(_clname);
}

int c_base_dev_cmd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void c_base_dev_cmd::signal_write()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void c_base_dev_cmd::NoConnection()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void c_base_dev_cmd::signal_start()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void c_base_dev_cmd::signal_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
