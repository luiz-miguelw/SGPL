#ifndef PEDIDOSERVICE_H
#define PEDIDOSERVICE_H

#include <QObject>
#include <QList>
#include <QString>
#include "pedido.h"

class PedidoService : public QObject
{
    Q_OBJECT

public:
    explicit PedidoService(QObject *parent = nullptr);

    int realizarPedido(const QList<ItemPedido*> &itens, const QString &endereco, const QString &pagamento, const QString &agendamento);

    QList<Pedido*> listarPedidos() const;

private:
    QList<Pedido*> m_pedidos;
    int proximoId = 1;
};

#endif