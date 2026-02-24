#include "pedidoservice.h"

PedidoService::PedidoService(QObject *parent)
    : QObject(parent)
{
}

int PedidoService::realizarPedido(const QList<ItemPedido*> &itens, const QString &endereco, const QString &pagamento, const QString &agendamento)
{
    Pedido *pedido = new Pedido(this);

    for (ItemPedido *item : itens)
    {
        pedido->adicionarItem(item->getProduto(), item->quantidade());
        
        Produto* p = item->getProduto();
        if (p->estoque() > 0) {
            p->setEstoque(p->estoque() - item->quantidade());
        }
    }

    pedido->setEndereco(endereco);
    pedido->setPagamento(pagamento);
    pedido->setAgendamento(agendamento);
    pedido->setStatus("Pedido Realizado");

    m_pedidos.append(pedido);

    return proximoId++;
}

QList<Pedido*> PedidoService::listarPedidos() const
{
    return m_pedidos;
}