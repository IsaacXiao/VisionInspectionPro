/****************************************************************************
** Meta object code from reading C++ file 'CameraShot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../CameraShot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CameraShot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CameraShot_t {
    QByteArrayData data[6];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraShot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraShot_t qt_meta_stringdata_CameraShot = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CameraShot"
QT_MOC_LITERAL(1, 11, 14), // "sigSoftTrigger"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "num"
QT_MOC_LITERAL(4, 31, 12), // "sigOpenImage"
QT_MOC_LITERAL(5, 44, 10) // "sigSaveROI"

    },
    "CameraShot\0sigSoftTrigger\0\0num\0"
    "sigOpenImage\0sigSaveROI"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraShot[] = {

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
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       5,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void CameraShot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CameraShot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigSoftTrigger((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sigOpenImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sigSaveROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CameraShot::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraShot::sigSoftTrigger)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CameraShot::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraShot::sigOpenImage)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CameraShot::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraShot::sigSaveROI)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CameraShot::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_CameraShot.data,
    qt_meta_data_CameraShot,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CameraShot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraShot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CameraShot.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int CameraShot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
void CameraShot::sigSoftTrigger(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CameraShot::sigOpenImage(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CameraShot::sigSaveROI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
