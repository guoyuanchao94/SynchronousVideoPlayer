/****************************************************************************
** Meta object code from reading C++ file 'connecttoserver.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../connecttoserver.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connecttoserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSConnectToServerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSConnectToServerENDCLASS = QtMocHelpers::stringData(
    "ConnectToServer",
    "connectToServer",
    "",
    "url",
    "port",
    "connectToUdpServer",
    "setUserName",
    "username",
    "setServerURL",
    "on_buttonBox_accepted",
    "on_TextChanged",
    "text"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSConnectToServerENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[16];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[5];
    char stringdata5[19];
    char stringdata6[12];
    char stringdata7[9];
    char stringdata8[13];
    char stringdata9[22];
    char stringdata10[15];
    char stringdata11[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSConnectToServerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSConnectToServerENDCLASS_t qt_meta_stringdata_CLASSConnectToServerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "ConnectToServer"
        QT_MOC_LITERAL(16, 15),  // "connectToServer"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 3),  // "url"
        QT_MOC_LITERAL(37, 4),  // "port"
        QT_MOC_LITERAL(42, 18),  // "connectToUdpServer"
        QT_MOC_LITERAL(61, 11),  // "setUserName"
        QT_MOC_LITERAL(73, 8),  // "username"
        QT_MOC_LITERAL(82, 12),  // "setServerURL"
        QT_MOC_LITERAL(95, 21),  // "on_buttonBox_accepted"
        QT_MOC_LITERAL(117, 14),  // "on_TextChanged"
        QT_MOC_LITERAL(132, 4)   // "text"
    },
    "ConnectToServer",
    "connectToServer",
    "",
    "url",
    "port",
    "connectToUdpServer",
    "setUserName",
    "username",
    "setServerURL",
    "on_buttonBox_accepted",
    "on_TextChanged",
    "text"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSConnectToServerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   50,    2, 0x06,    1 /* Public */,
       5,    2,   55,    2, 0x06,    4 /* Public */,
       6,    1,   60,    2, 0x06,    7 /* Public */,
       8,    1,   63,    2, 0x06,    9 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   66,    2, 0x08,   11 /* Private */,
      10,    1,   67,    2, 0x08,   12 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QUrl, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QUrl, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QUrl,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject ConnectToServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSConnectToServerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSConnectToServerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSConnectToServerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ConnectToServer, std::true_type>,
        // method 'connectToServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QUrl, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'connectToUdpServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QUrl, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setUserName'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setServerURL'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QUrl, std::false_type>,
        // method 'on_buttonBox_accepted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_TextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void ConnectToServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConnectToServer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connectToServer((*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->connectToUdpServer((*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->setUserName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->setServerURL((*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[1]))); break;
        case 4: _t->on_buttonBox_accepted(); break;
        case 5: _t->on_TextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConnectToServer::*)(QUrl , int );
            if (_t _q_method = &ConnectToServer::connectToServer; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConnectToServer::*)(QUrl , int );
            if (_t _q_method = &ConnectToServer::connectToUdpServer; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConnectToServer::*)(QString );
            if (_t _q_method = &ConnectToServer::setUserName; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ConnectToServer::*)(QUrl );
            if (_t _q_method = &ConnectToServer::setServerURL; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *ConnectToServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectToServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSConnectToServerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ConnectToServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ConnectToServer::connectToServer(QUrl _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConnectToServer::connectToUdpServer(QUrl _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConnectToServer::setUserName(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ConnectToServer::setServerURL(QUrl _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
