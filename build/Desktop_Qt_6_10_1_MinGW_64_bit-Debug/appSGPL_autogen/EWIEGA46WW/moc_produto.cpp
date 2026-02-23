/****************************************************************************
** Meta object code from reading C++ file 'produto.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../produto.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'produto.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
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
struct qt_meta_tag_ZN7ProdutoE_t {};
} // unnamed namespace

template <> constexpr inline auto Produto::qt_create_metaobjectdata<qt_meta_tag_ZN7ProdutoE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Produto",
        "nomeChanged",
        "",
        "precoChanged",
        "estoqueChanged",
        "sobEncomendaChanged",
        "nome",
        "preco",
        "estoque",
        "sobEncomenda"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'nomeChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'precoChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'estoqueChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sobEncomendaChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'nome'
        QtMocHelpers::PropertyData<QString>(6, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'preco'
        QtMocHelpers::PropertyData<double>(7, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'estoque'
        QtMocHelpers::PropertyData<int>(8, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'sobEncomenda'
        QtMocHelpers::PropertyData<bool>(9, QMetaType::Bool, QMC::DefaultPropertyFlags, 3),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Produto, qt_meta_tag_ZN7ProdutoE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Produto::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7ProdutoE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7ProdutoE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7ProdutoE_t>.metaTypes,
    nullptr
} };

void Produto::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Produto *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->nomeChanged(); break;
        case 1: _t->precoChanged(); break;
        case 2: _t->estoqueChanged(); break;
        case 3: _t->sobEncomendaChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Produto::*)()>(_a, &Produto::nomeChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Produto::*)()>(_a, &Produto::precoChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Produto::*)()>(_a, &Produto::estoqueChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Produto::*)()>(_a, &Produto::sobEncomendaChanged, 3))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->nome(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->preco(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->estoque(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->sobEncomenda(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setNome(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setPreco(*reinterpret_cast<double*>(_v)); break;
        case 2: _t->setEstoque(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Produto::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Produto::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7ProdutoE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Produto::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Produto::nomeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Produto::precoChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Produto::estoqueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Produto::sobEncomendaChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
