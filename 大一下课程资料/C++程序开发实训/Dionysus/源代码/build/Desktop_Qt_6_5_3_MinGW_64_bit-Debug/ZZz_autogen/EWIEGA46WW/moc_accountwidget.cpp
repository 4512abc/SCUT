/****************************************************************************
** Meta object code from reading C++ file 'accountwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../accountwidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'accountwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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
struct qt_meta_stringdata_CLASSaccountWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSaccountWidgetENDCLASS = QtMocHelpers::stringData(
    "accountWidget",
    "returnToMainPage",
    "",
    "StartPlayWithAccount",
    "StartPlay",
    "registerBtnClicked",
    "onGuestModeContinueClicked",
    "onGuestModeConfirmed"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSaccountWidgetENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[14];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[10];
    char stringdata5[19];
    char stringdata6[27];
    char stringdata7[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSaccountWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSaccountWidgetENDCLASS_t qt_meta_stringdata_CLASSaccountWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "accountWidget"
        QT_MOC_LITERAL(14, 16),  // "returnToMainPage"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 20),  // "StartPlayWithAccount"
        QT_MOC_LITERAL(53, 9),  // "StartPlay"
        QT_MOC_LITERAL(63, 18),  // "registerBtnClicked"
        QT_MOC_LITERAL(82, 26),  // "onGuestModeContinueClicked"
        QT_MOC_LITERAL(109, 20)   // "onGuestModeConfirmed"
    },
    "accountWidget",
    "returnToMainPage",
    "",
    "StartPlayWithAccount",
    "StartPlay",
    "registerBtnClicked",
    "onGuestModeContinueClicked",
    "onGuestModeConfirmed"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSaccountWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    0,   51,    2, 0x06,    2 /* Public */,
       4,    0,   52,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   53,    2, 0x0a,    4 /* Public */,
       6,    0,   54,    2, 0x0a,    5 /* Public */,
       7,    0,   55,    2, 0x0a,    6 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject accountWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSaccountWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSaccountWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSaccountWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<accountWidget, std::true_type>,
        // method 'returnToMainPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'StartPlayWithAccount'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'StartPlay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'registerBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onGuestModeContinueClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onGuestModeConfirmed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void accountWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<accountWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->returnToMainPage(); break;
        case 1: _t->StartPlayWithAccount(); break;
        case 2: _t->StartPlay(); break;
        case 3: _t->registerBtnClicked(); break;
        case 4: _t->onGuestModeContinueClicked(); break;
        case 5: _t->onGuestModeConfirmed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (accountWidget::*)();
            if (_t _q_method = &accountWidget::returnToMainPage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (accountWidget::*)();
            if (_t _q_method = &accountWidget::StartPlayWithAccount; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (accountWidget::*)();
            if (_t _q_method = &accountWidget::StartPlay; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *accountWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *accountWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSaccountWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int accountWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void accountWidget::returnToMainPage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void accountWidget::StartPlayWithAccount()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void accountWidget::StartPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFindPasswordWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSFindPasswordWidgetENDCLASS = QtMocHelpers::stringData(
    "FindPasswordWidget",
    "continueBtnClicked",
    "",
    "toProtectQuesetion",
    "verifyQuestion",
    "protectQuestionInput"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFindPasswordWidgetENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[19];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[15];
    char stringdata5[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFindPasswordWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFindPasswordWidgetENDCLASS_t qt_meta_stringdata_CLASSFindPasswordWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "FindPasswordWidget"
        QT_MOC_LITERAL(19, 18),  // "continueBtnClicked"
        QT_MOC_LITERAL(38, 0),  // ""
        QT_MOC_LITERAL(39, 18),  // "toProtectQuesetion"
        QT_MOC_LITERAL(58, 14),  // "verifyQuestion"
        QT_MOC_LITERAL(73, 20)   // "protectQuestionInput"
    },
    "FindPasswordWidget",
    "continueBtnClicked",
    "",
    "toProtectQuesetion",
    "verifyQuestion",
    "protectQuestionInput"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFindPasswordWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x0a,    1 /* Public */,
       3,    0,   33,    2, 0x0a,    2 /* Public */,
       4,    1,   34,    2, 0x0a,    3 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

Q_CONSTINIT const QMetaObject FindPasswordWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSFindPasswordWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFindPasswordWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFindPasswordWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FindPasswordWidget, std::true_type>,
        // method 'continueBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toProtectQuesetion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'verifyQuestion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void FindPasswordWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FindPasswordWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->continueBtnClicked(); break;
        case 1: _t->toProtectQuesetion(); break;
        case 2: _t->verifyQuestion((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *FindPasswordWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FindPasswordWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFindPasswordWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FindPasswordWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSRegisterWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSRegisterWidgetENDCLASS = QtMocHelpers::stringData(
    "RegisterWidget",
    "registerAccount",
    ""
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSRegisterWidgetENDCLASS_t {
    uint offsetsAndSizes[6];
    char stringdata0[15];
    char stringdata1[16];
    char stringdata2[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSRegisterWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSRegisterWidgetENDCLASS_t qt_meta_stringdata_CLASSRegisterWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "RegisterWidget"
        QT_MOC_LITERAL(15, 15),  // "registerAccount"
        QT_MOC_LITERAL(31, 0)   // ""
    },
    "RegisterWidget",
    "registerAccount",
    ""
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSRegisterWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x0a,    1 /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject RegisterWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSRegisterWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSRegisterWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSRegisterWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<RegisterWidget, std::true_type>,
        // method 'registerAccount'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void RegisterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RegisterWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->registerAccount(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *RegisterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RegisterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSRegisterWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RegisterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
