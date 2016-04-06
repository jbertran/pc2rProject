/****************************************************************************
** Meta object code from reading C++ file 'plateauWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "plateauWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plateauWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlateauWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      29,   14,   14,   14, 0x05,
      43,   14,   14,   14, 0x05,
      60,   58,   14,   14, 0x05,
      83,   78,   14,   14, 0x05,
     111,  105,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     140,  134,   14,   14, 0x0a,
     171,   14,   14,   14, 0x0a,
     183,   14,   14,   14, 0x0a,
     191,   14,   14,   14, 0x0a,
     198,   14,   14,   14, 0x0a,
     210,  208,   14,   14, 0x0a,
     231,  226,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PlateauWidget[] = {
    "PlateauWidget\0\0counterIncr()\0counterDecr()\0"
    "counterReset()\0c\0resetRobot(color)\0"
    "c,xy\0undoMove(color,coord)\0moves\0"
    "sendMoves(std::string)\0x,y,d\0"
    "addWallRepr(int,int,direction)\0"
    "resetRepr()\0reset()\0undo()\0valider()\0"
    "m\0addMove(s_move)\0c,co\0setRobot(color,coord)\0"
};

void PlateauWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlateauWidget *_t = static_cast<PlateauWidget *>(_o);
        switch (_id) {
        case 0: _t->counterIncr(); break;
        case 1: _t->counterDecr(); break;
        case 2: _t->counterReset(); break;
        case 3: _t->resetRobot((*reinterpret_cast< color(*)>(_a[1]))); break;
        case 4: _t->undoMove((*reinterpret_cast< color(*)>(_a[1])),(*reinterpret_cast< coord(*)>(_a[2]))); break;
        case 5: _t->sendMoves((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 6: _t->addWallRepr((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< direction(*)>(_a[3]))); break;
        case 7: _t->resetRepr(); break;
        case 8: _t->reset(); break;
        case 9: _t->undo(); break;
        case 10: _t->valider(); break;
        case 11: _t->addMove((*reinterpret_cast< s_move(*)>(_a[1]))); break;
        case 12: _t->setRobot((*reinterpret_cast< color(*)>(_a[1])),(*reinterpret_cast< coord(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlateauWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlateauWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PlateauWidget,
      qt_meta_data_PlateauWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlateauWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlateauWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlateauWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlateauWidget))
        return static_cast<void*>(const_cast< PlateauWidget*>(this));
    return QFrame::qt_metacast(_clname);
}

int PlateauWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void PlateauWidget::counterIncr()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PlateauWidget::counterDecr()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PlateauWidget::counterReset()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void PlateauWidget::resetRobot(color _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlateauWidget::undoMove(color _t1, coord _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PlateauWidget::sendMoves(std::string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
