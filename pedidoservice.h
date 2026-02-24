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

    // Método para salvar no banco
    Q_INVOKABLE int realizarPedido(const QList<ItemPedido*> &itens, const QString &endereco, const QString &pagamento, const QString &agendamento);

    // Método para ler do banco (Sem 'const' no final!)
    Q_INVOKABLE QList<Pedido*> listarPedidos();

private:
    QList<Pedido*> m_pedidos;
};

#endif // PEDIDOSERVICE_H
