/****************************************************************************
** Meta object code from reading C++ file 'QMyCameraThread.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Clients/QMyCameraThread.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMyCameraThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMyCameraThread_t {
    uint offsetsAndSizes[18];
    char stringdata0[16];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[24];
    char stringdata4[26];
    char stringdata5[17];
    char stringdata6[18];
    char stringdata7[12];
    char stringdata8[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QMyCameraThread_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_QMyCameraThread_t qt_meta_stringdata_QMyCameraThread = {
    {
        QT_MOC_LITERAL(0, 15),  // "QMyCameraThread"
        QT_MOC_LITERAL(16, 16),  // "forwardCameraPic"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 23),  // "forward_shareDesktopPic"
        QT_MOC_LITERAL(58, 25),  // "forward_sendServerDeskPic"
        QT_MOC_LITERAL(84, 16),  // "stopShareDesktop"
        QT_MOC_LITERAL(101, 17),  // "startShareDesktop"
        QT_MOC_LITERAL(119, 11),  // "startCamera"
        QT_MOC_LITERAL(131, 10)   // "stopCamera"
    },
    "QMyCameraThread",
    "forwardCameraPic",
    "",
    "forward_shareDesktopPic",
    "forward_sendServerDeskPic",
    "stopShareDesktop",
    "startShareDesktop",
    "startCamera",
    "stopCamera"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMyCameraThread[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       3,    1,   59,    2, 0x06,    3 /* Public */,
       4,    1,   62,    2, 0x06,    5 /* Public */,
       5,    0,   65,    2, 0x06,    7 /* Public */,
       6,    0,   66,    2, 0x06,    8 /* Public */,
       7,    0,   67,    2, 0x06,    9 /* Public */,
       8,    0,   68,    2, 0x06,   10 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QMyCameraThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QMyCameraThread *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->forwardCameraPic((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 1: _t->forward_shareDesktopPic((*reinterpret_cast< std::add_pointer_t<QPixmap>>(_a[1]))); break;
        case 2: _t->forward_sendServerDeskPic((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 3: _t->stopShareDesktop(); break;
        case 4: _t->startShareDesktop(); break;
        case 5: _t->startCamera(); break;
        case 6: _t->stopCamera(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QMyCameraThread::*)(QImage );
            if (_t _q_method = &QMyCameraThread::forwardCameraPic; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QMyCameraThread::*)(QPixmap );
            if (_t _q_method = &QMyCameraThread::forward_shareDesktopPic; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QMyCameraThread::*)(QByteArray );
            if (_t _q_method = &QMyCameraThread::forward_sendServerDeskPic; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QMyCameraThread::*)();
            if (_t _q_method = &QMyCameraThread::stopShareDesktop; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QMyCameraThread::*)();
            if (_t _q_method = &QMyCameraThread::startShareDesktop; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QMyCameraThread::*)();
            if (_t _q_method = &QMyCameraThread::startCamera; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QMyCameraThread::*)();
            if (_t _q_method = &QMyCameraThread::stopCamera; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject QMyCameraThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_QMyCameraThread.offsetsAndSizes,
    qt_meta_data_QMyCameraThread,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QMyCameraThread_t
, QtPrivate::TypeAndForceComplete<QMyCameraThread, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QImage, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QPixmap, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *QMyCameraThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMyCameraThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QMyCameraThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int QMyCameraThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void QMyCameraThread::forwardCameraPic(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QMyCameraThread::forward_shareDesktopPic(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QMyCameraThread::forward_sendServerDeskPic(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QMyCameraThread::stopShareDesktop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QMyCameraThread::startShareDesktop()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QMyCameraThread::startCamera()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QMyCameraThread::stopCamera()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
