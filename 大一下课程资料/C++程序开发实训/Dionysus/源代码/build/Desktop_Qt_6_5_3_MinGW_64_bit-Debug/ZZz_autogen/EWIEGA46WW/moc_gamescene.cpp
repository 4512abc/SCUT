/****************************************************************************
** Meta object code from reading C++ file 'gamescene.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../gamescene.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamescene.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSVictoryWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSVictoryWidgetENDCLASS = QtMocHelpers::stringData(
    "VictoryWidget",
    "restart",
    "",
    "toRank",
    "selectOtherMode"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVictoryWidgetENDCLASS_t {
    uint offsetsAndSizes[10];
    char stringdata0[14];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVictoryWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVictoryWidgetENDCLASS_t qt_meta_stringdata_CLASSVictoryWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "VictoryWidget"
        QT_MOC_LITERAL(14, 7),  // "restart"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 6),  // "toRank"
        QT_MOC_LITERAL(30, 15)   // "selectOtherMode"
    },
    "VictoryWidget",
    "restart",
    "",
    "toRank",
    "selectOtherMode"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVictoryWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x06,    1 /* Public */,
       3,    0,   33,    2, 0x06,    2 /* Public */,
       4,    0,   34,    2, 0x06,    3 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject VictoryWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSVictoryWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSVictoryWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSVictoryWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VictoryWidget, std::true_type>,
        // method 'restart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toRank'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectOtherMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void VictoryWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VictoryWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->restart(); break;
        case 1: _t->toRank(); break;
        case 2: _t->selectOtherMode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VictoryWidget::*)();
            if (_t _q_method = &VictoryWidget::restart; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VictoryWidget::*)();
            if (_t _q_method = &VictoryWidget::toRank; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VictoryWidget::*)();
            if (_t _q_method = &VictoryWidget::selectOtherMode; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *VictoryWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VictoryWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSVictoryWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VictoryWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void VictoryWidget::restart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VictoryWidget::toRank()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void VictoryWidget::selectOtherMode()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSrankWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSrankWidgetENDCLASS = QtMocHelpers::stringData(
    "rankWidget",
    "returnToGameScene",
    "",
    "sortRank",
    "mode"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSrankWidgetENDCLASS_t {
    uint offsetsAndSizes[10];
    char stringdata0[11];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSrankWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSrankWidgetENDCLASS_t qt_meta_stringdata_CLASSrankWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "rankWidget"
        QT_MOC_LITERAL(11, 17),  // "returnToGameScene"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 8),  // "sortRank"
        QT_MOC_LITERAL(39, 4)   // "mode"
    },
    "rankWidget",
    "returnToGameScene",
    "",
    "sortRank",
    "mode"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSrankWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   27,    2, 0x0a,    2 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject rankWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSrankWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSrankWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSrankWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<rankWidget, std::true_type>,
        // method 'returnToGameScene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sortRank'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void rankWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<rankWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->returnToGameScene(); break;
        case 1: _t->sortRank((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (rankWidget::*)();
            if (_t _q_method = &rankWidget::returnToGameScene; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *rankWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rankWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSrankWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int rankWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void rankWidget::returnToGameScene()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSplayWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSplayWidgetENDCLASS = QtMocHelpers::stringData(
    "playWidget",
    "returnToGameScene",
    "",
    "recustom",
    "selectOtherMode",
    "toRank",
    "updateTime",
    "withdraw",
    "updateTargetSlice",
    "sliceKind",
    "posInArray",
    "pos_x",
    "pos_y",
    "delta",
    "updateSliceToPut",
    "change",
    "updateTargetSliceLabel",
    "startWithOthersMap",
    "startByCustomInput",
    "showCustom"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSplayWidgetENDCLASS_t {
    uint offsetsAndSizes[40];
    char stringdata0[11];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[16];
    char stringdata5[7];
    char stringdata6[11];
    char stringdata7[9];
    char stringdata8[18];
    char stringdata9[10];
    char stringdata10[11];
    char stringdata11[6];
    char stringdata12[6];
    char stringdata13[6];
    char stringdata14[17];
    char stringdata15[7];
    char stringdata16[23];
    char stringdata17[19];
    char stringdata18[19];
    char stringdata19[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSplayWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSplayWidgetENDCLASS_t qt_meta_stringdata_CLASSplayWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "playWidget"
        QT_MOC_LITERAL(11, 17),  // "returnToGameScene"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 8),  // "recustom"
        QT_MOC_LITERAL(39, 15),  // "selectOtherMode"
        QT_MOC_LITERAL(55, 6),  // "toRank"
        QT_MOC_LITERAL(62, 10),  // "updateTime"
        QT_MOC_LITERAL(73, 8),  // "withdraw"
        QT_MOC_LITERAL(82, 17),  // "updateTargetSlice"
        QT_MOC_LITERAL(100, 9),  // "sliceKind"
        QT_MOC_LITERAL(110, 10),  // "posInArray"
        QT_MOC_LITERAL(121, 5),  // "pos_x"
        QT_MOC_LITERAL(127, 5),  // "pos_y"
        QT_MOC_LITERAL(133, 5),  // "delta"
        QT_MOC_LITERAL(139, 16),  // "updateSliceToPut"
        QT_MOC_LITERAL(156, 6),  // "change"
        QT_MOC_LITERAL(163, 22),  // "updateTargetSliceLabel"
        QT_MOC_LITERAL(186, 18),  // "startWithOthersMap"
        QT_MOC_LITERAL(205, 18),  // "startByCustomInput"
        QT_MOC_LITERAL(224, 10)   // "showCustom"
    },
    "playWidget",
    "returnToGameScene",
    "",
    "recustom",
    "selectOtherMode",
    "toRank",
    "updateTime",
    "withdraw",
    "updateTargetSlice",
    "sliceKind",
    "posInArray",
    "pos_x",
    "pos_y",
    "delta",
    "updateSliceToPut",
    "change",
    "updateTargetSliceLabel",
    "startWithOthersMap",
    "startByCustomInput",
    "showCustom"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSplayWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,    1 /* Public */,
       3,    0,   87,    2, 0x06,    2 /* Public */,
       4,    0,   88,    2, 0x06,    3 /* Public */,
       5,    0,   89,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   90,    2, 0x0a,    5 /* Public */,
       7,    0,   91,    2, 0x0a,    6 /* Public */,
       8,    5,   92,    2, 0x0a,    7 /* Public */,
      14,    2,  103,    2, 0x0a,   13 /* Public */,
      16,    0,  108,    2, 0x0a,   16 /* Public */,
      17,    0,  109,    2, 0x0a,   17 /* Public */,
      18,    0,  110,    2, 0x0a,   18 /* Public */,
      19,    0,  111,    2, 0x0a,   19 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject playWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSplayWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSplayWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSplayWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<playWidget, std::true_type>,
        // method 'returnToGameScene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recustom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectOtherMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toRank'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTime'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'withdraw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTargetSlice'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateSliceToPut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateTargetSliceLabel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startWithOthersMap'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startByCustomInput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showCustom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void playWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<playWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->returnToGameScene(); break;
        case 1: _t->recustom(); break;
        case 2: _t->selectOtherMode(); break;
        case 3: _t->toRank(); break;
        case 4: _t->updateTime(); break;
        case 5: _t->withdraw(); break;
        case 6: _t->updateTargetSlice((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 7: _t->updateSliceToPut((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 8: _t->updateTargetSliceLabel(); break;
        case 9: _t->startWithOthersMap(); break;
        case 10: _t->startByCustomInput(); break;
        case 11: _t->showCustom(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (playWidget::*)();
            if (_t _q_method = &playWidget::returnToGameScene; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (playWidget::*)();
            if (_t _q_method = &playWidget::recustom; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (playWidget::*)();
            if (_t _q_method = &playWidget::selectOtherMode; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (playWidget::*)();
            if (_t _q_method = &playWidget::toRank; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *playWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *playWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSplayWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int playWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void playWidget::returnToGameScene()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void playWidget::recustom()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void playWidget::selectOtherMode()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void playWidget::toRank()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSgameWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSgameWidgetENDCLASS = QtMocHelpers::stringData(
    "gameWidget",
    "returnToMainPage",
    "",
    "ToPractice",
    "ToCompetition",
    "ToRankWidget",
    "loginOutSignal",
    "ToEndless",
    "ToCustom"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSgameWidgetENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[11];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[14];
    char stringdata5[13];
    char stringdata6[15];
    char stringdata7[10];
    char stringdata8[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSgameWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSgameWidgetENDCLASS_t qt_meta_stringdata_CLASSgameWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "gameWidget"
        QT_MOC_LITERAL(11, 16),  // "returnToMainPage"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 10),  // "ToPractice"
        QT_MOC_LITERAL(40, 13),  // "ToCompetition"
        QT_MOC_LITERAL(54, 12),  // "ToRankWidget"
        QT_MOC_LITERAL(67, 14),  // "loginOutSignal"
        QT_MOC_LITERAL(82, 9),  // "ToEndless"
        QT_MOC_LITERAL(92, 8)   // "ToCustom"
    },
    "gameWidget",
    "returnToMainPage",
    "",
    "ToPractice",
    "ToCompetition",
    "ToRankWidget",
    "loginOutSignal",
    "ToEndless",
    "ToCustom"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSgameWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    1 /* Public */,
       3,    0,   57,    2, 0x06,    2 /* Public */,
       4,    0,   58,    2, 0x06,    3 /* Public */,
       5,    0,   59,    2, 0x06,    4 /* Public */,
       6,    0,   60,    2, 0x06,    5 /* Public */,
       7,    0,   61,    2, 0x06,    6 /* Public */,
       8,    0,   62,    2, 0x06,    7 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject gameWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSgameWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSgameWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSgameWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<gameWidget, std::true_type>,
        // method 'returnToMainPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ToPractice'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ToCompetition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ToRankWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loginOutSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ToEndless'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ToCustom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void gameWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gameWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->returnToMainPage(); break;
        case 1: _t->ToPractice(); break;
        case 2: _t->ToCompetition(); break;
        case 3: _t->ToRankWidget(); break;
        case 4: _t->loginOutSignal(); break;
        case 5: _t->ToEndless(); break;
        case 6: _t->ToCustom(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (gameWidget::*)();
            if (_t _q_method = &gameWidget::returnToMainPage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (gameWidget::*)();
            if (_t _q_method = &gameWidget::ToPractice; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (gameWidget::*)();
            if (_t _q_method = &gameWidget::ToCompetition; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (gameWidget::*)();
            if (_t _q_method = &gameWidget::ToRankWidget; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (gameWidget::*)();
            if (_t _q_method = &gameWidget::loginOutSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (gameWidget::*)();
            if (_t _q_method = &gameWidget::ToEndless; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (gameWidget::*)();
            if (_t _q_method = &gameWidget::ToCustom; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *gameWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gameWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSgameWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int gameWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void gameWidget::returnToMainPage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void gameWidget::ToPractice()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void gameWidget::ToCompetition()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void gameWidget::ToRankWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void gameWidget::loginOutSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void gameWidget::ToEndless()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void gameWidget::ToCustom()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
