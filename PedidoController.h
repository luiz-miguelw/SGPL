#ifndef PEDIDOCONTROLLER_H
#define PEDIDOCONTROLLER_H

#include <QObject>
#include <QList>
#include <QString>
#include "pedidoservice.h"
#include "itempedido.h"
#include "produto.h"

class PedidoController : public QObject
{
    Q_OBJECT

public:
    explicit PedidoController(PedidoService *service, QObject *parent = nullptr);

    Q_INVOKABLE void adicionarItem(QObject *produtoObj, int quantidade);
    Q_INVOKABLE void limparItens();
    Q_INVOKABLE int realizarPedido(const QString &endereco, const QString &pagamento, const QString &agendamento);
    Q_INVOKABLE QList<Pedido*> listarPedidos();

private:
    PedidoService *m_service;
    QList<ItemPedido*> m_itens;
};

#endif