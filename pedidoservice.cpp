#include "pedidoservice.h"

PedidoService::PedidoService(QObject *parent)
    : QObject(parent)
{
}

int PedidoService::realizarPedido(const QList<ItemPedido*> &itens, const QString &endereco)
{
    
    Pedido *pedido = new Pedido(this);

   
    for (ItemPedido *item : itens)
    {
        pedido->adicionarItem(item->getProduto(), item->quantidade());
    }

    m_pedidos.append(pedido);

    return proximoId++;
}

QList<Pedido*> PedidoService::listarPedidos() const
{
    return m_pedidos;
}