/****************************************************************************
** Meta object code from reading C++ file 'filemanagerwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../filemanager/filemanagerwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filemanagerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_filemanagerWidget_t {
    QByteArrayData data[11];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_filemanagerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_filemanagerWidget_t qt_meta_stringdata_filemanagerWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "filemanagerWidget"
QT_MOC_LITERAL(1, 18, 7), // "chgDisk"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "index"
QT_MOC_LITERAL(4, 33, 10), // "goMainPath"
QT_MOC_LITERAL(5, 44, 7), // "chgPath"
QT_MOC_LITERAL(6, 52, 12), // "chgPathIndex"
QT_MOC_LITERAL(7, 65, 11), // "QModelIndex"
QT_MOC_LITERAL(8, 77, 15), // "updateListDisks"
QT_MOC_LITERAL(9, 93, 17), // "genStringPathFile"
QT_MOC_LITERAL(10, 111, 12) // "deleteThread"

    },
    "filemanagerWidget\0chgDisk\0\0index\0"
    "goMainPath\0chgPath\0chgPathIndex\0"
    "QModelIndex\0updateListDisks\0"
    "genStringPathFile\0deleteThread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_filemanagerWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       4,    0,   52,    2, 0x08 /* Private */,
       5,    0,   53,    2, 0x08 /* Private */,
       6,    1,   54,    2, 0x08 /* Private */,
       8,    0,   57,    2, 0x08 /* Private */,
       9,    1,   58,    2, 0x08 /* Private */,
      10,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

       0        // eod
};

void filemanagerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<filemanagerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->chgDisk((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->goMainPath(); break;
        case 2: _t->chgPath(); break;
        case 3: _t->chgPathIndex((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->updateListDisks(); break;
        case 5: _t->genStringPathFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->deleteThread(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject filemanagerWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_filemanagerWidget.data,
    qt_meta_data_filemanagerWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *filemanagerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *filemanagerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_filemanagerWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int filemanagerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
