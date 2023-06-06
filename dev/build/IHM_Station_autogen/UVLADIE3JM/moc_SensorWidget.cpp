/****************************************************************************
** Meta object code from reading C++ file 'SensorWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/SensorWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SensorWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SensorWidget_t {
    const uint offsetsAndSize[18];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_SensorWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_SensorWidget_t qt_meta_stringdata_SensorWidget = {
    {
QT_MOC_LITERAL(0, 12), // "SensorWidget"
QT_MOC_LITERAL(13, 7), // "nextSig"
QT_MOC_LITERAL(21, 0), // ""
QT_MOC_LITERAL(22, 11), // "previousSig"
QT_MOC_LITERAL(34, 10), // "acquireSig"
QT_MOC_LITERAL(45, 7), // "acquire"
QT_MOC_LITERAL(53, 4), // "next"
QT_MOC_LITERAL(58, 8), // "previous"
QT_MOC_LITERAL(67, 12) // "startAcquire"

    },
    "SensorWidget\0nextSig\0\0previousSig\0"
    "acquireSig\0acquire\0next\0previous\0"
    "startAcquire"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SensorWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    1 /* Public */,
       3,    0,   57,    2, 0x06,    2 /* Public */,
       4,    0,   58,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   59,    2, 0x0a,    4 /* Public */,
       6,    0,   60,    2, 0x0a,    5 /* Public */,
       7,    0,   61,    2, 0x0a,    6 /* Public */,
       8,    0,   62,    2, 0x0a,    7 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SensorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SensorWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->nextSig(); break;
        case 1: _t->previousSig(); break;
        case 2: _t->acquireSig(); break;
        case 3: _t->acquire(); break;
        case 4: _t->next(); break;
        case 5: _t->previous(); break;
        case 6: _t->startAcquire(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SensorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorWidget::nextSig)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SensorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorWidget::previousSig)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SensorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorWidget::acquireSig)) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject SensorWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SensorWidget.offsetsAndSize,
    qt_meta_data_SensorWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_SensorWidget_t
, QtPrivate::TypeAndForceComplete<SensorWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *SensorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SensorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SensorWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SensorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void SensorWidget::nextSig()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SensorWidget::previousSig()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SensorWidget::acquireSig()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
