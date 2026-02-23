#include "pedido.h"

Pedido::Pedido(QObject *parent)
    : QObject(parent)
{
}

void Pedido::adicionarItem(Produto *produto, int quantidade)
{
    ItemPedido *item = new ItemPedido(produto, quantidade, this);
    m_itens.append(item);
    emit pedidoChanged();
}

QList<ItemPedido*> Pedido::itens() const
{
    return m_itens;
}

double Pedido::total() const
{
    double soma = 0;
    for (auto item : m_itens)
        soma += item->subtotal();

    return soma;
}