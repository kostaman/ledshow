/****************************************************************************
** Meta object code from reading C++ file 'clockProperty.h'
**
** Created: Sat Oct 23 20:32:19 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QTPrj/clockProperty.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clockProperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CclockProperty[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CclockProperty[] = {
    "CclockProperty\0\0edited()\0propertyEdited()\0"
};

const QMetaObject CclockProperty::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CclockProperty,
      qt_meta_data_CclockProperty, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CclockProperty::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CclockProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CclockProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CclockProperty))
        return static_cast<void*>(const_cast< CclockProperty*>(this));
    return QWidget::qt_metacast(_clname);
}

int CclockProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: edited(); break;
        case 1: propertyEdited(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CclockProperty::edited()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
