/****************************************************************************
** Meta object code from reading C++ file 'mydialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../zhucejiemian/mydialog.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mydialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MyDialog_t {
    uint offsetsAndSizes[20];
    char stringdata0[9];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[22];
    char stringdata4[8];
    char stringdata5[17];
    char stringdata6[16];
    char stringdata7[17];
    char stringdata8[15];
    char stringdata9[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MyDialog_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MyDialog_t qt_meta_stringdata_MyDialog = {
    {
        QT_MOC_LITERAL(0, 8),  // "MyDialog"
        QT_MOC_LITERAL(9, 15),  // "on_exit_clicked"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 21),  // "on_Xiahuaxian_clicked"
        QT_MOC_LITERAL(48, 7),  // "checked"
        QT_MOC_LITERAL(56, 16),  // "on_Xieti_clicked"
        QT_MOC_LITERAL(73, 15),  // "on_Cuti_clicked"
        QT_MOC_LITERAL(89, 16),  // "on_Black_clicked"
        QT_MOC_LITERAL(106, 14),  // "on_Red_clicked"
        QT_MOC_LITERAL(121, 15)   // "on_Blue_clicked"
    },
    "MyDialog",
    "on_exit_clicked",
    "",
    "on_Xiahuaxian_clicked",
    "checked",
    "on_Xieti_clicked",
    "on_Cuti_clicked",
    "on_Black_clicked",
    "on_Red_clicked",
    "on_Blue_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MyDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    1,   57,    2, 0x08,    2 /* Private */,
       5,    1,   60,    2, 0x08,    4 /* Private */,
       6,    1,   63,    2, 0x08,    6 /* Private */,
       7,    0,   66,    2, 0x08,    8 /* Private */,
       8,    0,   67,    2, 0x08,    9 /* Private */,
       9,    0,   68,    2, 0x08,   10 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MyDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_MyDialog.offsetsAndSizes,
    qt_meta_data_MyDialog,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MyDialog_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MyDialog, std::true_type>,
        // method 'on_exit_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Xiahuaxian_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_Xieti_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_Cuti_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_Black_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Red_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Blue_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MyDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_exit_clicked(); break;
        case 1: _t->on_Xiahuaxian_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->on_Xieti_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->on_Cuti_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->on_Black_clicked(); break;
        case 5: _t->on_Red_clicked(); break;
        case 6: _t->on_Blue_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MyDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
