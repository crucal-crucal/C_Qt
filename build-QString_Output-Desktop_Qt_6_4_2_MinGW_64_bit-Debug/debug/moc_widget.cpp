/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QString_Output/widget.h"
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
    uint offsetsAndSizes[14];
    char stringdata0[7];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[19];
    char stringdata5[19];
    char stringdata6[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Widget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
        QT_MOC_LITERAL(0, 6),  // "Widget"
        QT_MOC_LITERAL(7, 18),  // "on_Btn_sum_clicked"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 20),  // "on_Btn_debug_clicked"
        QT_MOC_LITERAL(48, 18),  // "on_Btn_DEC_clicked"
        QT_MOC_LITERAL(67, 18),  // "on_Btn_BIN_clicked"
        QT_MOC_LITERAL(86, 18)   // "on_Btn_HEX_clicked"
    },
    "Widget",
    "on_Btn_sum_clicked",
    "",
    "on_Btn_debug_clicked",
    "on_Btn_DEC_clicked",
    "on_Btn_BIN_clicked",
    "on_Btn_HEX_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Widget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    0,   45,    2, 0x08,    2 /* Private */,
       4,    0,   46,    2, 0x08,    3 /* Private */,
       5,    0,   47,    2, 0x08,    4 /* Private */,
       6,    0,   48,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        // method 'on_Btn_sum_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Btn_debug_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Btn_DEC_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Btn_BIN_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Btn_HEX_clicked'
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
        case 0: _t->on_Btn_sum_clicked(); break;
        case 1: _t->on_Btn_debug_clicked(); break;
        case 2: _t->on_Btn_DEC_clicked(); break;
        case 3: _t->on_Btn_BIN_clicked(); break;
        case 4: _t->on_Btn_HEX_clicked(); break;
        default: ;
        }
    }
    (void)_a;
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
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
