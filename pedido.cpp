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

QString Pedido::endereco() const { return m_endereco; }
void Pedido::setEndereco(const QString &end) { 
    if (m_endereco != end) { m_endereco = end; emit pedidoChanged(); } 
}

QString Pedido::pagamento() const { return m_pagamento; }
void Pedido::setPagamento(const QString &pag) { 
    if (m_pagamento != pag) { m_pagamento = pag; emit pedidoChanged(); } 
}

QString Pedido::agendamento() const { return m_agendamento; }
void Pedido::setAgendamento(const QString &agd) { 
    if (m_agendamento != agd) { m_agendamento = agd; emit pedidoChanged(); } 
}

QString Pedido::status() const { return m_status; }
void Pedido::setStatus(const QString &st) { 
    if (m_status != st) { m_status = st; emit pedidoChanged(); } 
}