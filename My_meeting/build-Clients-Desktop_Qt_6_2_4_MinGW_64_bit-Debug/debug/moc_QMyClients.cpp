/****************************************************************************
** Meta object code from reading C++ file 'QMyClients.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Clients/QMyClients.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMyClients.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMyClients_t {
    const uint offsetsAndSize[24];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QMyClients_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QMyClients_t qt_meta_stringdata_QMyClients = {
    {
QT_MOC_LITERAL(0, 10), // "QMyClients"
QT_MOC_LITERAL(11, 15), // "connectToServer"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 17), // "sendVideoToServer"
QT_MOC_LITERAL(46, 3), // "map"
QT_MOC_LITERAL(50, 22), // "sendUserMessgeToServer"
QT_MOC_LITERAL(73, 17), // "sendAudiotoServer"
QT_MOC_LITERAL(91, 18), // "sendMessageToSever"
QT_MOC_LITERAL(110, 4), // "text"
QT_MOC_LITERAL(115, 19), // "sendDeskTopToServer"
QT_MOC_LITERAL(135, 11), // "target_data"
QT_MOC_LITERAL(147, 11) // "ReadAllData"

    },
    "QMyClients\0connectToServer\0\0"
    "sendVideoToServer\0map\0sendUserMessgeToServer\0"
    "sendAudiotoServer\0sendMessageToSever\0"
    "text\0sendDeskTopToServer\0target_data\0"
    "ReadAllData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMyClients[] = {

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
       1,    0,   56,    2, 0x0a,    1 /* Public */,
       3,    1,   57,    2, 0x0a,    2 /* Public */,
       5,    0,   60,    2, 0x0a,    4 /* Public */,
       6,    0,   61,    2, 0x0a,    5 /* Public */,
       7,    1,   62,    2, 0x0a,    6 /* Public */,
       9,    1,   65,    2, 0x0a,    8 /* Public */,
      11,    0,   68,    2, 0x08,   10 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void,

       0        // eod
};

void QMyClients::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QMyClients *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connectToServer(); break;
        case 1: _t->sendVideoToServer((*reinterpret_cast< std::add_pointer_t<QPixmap>>(_a[1]))); break;
        case 2: _t->sendUserMessgeToServer(); break;
        case 3: _t->sendAudiotoServer(); break;
        case 4: _t->sendMessageToSever((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->sendDeskTopToServer((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 6: _t->ReadAllData(); break;
        default: ;
        }
    }
}

const QMetaObject QMyClients::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QMyClients.offsetsAndSize,
    qt_meta_data_QMyClients,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QMyClients_t
, QtPrivate::TypeAndForceComplete<QMyClients, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QPixmap, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *QMyClients::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMyClients::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QMyClients.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QMyClients::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
