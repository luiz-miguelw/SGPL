#include "pedidoservice.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

PedidoService::PedidoService(QObject *parent)
    : QObject(parent)
{
}

int PedidoService::realizarPedido(const QList<ItemPedido*> &itens, const QString &endereco, const QString &pagamento, const QString &agendamento)
{
    QSqlDatabase db = QSqlDatabase::database();

    // 1. Inicia Transação (Segurança: ou salva tudo, ou não salva nada)
    if (!db.transaction()) {
        qCritical() << "Erro ao iniciar transação:" << db.lastError().text();
        return -1;
    }

    // 2. Insere o Cabeçalho do Pedido na tabela 'pedido'
    QSqlQuery query;
    query.prepare("INSERT INTO pedido (endereco, pagamento, agendamento, status) "
                  "VALUES (:end, :pag, :agd, :status)");
    query.bindValue(":end", endereco);
    query.bindValue(":pag", pagamento);
    query.bindValue(":agd", agendamento);
    query.bindValue(":status", "Realizado");

    if (!query.exec()) {
        qCritical() << "Erro ao inserir pedido:" << query.lastError().text();
        db.rollback(); // Cancela tudo
        return -1;
    }

    // Pega o ID gerado automaticamente pelo banco (Ex: Pedido nº 1, nº 2...)
    int pedidoId = query.lastInsertId().toInt();

    // 3. Processa cada item do pedido
    for (ItemPedido *item : itens)
    {
        Produto* p = item->getProduto();

        // A) Insere na tabela de relacionamento 'item_pedido'
        QSqlQuery queryItem;
        queryItem.prepare("INSERT INTO item_pedido (pedido_id, produto_id, quantidade) "
                          "VALUES (:pedId, :prodId, :qtd)");
        queryItem.bindValue(":pedId", pedidoId);
        queryItem.bindValue(":prodId", p->id()); // Assume que Produto tem id()
        queryItem.bindValue(":qtd", item->quantidade());

        if (!queryItem.exec()) {
            qCritical() << "Erro ao inserir item:" << queryItem.lastError().text();
            db.rollback();
            return -1;
        }

        // B) Atualiza o estoque na tabela 'produto'
        // SQL: UPDATE produto SET estoque = estoque - X WHERE id = Y
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

    // 4. Se chegou aqui, deu tudo certo. Confirma a gravação permanente.
    if (db.commit()) {
        qDebug() << "Pedido" << pedidoId << "realizado com sucesso!";
        // Opcional: Recarregar a lista local se você mantiver m_pedidos
        return pedidoId;
    } else {
        qCritical() << "Erro no commit:" << db.lastError().text();
        db.rollback();
        return -1;
    }
}

QList<Pedido*> PedidoService::listarPedidos()
{
    // Limpa a lista da memória para recarregar do banco (evita duplicatas)
    qDeleteAll(m_pedidos);
    m_pedidos.clear();

    QSqlQuery query("SELECT id, endereco, pagamento, agendamento, status FROM pedido ORDER BY id DESC");

    while (query.next()) {
        Pedido *p = new Pedido(this);
        p->setId(query.value("id").toInt());
        p->setEndereco(query.value("endereco").toString());
        p->setPagamento(query.value("pagamento").toString());
        p->setAgendamento(query.value("agendamento").toString());
        p->setStatus(query.value("status").toString());

        // Nota: Por enquanto estamos carregando só o cabeçalho.
        // Se quiser exibir os itens na lista de histórico, precisaria fazer outra query aqui.

        m_pedidos.append(p);
    }

    return m_pedidos;
}
