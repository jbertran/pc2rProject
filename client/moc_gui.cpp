/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x05,
      18,    4,    4,    4, 0x05,
      38,   32,    4,    4, 0x05,
      75,   70,    4,    4, 0x05,
      98,    4,    4,    4, 0x05,
     110,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
     124,    4,    4,    4, 0x0a,
     138,  134,    4,    4, 0x0a,
     181,  176,    4,    4, 0x0a,
     228,  176,    4,    4, 0x0a,
     272,  176,    4,    4, 0x0a,
     316,  176,    4,    4, 0x0a,
     360,  176,    4,    4, 0x0a,
     407,  176,    4,    4, 0x0a,
     454,  176,    4,    4, 0x0a,
     498,  176,    4,    4, 0x0a,
     544,  176,    4,    4, 0x0a,
     590,  176,    4,    4, 0x0a,
     637,  176,    4,    4, 0x0a,
     685,  176,    4,    4, 0x0a,
     731,  176,    4,    4, 0x0a,
     777,  176,    4,    4, 0x0a,
     824,  176,    4,    4, 0x0a,
     874,  176,    4,    4, 0x0a,
     920,  176,    4,    4, 0x0a,
     967,  176,    4,    4, 0x0a,
    1013,  176,    4,    4, 0x0a,
    1061,  176,    4,    4, 0x0a,
    1108,    4,    4,    4, 0x0a,
    1119,    4,    4,    4, 0x0a,
    1130, 1128,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GUI[] = {
    "GUI\0\0resetBoard()\0updateBoard()\0x,y,d\0"
    "addWallBoard(int,int,direction)\0c,co\0"
    "moveRobot(color,coord)\0beginEnch()\0"
    "yourTurnSol()\0hskDone()\0msg\0"
    "gui_handleUnknownMessage(std::string)\0"
    "args\0gui_handleConnectMsg(std::vector<std::string>)\0"
    "gui_handleLeftMsg(std::vector<std::string>)\0"
    "gui_handleDiscMsg(std::vector<std::string>)\0"
    "gui_handleChatMsg(std::vector<std::string>)\0"
    "gui_handleWelcomeMsg(std::vector<std::string>)\0"
    "gui_handleSessionMsg(std::vector<std::string>)\0"
    "gui_handleTurnMsg(std::vector<std::string>)\0"
    "gui_handleWinnerMsg(std::vector<std::string>)\0"
    "gui_handleUFoundMsg(std::vector<std::string>)\0"
    "gui_handleHeFoundMsg(std::vector<std::string>)\0"
    "gui_handleEndThinkMsg(std::vector<std::string>)\0"
    "gui_handleYouBidMsg(std::vector<std::string>)\0"
    "gui_handleHeBidsMsg(std::vector<std::string>)\0"
    "gui_handleFailBidMsg(std::vector<std::string>)\0"
    "gui_handleEndAuctionMsg(std::vector<std::string>)\0"
    "gui_handleHisSolMsg(std::vector<std::string>)\0"
    "gui_handleGoodSolMsg(std::vector<std::string>)\0"
    "gui_handleBadSolMsg(std::vector<std::string>)\0"
    "gui_handleEndSolveMsg(std::vector<std::string>)\0"
    "gui_handleTimeoutMsg(std::vector<std::string>)\0"
    "encherir()\0trouve()\0s\0"
    "clientSendMoves(std::string)\0"
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUI *_t = static_cast<GUI *>(_o);
        switch (_id) {
        case 0: _t->resetBoard(); break;
        case 1: _t->updateBoard(); break;
        case 2: _t->addWallBoard((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< direction(*)>(_a[3]))); break;
        case 3: _t->moveRobot((*reinterpret_cast< color(*)>(_a[1])),(*reinterpret_cast< coord(*)>(_a[2]))); break;
        case 4: _t->beginEnch(); break;
        case 5: _t->yourTurnSol(); break;
        case 6: _t->hskDone(); break;
        case 7: _t->gui_handleUnknownMessage((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 8: _t->gui_handleConnectMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 9: _t->gui_handleLeftMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 10: _t->gui_handleDiscMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 11: _t->gui_handleChatMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 12: _t->gui_handleWelcomeMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 13: _t->gui_handleSessionMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 14: _t->gui_handleTurnMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 15: _t->gui_handleWinnerMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 16: _t->gui_handleUFoundMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 17: _t->gui_handleHeFoundMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 18: _t->gui_handleEndThinkMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 19: _t->gui_handleYouBidMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 20: _t->gui_handleHeBidsMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 21: _t->gui_handleFailBidMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 22: _t->gui_handleEndAuctionMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 23: _t->gui_handleHisSolMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 24: _t->gui_handleGoodSolMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 25: _t->gui_handleBadSolMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 26: _t->gui_handleEndSolveMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 27: _t->gui_handleTimeoutMsg((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 28: _t->encherir(); break;
        case 29: _t->trouve(); break;
        case 30: _t->clientSendMoves((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GUI,
      qt_meta_data_GUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI))
        return static_cast<void*>(const_cast< GUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void GUI::resetBoard()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GUI::updateBoard()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GUI::addWallBoard(int _t1, int _t2, direction _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GUI::moveRobot(color _t1, coord _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GUI::beginEnch()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void GUI::yourTurnSol()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
static const uint qt_meta_data_CoupsLabel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   11,   11,   11, 0x0a,
      35,   11,   11,   11, 0x0a,
      42,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CoupsLabel[] = {
    "CoupsLabel\0\0val\0value(int)\0reset()\0"
    "incr()\0decr()\0"
};

void CoupsLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CoupsLabel *_t = static_cast<CoupsLabel *>(_o);
        switch (_id) {
        case 0: _t->value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->reset(); break;
        case 2: _t->incr(); break;
        case 3: _t->decr(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CoupsLabel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CoupsLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_CoupsLabel,
      qt_meta_data_CoupsLabel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CoupsLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CoupsLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CoupsLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CoupsLabel))
        return static_cast<void*>(const_cast< CoupsLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int CoupsLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CoupsLabel::value(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
