#ifndef ITEMPEDIDO_H
#define ITEMPEDIDO_H

#include <QObject>
#include <QString>
#include "produto.h"

class ItemPedido : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString nomeProduto READ nomeProduto NOTIFY itemChanged)
    Q_PROPERTY(int quantidade READ quantidade WRITE setQuantidade NOTIFY itemChanged)
    Q_PROPERTY(double subtotal READ subtotal NOTIFY itemChanged)

public:
    explicit ItemPedido(Produto *produto, int quantidade, QObject *parent = nullptr);

    QString nomeProduto() const;
    int quantidade() const;
    void setQuantidade(int qtd);

    double subtotal() const;
    Produto* getProduto() const;

signals:
    void itemChanged();

private:
    Produto *m_produto;
    int m_quantidade;
};

#endif