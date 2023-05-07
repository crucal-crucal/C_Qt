/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Meta_object_system_properties/widget.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_Widget_t {
    uint offsetsAndSizes[30];
    char stringdata0[7];
    char stringdata1[7];
    char stringdata2[3];
    char stringdata3[8];
    char stringdata4[8];
    char stringdata5[8];
    char stringdata6[4];
    char stringdata7[20];
    char stringdata8[1];
    char stringdata9[28];
    char stringdata10[5];
    char stringdata11[14];
    char stringdata12[19];
    char stringdata13[29];
    char stringdata14[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Widget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
        QT_MOC_LITERAL(0, 6),  // "Widget"
        QT_MOC_LITERAL(7, 6),  // "author"
        QT_MOC_LITERAL(14, 2),  // "cf"
        QT_MOC_LITERAL(17, 7),  // "company"
        QT_MOC_LITERAL(25, 7),  // "icework"
        QT_MOC_LITERAL(33, 7),  // "version"
        QT_MOC_LITERAL(41, 3),  // "1.0"
        QT_MOC_LITERAL(45, 19),  // "on_Btn_Meta_clicked"
        QT_MOC_LITERAL(65, 0),  // ""
        QT_MOC_LITERAL(66, 27),  // "on_spinBox_boy_valueChanged"
        QT_MOC_LITERAL(94, 4),  // "arg1"
        QT_MOC_LITERAL(99, 13),  // "on_ageChanged"
        QT_MOC_LITERAL(113, 18),  // "on_Btn_boy_clicked"
        QT_MOC_LITERAL(132, 28),  // "on_spinBox_girl_valueChanged"
        QT_MOC_LITERAL(161, 19)   // "on_Btn_girl_clicked"
    },
    "Widget",
    "author",
    "cf",
    "company",
    "icework",
    "version",
    "1.0",
    "on_Btn_Meta_clicked",
    "",
    "on_spinBox_boy_valueChanged",
    "arg1",
    "on_ageChanged",
    "on_Btn_boy_clicked",
    "on_spinBox_girl_valueChanged",
    "on_Btn_girl_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Widget[] = {

 // content:
      10,       // revision
       0,       // classname
       3,   14, // classinfo
       6,   20, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   56,    8, 0x08,    1 /* Private */,
       9,    1,   57,    8, 0x08,    2 /* Private */,
      11,    0,   60,    8, 0x08,    4 /* Private */,
      12,    0,   61,    8, 0x08,    5 /* Private */,
      13,    1,   62,    8, 0x08,    6 /* Private */,
      14,    0,   65,    8, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Widget.offsetsAndSizes,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Widget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Widget, std::true_type>,
        // method 'on_Btn_Meta_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_spinBox_boy_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_ageChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Btn_boy_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_spinBox_girl_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_Btn_girl_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_Btn_Meta_clicked(); break;
        case 1: _t->on_spinBox_boy_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->on_ageChanged(); break;
        case 3: _t->on_Btn_boy_clicked(); break;
        case 4: _t->on_spinBox_girl_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->on_Btn_girl_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
