#include "itempedido.h"

ItemPedido::ItemPedido(Produto *produto, int quantidade, QObject *parent)
    : QObject(parent), m_produto(produto), m_quantidade(quantidade)
{
}

QString ItemPedido::nomeProduto() const
{
    return m_produto->nome();
}

int ItemPedido::quantidade() const
{
    return m_quantidade;
}

void ItemPedido::setQuantidade(int qtd)
{
    if (m_quantidade != qtd) {
        m_quantidade = qtd;
        emit itemChanged();
    }
}

double ItemPedido::subtotal() const
{
    return m_produto->preco() * m_quantidade;
}
Produto* ItemPedido::getProduto() const
{
    return m_produto;
}