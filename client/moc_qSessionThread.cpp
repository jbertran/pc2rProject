/****************************************************************************
** Meta object code from reading C++ file 'qSessionThread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qSessionThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qSessionThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_qSessionThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      21,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   16,   15,   15, 0x05,
      59,   54,   15,   15, 0x05,
     102,   54,   15,   15, 0x05,
     142,   54,   15,   15, 0x05,
     182,   54,   15,   15, 0x05,
     222,   54,   15,   15, 0x05,
     265,   54,   15,   15, 0x05,
     308,   54,   15,   15, 0x05,
     348,   54,   15,   15, 0x05,
     390,   54,   15,   15, 0x05,
     432,   54,   15,   15, 0x05,
     475,   54,   15,   15, 0x05,
     519,   54,   15,   15, 0x05,
     561,   54,   15,   15, 0x05,
     603,   54,   15,   15, 0x05,
     646,   54,   15,   15, 0x05,
     692,   54,   15,   15, 0x05,
     734,   54,   15,   15, 0x05,
     777,   54,   15,   15, 0x05,
     819,   54,   15,   15, 0x05,
     863,   54,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_qSessionThread[] = {
    "qSessionThread\0\0msg\0"
    "handleUnknownMessage(std::string)\0"
    "args\0handleConnectMsg(std::vector<std::string>)\0"
    "handleLeftMsg(std::vector<std::string>)\0"
    "handleDiscMsg(std::vector<std::string>)\0"
    "handleChatMsg(std::vector<std::string>)\0"
    "handleWelcomeMsg(std::vector<std::string>)\0"
    "handleSessionMsg(std::vector<std::string>)\0"
    "handleTurnMsg(std::vector<std::string>)\0"
    "handleWinnerMsg(std::vector<std::string>)\0"
    "handleUFoundMsg(std::vector<std::string>)\0"
    "handleHeFoundMsg(std::vector<std::string>)\0"
    "handleEndThinkMsg(std::vector<std::string>)\0"
    "handleYouBidMsg(std::vector<std::string>)\0"
    "handleHeBidsMsg(std::vector<std::string>)\0"
    "handleFailBidMsg(std::vector<std::string>)\0"
    "handleEndAuctionMsg(std::vector<std::string>)\0"
    "handleHisSolMsg(std::vector<std::string>)\0"
    "handleGoodSolMsg(std::vector<std::string>)\0"
    "handleBadSolMsg(std::vector<std::string>)\0"
    "handleEndSolveMsg(std::vector<std::string>)\0"
    "handleTimeoutMsg(std::vector<std::string>)\0"
};

void qSessionThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        qSessionThread *_t = static_cast<qSessionThread *>(_o);
        switch (_id) {
        case 0: _t->handleUnknownMessage((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->handleConnectMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 2: _t->handleLeftMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 3: _t->handleDiscMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 4: _t->handleChatMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 5: _t->handleWelcomeMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 6: _t->handleSessionMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 7: _t->handleTurnMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 8: _t->handleWinnerMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 9: _t->handleUFoundMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 10: _t->handleHeFoundMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 11: _t->handleEndThinkMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 12: _t->handleYouBidMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 13: _t->handleHeBidsMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 14: _t->handleFailBidMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 15: _t->handleEndAuctionMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 16: _t->handleHisSolMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 17: _t->handleGoodSolMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 18: _t->handleBadSolMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 19: _t->handleEndSolveMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 20: _t->handleTimeoutMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData qSessionThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject qSessionThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_qSessionThread,
      qt_meta_data_qSessionThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &qSessionThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *qSessionThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *qSessionThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_qSessionThread))
        return static_cast<void*>(const_cast< qSessionThread*>(this));
    return QThread::qt_metacast(_clname);
}

int qSessionThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void qSessionThread::handleUnknownMessage(std::string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qSessionThread::handleConnectMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void qSessionThread::handleLeftMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void qSessionThread::handleDiscMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void qSessionThread::handleChatMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void qSessionThread::handleWelcomeMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void qSessionThread::handleSessionMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void qSessionThread::handleTurnMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void qSessionThread::handleWinnerMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void qSessionThread::handleUFoundMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void qSessionThread::handleHeFoundMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void qSessionThread::handleEndThinkMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void qSessionThread::handleYouBidMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void qSessionThread::handleHeBidsMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void qSessionThread::handleFailBidMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void qSessionThread::handleEndAuctionMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void qSessionThread::handleHisSolMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void qSessionThread::handleGoodSolMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void qSessionThread::handleBadSolMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void qSessionThread::handleEndSolveMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void qSessionThread::handleTimeoutMsg(std::vector<std::string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}
QT_END_MOC_NAMESPACE
