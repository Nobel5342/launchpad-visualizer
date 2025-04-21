/****************************************************************************
** Meta object code from reading C++ file 'MidiManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/midi/MidiManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MidiManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MidiManager_t {
    QByteArrayData data[9];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MidiManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MidiManager_t qt_meta_stringdata_MidiManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MidiManager"
QT_MOC_LITERAL(1, 12, 14), // "noteOnReceived"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "note"
QT_MOC_LITERAL(4, 33, 8), // "velocity"
QT_MOC_LITERAL(5, 42, 15), // "noteOffReceived"
QT_MOC_LITERAL(6, 58, 13), // "sysExReceived"
QT_MOC_LITERAL(7, 72, 26), // "std::vector<unsigned char>"
QT_MOC_LITERAL(8, 99, 4) // "data"

    },
    "MidiManager\0noteOnReceived\0\0note\0"
    "velocity\0noteOffReceived\0sysExReceived\0"
    "std::vector<unsigned char>\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MidiManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       5,    1,   34,    2, 0x06 /* Public */,
       6,    1,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void MidiManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MidiManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->noteOnReceived((*reinterpret_cast< unsigned char(*)>(_a[1])),(*reinterpret_cast< unsigned char(*)>(_a[2]))); break;
        case 1: _t->noteOffReceived((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 2: _t->sysExReceived((*reinterpret_cast< const std::vector<unsigned char>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MidiManager::*)(unsigned char , unsigned char );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MidiManager::noteOnReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MidiManager::*)(unsigned char );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MidiManager::noteOffReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MidiManager::*)(const std::vector<unsigned char> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MidiManager::sysExReceived)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MidiManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MidiManager.data,
    qt_meta_data_MidiManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MidiManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MidiManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MidiManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MidiManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void MidiManager::noteOnReceived(unsigned char _t1, unsigned char _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MidiManager::noteOffReceived(unsigned char _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MidiManager::sysExReceived(const std::vector<unsigned char> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
