/****************************************************************************
** Meta object code from reading C++ file 'automatform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI/automatform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'automatform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AutomatForm_t {
    QByteArrayData data[5];
    char stringdata[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AutomatForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AutomatForm_t qt_meta_stringdata_AutomatForm = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AutomatForm"
QT_MOC_LITERAL(1, 12, 9), // "goto_main"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "msn"
QT_MOC_LITERAL(4, 27, 13) // "draw_automata"

    },
    "AutomatForm\0goto_main\0\0msn\0draw_automata"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AutomatForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       4,    0,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

       0        // eod
};

void AutomatForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AutomatForm *_t = static_cast<AutomatForm *>(_o);
        switch (_id) {
        case 0: _t->goto_main((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->draw_automata(); break;
        default: ;
        }
    }
}

const QMetaObject AutomatForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AutomatForm.data,
      qt_meta_data_AutomatForm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AutomatForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AutomatForm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AutomatForm.stringdata))
        return static_cast<void*>(const_cast< AutomatForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int AutomatForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
