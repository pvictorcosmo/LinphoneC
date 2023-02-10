/****************************************************************************
** Meta object code from reading C++ file 'Linphone.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Core/Linphone.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Linphone.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LinphoneWorker_t {
    QByteArrayData data[5];
    char stringdata0[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LinphoneWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LinphoneWorker_t qt_meta_stringdata_LinphoneWorker = {
    {
QT_MOC_LITERAL(0, 0, 14), // "LinphoneWorker"
QT_MOC_LITERAL(1, 15, 12), // "callReceived"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 6), // "result"
QT_MOC_LITERAL(4, 36, 6) // "doWork"

    },
    "LinphoneWorker\0callReceived\0\0result\0"
    "doWork"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LinphoneWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void LinphoneWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LinphoneWorker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->callReceived((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 1: _t->doWork(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LinphoneWorker::*)(const bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinphoneWorker::callReceived)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LinphoneWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LinphoneWorker.data,
    qt_meta_data_LinphoneWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LinphoneWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LinphoneWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LinphoneWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LinphoneWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LinphoneWorker::callReceived(const bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_LinphoneController_t {
    QByteArrayData data[19];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LinphoneController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LinphoneController_t qt_meta_stringdata_LinphoneController = {
    {
QT_MOC_LITERAL(0, 0, 18), // "LinphoneController"
QT_MOC_LITERAL(1, 19, 7), // "operate"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "openCall"
QT_MOC_LITERAL(4, 37, 10), // "acceptCall"
QT_MOC_LITERAL(5, 48, 11), // "declineCall"
QT_MOC_LITERAL(6, 60, 13), // "declineInCall"
QT_MOC_LITERAL(7, 74, 9), // "callingOk"
QT_MOC_LITERAL(8, 84, 8), // "callInit"
QT_MOC_LITERAL(9, 93, 8), // "muteCall"
QT_MOC_LITERAL(10, 102, 14), // "onCallReceived"
QT_MOC_LITERAL(11, 117, 6), // "result"
QT_MOC_LITERAL(12, 124, 10), // "initThread"
QT_MOC_LITERAL(13, 135, 6), // "accept"
QT_MOC_LITERAL(14, 142, 7), // "decline"
QT_MOC_LITERAL(15, 150, 12), // "decline_call"
QT_MOC_LITERAL(16, 163, 15), // "linphoneCalling"
QT_MOC_LITERAL(17, 179, 18), // "callInitialization"
QT_MOC_LITERAL(18, 198, 9) // "mute_call"

    },
    "LinphoneController\0operate\0\0openCall\0"
    "acceptCall\0declineCall\0declineInCall\0"
    "callingOk\0callInit\0muteCall\0onCallReceived\0"
    "result\0initThread\0accept\0decline\0"
    "decline_call\0linphoneCalling\0"
    "callInitialization\0mute_call"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LinphoneController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    0,   96,    2, 0x06 /* Public */,
       5,    0,   97,    2, 0x06 /* Public */,
       6,    0,   98,    2, 0x06 /* Public */,
       7,    0,   99,    2, 0x06 /* Public */,
       8,    0,  100,    2, 0x06 /* Public */,
       9,    0,  101,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  102,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      12,    0,  105,    2, 0x02 /* Public */,
      13,    0,  106,    2, 0x02 /* Public */,
      14,    0,  107,    2, 0x02 /* Public */,
      15,    0,  108,    2, 0x02 /* Public */,
      16,    0,  109,    2, 0x02 /* Public */,
      17,    0,  110,    2, 0x02 /* Public */,
      18,    0,  111,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   11,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LinphoneController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LinphoneController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->operate(); break;
        case 1: _t->openCall(); break;
        case 2: _t->acceptCall(); break;
        case 3: _t->declineCall(); break;
        case 4: _t->declineInCall(); break;
        case 5: _t->callingOk(); break;
        case 6: _t->callInit(); break;
        case 7: _t->muteCall(); break;
        case 8: _t->onCallReceived((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 9: _t->initThread(); break;
        case 10: _t->accept(); break;
        case 11: _t->decline(); break;
        case 12: _t->decline_call(); break;
        case 13: { int _r = _t->linphoneCalling();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->callInitialization(); break;
        case 15: _t->mute_call(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LinphoneController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinphoneController::operate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LinphoneController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinphoneController::openCall)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LinphoneController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinphoneController::acceptCall)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LinphoneController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinphoneController::declineCall)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LinphoneController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinphoneController::declineInCall)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LinphoneController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinphoneController::callingOk)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (LinphoneController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinphoneController::callInit)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (LinphoneController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinphoneController::muteCall)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LinphoneController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LinphoneController.data,
    qt_meta_data_LinphoneController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LinphoneController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LinphoneController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LinphoneController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LinphoneController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void LinphoneController::operate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LinphoneController::openCall()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LinphoneController::acceptCall()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LinphoneController::declineCall()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void LinphoneController::declineInCall()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void LinphoneController::callingOk()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void LinphoneController::callInit()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void LinphoneController::muteCall()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
