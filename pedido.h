#ifndef PEDIDO_H
#define PEDIDO_H

#include <QObject>
#include <QList>
#include <QString>
#include "itempedido.h"
#include "produto.h"

class Pedido : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(double total READ total NOTIFY pedidoChanged)
    Q_PROPERTY(QString endereco READ endereco WRITE setEndereco NOTIFY pedidoChanged)
    Q_PROPERTY(QString pagamento READ pagamento WRITE setPagamento NOTIFY pedidoChanged)
    Q_PROPERTY(QString agendamento READ agendamento WRITE setAgendamento NOTIFY pedidoChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY pedidoChanged)

public:
    explicit Pedido(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    Q_INVOKABLE void adicionarItem(Produto *produto, int quantidade);
    Q_INVOKABLE QList<ItemPedido*> itens() const;

    // Total calculado dinamicamente (corrige o erro m_total)
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
    void idChanged();

private:
    int m_id = -1;
    QList<ItemPedido*> m_itens;
    QString m_endereco;
    QString m_pagamento;
    QString m_agendamento;
    QString m_status;
};

#endif // PEDIDO_H
