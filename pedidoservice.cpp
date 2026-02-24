#include "pedidoservice.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include "produto.h" // Necessário para criar os objetos Produto

PedidoService::PedidoService(QObject *parent)
    : QObject(parent)
{
}

int PedidoService::realizarPedido(const QList<ItemPedido*> &itens, const QString &endereco, const QString &pagamento, const QString &agendamento)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        qCritical() << "Erro ao iniciar transação:" << db.lastError().text();
        return -1;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO pedido (endereco, pagamento, agendamento, status) "
                  "VALUES (:end, :pag, :agd, :status)");
    query.bindValue(":end", endereco);
    query.bindValue(":pag", pagamento);
    query.bindValue(":agd", agendamento);
    query.bindValue(":status", "Realizado");

    if (!query.exec()) {
        qCritical() << "Erro ao inserir pedido:" << query.lastError().text();
        db.rollback();
        return -1;
    }

    int pedidoId = query.lastInsertId().toInt();

    for (ItemPedido *item : itens)
    {
        Produto* p = item->getProduto();

        QSqlQuery queryItem;
        queryItem.prepare("INSERT INTO item_pedido (pedido_id, produto_id, quantidade) "
                          "VALUES (:pedId, :prodId, :qtd)");
        queryItem.bindValue(":pedId", pedidoId);
        queryItem.bindValue(":prodId", p->id());
        queryItem.bindValue(":qtd", item->quantidade());

        if (!queryItem.exec()) {
            qCritical() << "Erro ao inserir item:" << queryItem.lastError().text();
            db.rollback();
            return -1;
        }

        QSqlQuery queryEstoque;
        queryEstoque.prepare("UPDATE produto SET estoque = estoque - :qtd WHERE id = :prodId");
        queryEstoque.bindValue(":qtd", item->quantidade());
        queryEstoque.bindValue(":prodId", p->id());

        if (!queryEstoque.exec()) {
            qCritical() << "Erro ao atualizar estoque:" << queryEstoque.lastError().text();
            db.rollback();
            return -1;
        }
    }

    if (db.commit()) {
        qDebug() << "Pedido" << pedidoId << "realizado com sucesso!";
        return pedidoId;
    } else {
        db.rollback();
        return -1;
    }
}

QList<Pedido*> PedidoService::listarPedidos()
{
    qDeleteAll(m_pedidos);
    m_pedidos.clear();

    // 1. Busca todos os pedidos
    QSqlQuery query("SELECT id, endereco, pagamento, agendamento, status FROM pedido ORDER BY id DESC");

    while (query.next()) {
        Pedido *pedido = new Pedido(this);
        int idPedido = query.value("id").toInt();

        pedido->setId(idPedido);
        pedido->setEndereco(query.value("endereco").toString());
        pedido->setPagamento(query.value("pagamento").toString());
        pedido->setAgendamento(query.value("agendamento").toString());
        pedido->setStatus(query.value("status").toString());

        // 2. AGORA O PULO DO GATO:
        // Para cada pedido, buscamos os itens associados no banco
        // Fazemos um JOIN para pegar também o preço do produto na tabela 'produto'
        QSqlQuery queryItens;
        queryItens.prepare("SELECT i.quantidade, p.nome, p.preco "
                           "FROM item_pedido i "
                           "INNER JOIN produto p ON i.produto_id = p.id "
                           "WHERE i.pedido_id = :pid");
        queryItens.bindValue(":pid", idPedido);

        if (queryItens.exec()) {
            while (queryItens.next()) {
                int qtd = queryItens.value("quantidade").toInt();
                double preco = queryItens.value("preco").toDouble();
                QString nome = queryItens.value("nome").toString();

                // Criamos um produto temporário apenas para calcular o total na memória
                Produto *prodTemp = new Produto(nome, preco, 0, pedido);

                // Adicionamos ao pedido (isso faz o cálculo do total funcionar automaticamente)
                pedido->adicionarItem(prodTemp, qtd);
            }
        }

        m_pedidos.append(pedido);
    }

    return m_pedidos;
}
