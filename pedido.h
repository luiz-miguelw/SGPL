#ifndef PEDIDO_H
#define PEDIDO_H

#include <QObject>
#include <QList>
#include "itempedido.h"

class Pedido : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double total READ total NOTIFY pedidoChanged)

public:
    explicit Pedido(QObject *parent = nullptr);

    void adicionarItem(Produto *produto, int quantidade);
    QList<ItemPedido*> itens() const;
    double total() const;

signals:
    void pedidoChanged();

private:
    QList<ItemPedido*> m_itens;
};

#endif