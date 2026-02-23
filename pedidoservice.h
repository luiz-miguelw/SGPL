#ifndef PEDIDOSERVICE_H
#define PEDIDOSERVICE_H

#include <QObject>
#include <QList>
#include "pedido.h"

class PedidoService : public QObject
{
    Q_OBJECT

public:
    explicit PedidoService(QObject *parent = nullptr);

    int realizarPedido(const QList<ItemPedido*> &itens, const QString &endereco);

    QList<Pedido*> listarPedidos() const;

private:
    QList<Pedido*> m_pedidos;
    int proximoId = 1;
};

#endif