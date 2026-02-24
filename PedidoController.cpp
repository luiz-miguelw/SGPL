#include "PedidoController.h"

PedidoController::PedidoController(PedidoService *service, QObject *parent)
    : QObject(parent), m_service(service)
{
}

void PedidoController::adicionarItem(QObject *produtoObj, int quantidade)
{
    if (!produtoObj || quantidade <= 0)
        return;

    Produto *produto = qobject_cast<Produto*>(produtoObj);
    if (!produto)
        return;

    m_itens.append(new ItemPedido(produto, quantidade));
}

void PedidoController::limparItens()
{
    qDeleteAll(m_itens);
    m_itens.clear();
}

int PedidoController::realizarPedido(const QString &endereco, const QString &pagamento, const QString &agendamento)
{
    if (m_itens.isEmpty())
        return -1;

    int id = m_service->realizarPedido(m_itens, endereco, pagamento, agendamento);
    m_itens.clear();
    return id;
}

QList<Pedido*> PedidoController::listarPedidos()
{
    return m_service->listarPedidos();
}