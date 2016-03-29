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
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_GUI[] = {
    "GUI\0"
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
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
    return _id;
}
static const uint qt_meta_data_PlateauWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,
      40,   35,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   14,   14,   14, 0x0a,
      70,   14,   14,   14, 0x0a,
      77,   14,   14,   14, 0x0a,
      89,   87,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PlateauWidget[] = {
    "PlateauWidget\0\0c\0resetRobot(color)\0"
    "c,xy\0undoMove(color,coord)\0reset()\0"
    "undo()\0valider()\0m\0addMove(s_move)\0"
};

void PlateauWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlateauWidget *_t = static_cast<PlateauWidget *>(_o);
        switch (_id) {
        case 0: _t->resetRobot((*reinterpret_cast< color(*)>(_a[1]))); break;
        case 1: _t->undoMove((*reinterpret_cast< color(*)>(_a[1])),(*reinterpret_cast< coord(*)>(_a[2]))); break;
        case 2: _t->reset(); break;
        case 3: _t->undo(); break;
        case 4: _t->valider(); break;
        case 5: _t->addMove((*reinterpret_cast< s_move(*)>(_a[1]))); break;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PlateauWidget::resetRobot(color _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlateauWidget::undoMove(color _t1, coord _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_Robot[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    7,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   28,    6,    6, 0x0a,
      58,   56,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Robot[] = {
    "Robot\0\0m\0robotMoved(s_move)\0c,xy\0"
    "moveRobot(color,coord)\0c\0reset(color)\0"
};

void Robot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Robot *_t = static_cast<Robot *>(_o);
        switch (_id) {
        case 0: _t->robotMoved((*reinterpret_cast< s_move(*)>(_a[1]))); break;
        case 1: _t->moveRobot((*reinterpret_cast< color(*)>(_a[1])),(*reinterpret_cast< coord(*)>(_a[2]))); break;
        case 2: _t->reset((*reinterpret_cast< color(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Robot::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Robot::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Robot,
      qt_meta_data_Robot, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Robot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Robot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Robot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Robot))
        return static_cast<void*>(const_cast< Robot*>(this));
    return QWidget::qt_metacast(_clname);
}

int Robot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Robot::robotMoved(s_move _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
