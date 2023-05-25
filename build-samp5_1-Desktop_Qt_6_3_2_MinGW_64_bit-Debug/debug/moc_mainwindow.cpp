/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../samp5_1ListModel/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[34];
    char stringdata0[11];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[25];
    char stringdata5[25];
    char stringdata6[24];
    char stringdata7[20];
    char stringdata8[12];
    char stringdata9[6];
    char stringdata10[24];
    char stringdata11[25];
    char stringdata12[23];
    char stringdata13[8];
    char stringdata14[25];
    char stringdata15[27];
    char stringdata16[23];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 21),  // "on_btnIniList_clicked"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 24),  // "on_btnListAppend_clicked"
        QT_MOC_LITERAL(59, 24),  // "on_btnListInsert_clicked"
        QT_MOC_LITERAL(84, 24),  // "on_btnListDelete_clicked"
        QT_MOC_LITERAL(109, 23),  // "on_btnListClear_clicked"
        QT_MOC_LITERAL(133, 19),  // "on_listView_clicked"
        QT_MOC_LITERAL(153, 11),  // "QModelIndex"
        QT_MOC_LITERAL(165, 5),  // "index"
        QT_MOC_LITERAL(171, 23),  // "on_btnTextClear_clicked"
        QT_MOC_LITERAL(195, 24),  // "on_btnTextImport_clicked"
        QT_MOC_LITERAL(220, 22),  // "on_btnListSort_clicked"
        QT_MOC_LITERAL(243, 7),  // "checked"
        QT_MOC_LITERAL(251, 24),  // "on_btnListMoveUp_clicked"
        QT_MOC_LITERAL(276, 26),  // "on_btnListMoveDown_clicked"
        QT_MOC_LITERAL(303, 22)   // "on_chkEditable_clicked"
    },
    "MainWindow",
    "on_btnIniList_clicked",
    "",
    "on_btnListAppend_clicked",
    "on_btnListInsert_clicked",
    "on_btnListDelete_clicked",
    "on_btnListClear_clicked",
    "on_listView_clicked",
    "QModelIndex",
    "index",
    "on_btnTextClear_clicked",
    "on_btnTextImport_clicked",
    "on_btnListSort_clicked",
    "checked",
    "on_btnListMoveUp_clicked",
    "on_btnListMoveDown_clicked",
    "on_chkEditable_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x08,    1 /* Private */,
       3,    0,   87,    2, 0x08,    2 /* Private */,
       4,    0,   88,    2, 0x08,    3 /* Private */,
       5,    0,   89,    2, 0x08,    4 /* Private */,
       6,    0,   90,    2, 0x08,    5 /* Private */,
       7,    1,   91,    2, 0x08,    6 /* Private */,
      10,    0,   94,    2, 0x08,    8 /* Private */,
      11,    0,   95,    2, 0x08,    9 /* Private */,
      12,    1,   96,    2, 0x08,   10 /* Private */,
      14,    0,   99,    2, 0x08,   12 /* Private */,
      15,    0,  100,    2, 0x08,   13 /* Private */,
      16,    1,  101,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_btnIniList_clicked(); break;
        case 1: _t->on_btnListAppend_clicked(); break;
        case 2: _t->on_btnListInsert_clicked(); break;
        case 3: _t->on_btnListDelete_clicked(); break;
        case 4: _t->on_btnListClear_clicked(); break;
        case 5: _t->on_listView_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 6: _t->on_btnTextClear_clicked(); break;
        case 7: _t->on_btnTextImport_clicked(); break;
        case 8: _t->on_btnListSort_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->on_btnListMoveUp_clicked(); break;
        case 10: _t->on_btnListMoveDown_clicked(); break;
        case 11: _t->on_chkEditable_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
