#ifndef PEDIDO_H
#define PEDIDO_H

#include <QObject>
#include <QList>
#include <QString>
#include "itempedido.h"

class Pedido : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double total READ total NOTIFY pedidoChanged)
    Q_PROPERTY(QString endereco READ endereco NOTIFY pedidoChanged)
    Q_PROPERTY(QString pagamento READ pagamento NOTIFY pedidoChanged)
    Q_PROPERTY(QString agendamento READ agendamento NOTIFY pedidoChanged)
    Q_PROPERTY(QString status READ status NOTIFY pedidoChanged)

public:
    explicit Pedido(QObject *parent = nullptr);

    Q_INVOKABLE void adicionarItem(Produto *produto, int quantidade);
    Q_INVOKABLE QList<ItemPedido*> itens() const;
    Q_INVOKABLE double total() const;

    QString endereco() const;
    void setEndereco(const QString &end);

    QString pagamento() const;
    void setPagamento(const QString &pag);

    QString agendamento() const;
    void setAgendamento(const QString &agd);

    QString status() const;
    void setStatus(const QString &st);

signals:
    void pedidoChanged();

private:
    QList<ItemPedido*> m_itens;
    QString m_endereco;
    QString m_pagamento;
    QString m_agendamento;
    QString m_status;
};

#endif