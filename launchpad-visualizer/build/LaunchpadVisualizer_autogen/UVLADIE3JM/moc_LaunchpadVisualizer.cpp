/****************************************************************************
** Meta object code from reading C++ file 'LaunchpadVisualizer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/LaunchpadVisualizer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LaunchpadVisualizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LaunchpadVisualizer_t {
    QByteArrayData data[15];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LaunchpadVisualizer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LaunchpadVisualizer_t qt_meta_stringdata_LaunchpadVisualizer = {
    {
QT_MOC_LITERAL(0, 0, 19), // "LaunchpadVisualizer"
QT_MOC_LITERAL(1, 20, 10), // "padPressed"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 1), // "x"
QT_MOC_LITERAL(4, 34, 1), // "y"
QT_MOC_LITERAL(5, 36, 8), // "velocity"
QT_MOC_LITERAL(6, 45, 11), // "padReleased"
QT_MOC_LITERAL(7, 57, 15), // "padColorChanged"
QT_MOC_LITERAL(8, 73, 5), // "color"
QT_MOC_LITERAL(9, 79, 8), // "onNoteOn"
QT_MOC_LITERAL(10, 88, 4), // "note"
QT_MOC_LITERAL(11, 93, 9), // "onNoteOff"
QT_MOC_LITERAL(12, 103, 7), // "onSysEx"
QT_MOC_LITERAL(13, 111, 26), // "std::vector<unsigned char>"
QT_MOC_LITERAL(14, 138, 4) // "data"

    },
    "LaunchpadVisualizer\0padPressed\0\0x\0y\0"
    "velocity\0padReleased\0padColorChanged\0"
    "color\0onNoteOn\0note\0onNoteOff\0onSysEx\0"
    "std::vector<unsigned char>\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LaunchpadVisualizer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x06 /* Public */,
       6,    2,   51,    2, 0x06 /* Public */,
       7,    3,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,   63,    2, 0x0a /* Public */,
      11,    1,   68,    2, 0x0a /* Public */,
      12,    1,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QColor,    3,    4,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,   10,    5,
    QMetaType::Void, QMetaType::UChar,   10,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void LaunchpadVisualizer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LaunchpadVisualizer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->padPressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->padReleased((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->padColorChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QColor(*)>(_a[3]))); break;
        case 3: _t->onNoteOn((*reinterpret_cast< unsigned char(*)>(_a[1])),(*reinterpret_cast< unsigned char(*)>(_a[2]))); break;
        case 4: _t->onNoteOff((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 5: _t->onSysEx((*reinterpret_cast< const std::vector<unsigned char>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LaunchpadVisualizer::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LaunchpadVisualizer::padPressed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LaunchpadVisualizer::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LaunchpadVisualizer::padReleased)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LaunchpadVisualizer::*)(int , int , QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LaunchpadVisualizer::padColorChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LaunchpadVisualizer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LaunchpadVisualizer.data,
    qt_meta_data_LaunchpadVisualizer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LaunchpadVisualizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LaunchpadVisualizer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LaunchpadVisualizer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LaunchpadVisualizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void LaunchpadVisualizer::padPressed(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LaunchpadVisualizer::padReleased(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LaunchpadVisualizer::padColorChanged(int _t1, int _t2, QColor _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
