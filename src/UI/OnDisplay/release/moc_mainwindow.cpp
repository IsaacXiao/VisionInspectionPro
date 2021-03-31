/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWnd_t {
    QByteArrayData data[10];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWnd_t qt_meta_stringdata_MainWnd = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MainWnd"
QT_MOC_LITERAL(1, 8, 13), // "OnNavBtnClick"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "OnStartBtnClick"
QT_MOC_LITERAL(4, 39, 14), // "OnStopBtnClick"
QT_MOC_LITERAL(5, 54, 9), // "OnTrigger"
QT_MOC_LITERAL(6, 64, 14), // "OnSetBackImage"
QT_MOC_LITERAL(7, 79, 3), // "pos"
QT_MOC_LITERAL(8, 83, 10), // "ImgTypePtr"
QT_MOC_LITERAL(9, 94, 3) // "img"

    },
    "MainWnd\0OnNavBtnClick\0\0OnStartBtnClick\0"
    "OnStopBtnClick\0OnTrigger\0OnSetBackImage\0"
    "pos\0ImgTypePtr\0img"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWnd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    2,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, 0x80000000 | 8,    7,    9,

       0        // eod
};

void MainWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnNavBtnClick(); break;
        case 1: _t->OnStartBtnClick(); break;
        case 2: _t->OnStopBtnClick(); break;
        case 3: _t->OnTrigger(); break;
        case 4: _t->OnSetBackImage((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< ImgTypePtr(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWnd::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWnd.data,
    qt_meta_data_MainWnd,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWnd.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
