/****************************************************************************
** Meta object code from reading C++ file 'tune_thr.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tune_thr.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tune_thr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_c_tune_thr_t {
    QByteArrayData data[12];
    char stringdata[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_tune_thr_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_tune_thr_t qt_meta_stringdata_c_tune_thr = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 19),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 17),
QT_MOC_LITERAL(4, 50, 17),
QT_MOC_LITERAL(5, 68, 21),
QT_MOC_LITERAL(6, 90, 15),
QT_MOC_LITERAL(7, 106, 18),
QT_MOC_LITERAL(8, 125, 19),
QT_MOC_LITERAL(9, 145, 17),
QT_MOC_LITERAL(10, 163, 12),
QT_MOC_LITERAL(11, 176, 6)
    },
    "c_tune_thr\0signal_unsuccesfull\0\0"
    "signal_succesfull\0signal_wrong_mode\0"
    "signal_connect_setted\0signal_draw_osc\0"
    "signal_draw_spectr\0signal_collect_amps\0"
    "req_timer_timeout\0on_off_timer\0on_off"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_tune_thr[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,
       6,    0,   63,    2, 0x06 /* Public */,
       7,    0,   64,    2, 0x06 /* Public */,
       8,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   68,    2, 0x09 /* Protected */,
      10,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,

       0        // eod
};

void c_tune_thr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        c_tune_thr *_t = static_cast<c_tune_thr *>(_o);
        switch (_id) {
        case 0: _t->signal_unsuccesfull(); break;
        case 1: _t->signal_succesfull(); break;
        case 2: _t->signal_wrong_mode(); break;
        case 3: _t->signal_connect_setted(); break;
        case 4: _t->signal_draw_osc(); break;
        case 5: _t->signal_draw_spectr(); break;
        case 6: _t->signal_collect_amps((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->req_timer_timeout(); break;
        case 8: _t->on_off_timer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (c_tune_thr::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_tune_thr::signal_unsuccesfull)) {
                *result = 0;
            }
        }
        {
            typedef void (c_tune_thr::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_tune_thr::signal_succesfull)) {
                *result = 1;
            }
        }
        {
            typedef void (c_tune_thr::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_tune_thr::signal_wrong_mode)) {
                *result = 2;
            }
        }
        {
            typedef void (c_tune_thr::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_tune_thr::signal_connect_setted)) {
                *result = 3;
            }
        }
        {
            typedef void (c_tune_thr::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_tune_thr::signal_draw_osc)) {
                *result = 4;
            }
        }
        {
            typedef void (c_tune_thr::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_tune_thr::signal_draw_spectr)) {
                *result = 5;
            }
        }
        {
            typedef void (c_tune_thr::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&c_tune_thr::signal_collect_amps)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject c_tune_thr::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_c_tune_thr.data,
      qt_meta_data_c_tune_thr,  qt_static_metacall, 0, 0}
};


const QMetaObject *c_tune_thr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_tune_thr::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_c_tune_thr.stringdata))
        return static_cast<void*>(const_cast< c_tune_thr*>(this));
    return QObject::qt_metacast(_clname);
}

int c_tune_thr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void c_tune_thr::signal_unsuccesfull()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void c_tune_thr::signal_succesfull()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void c_tune_thr::signal_wrong_mode()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void c_tune_thr::signal_connect_setted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void c_tune_thr::signal_draw_osc()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void c_tune_thr::signal_draw_spectr()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void c_tune_thr::signal_collect_amps(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
