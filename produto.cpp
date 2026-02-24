#include "produto.h"

Produto::Produto(QObject *parent) : QObject(parent)
{
    m_id = -1;
    m_preco = 0.0;
    m_estoque = 0;
}

Produto::Produto(const QString &nome, double preco, int estoque, QObject *parent)
    : QObject(parent), m_nome(nome), m_preco(preco), m_estoque(estoque)
{
    m_id = -1;
}

int Produto::id() const { return m_id; }
void Produto::setId(int newId)
{
    if (m_id != newId) {
        m_id = newId;
        emit idChanged();
    }
}

QString Produto::nome() const { return m_nome; }
void Produto::setNome(const QString &nome)
{
    if (m_nome != nome) {
        m_nome = nome;
        emit nomeChanged();
    }
}

double Produto::preco() const { return m_preco; }
void Produto::setPreco(double preco)
{
    if (m_preco != preco) {
        m_preco = preco;
        emit precoChanged();
    }
}

int Produto::estoque() const { return m_estoque; }
void Produto::setEstoque(int estoque)
{
    if (m_estoque != estoque) {
        m_estoque = estoque;
        emit estoqueChanged();
    }
}

bool Produto::sobEncomenda() const
{
    return m_estoque <= 0;
}
