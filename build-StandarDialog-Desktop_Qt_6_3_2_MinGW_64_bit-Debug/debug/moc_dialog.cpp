/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../StandarDialog/dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_t {
    uint offsetsAndSizes[20];
    char stringdata0[7];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[21];
    char stringdata5[24];
    char stringdata6[20];
    char stringdata7[24];
    char stringdata8[20];
    char stringdata9[23];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Dialog_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_Dialog_t qt_meta_stringdata_Dialog = {
    {
        QT_MOC_LITERAL(0, 6),  // "Dialog"
        QT_MOC_LITERAL(7, 21),  // "on_pushButton_clicked"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 20),  // "on_Btn_color_clicked"
        QT_MOC_LITERAL(51, 20),  // "on_Btn_input_clicked"
        QT_MOC_LITERAL(72, 23),  // "on_Btn_progress_clicked"
        QT_MOC_LITERAL(96, 19),  // "on_Btn_file_clicked"
        QT_MOC_LITERAL(116, 23),  // "on_Btn_existing_clicked"
        QT_MOC_LITERAL(140, 19),  // "on_Btn_save_clicked"
        QT_MOC_LITERAL(160, 22)   // "on_Btn_massage_clicked"
    },
    "Dialog",
    "on_pushButton_clicked",
    "",
    "on_Btn_color_clicked",
    "on_Btn_input_clicked",
    "on_Btn_progress_clicked",
    "on_Btn_file_clicked",
    "on_Btn_existing_clicked",
    "on_Btn_save_clicked",
    "on_Btn_massage_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x08,    1 /* Private */,
       3,    0,   63,    2, 0x08,    2 /* Private */,
       4,    0,   64,    2, 0x08,    3 /* Private */,
       5,    0,   65,    2, 0x08,    4 /* Private */,
       6,    0,   66,    2, 0x08,    5 /* Private */,
       7,    0,   67,    2, 0x08,    6 /* Private */,
       8,    0,   68,    2, 0x08,    7 /* Private */,
       9,    0,   69,    2, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_Btn_color_clicked(); break;
        case 2: _t->on_Btn_input_clicked(); break;
        case 3: _t->on_Btn_progress_clicked(); break;
        case 4: _t->on_Btn_file_clicked(); break;
        case 5: _t->on_Btn_existing_clicked(); break;
        case 6: _t->on_Btn_save_clicked(); break;
        case 7: _t->on_Btn_massage_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject Dialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Dialog.offsetsAndSizes,
    qt_meta_data_Dialog,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Dialog_t
, QtPrivate::TypeAndForceComplete<Dialog, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
