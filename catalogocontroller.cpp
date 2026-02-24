#include "catalogocontroller.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord> // Para usar query.record() se necessário

CatalogoController::CatalogoController(QObject *parent)
    : QObject(parent)
{
    // Primeiro, carregamos o que já existe no banco de dados para a memória
    carregarProdutosDoBanco();

    // DADOS DE TESTE INICIAIS
    // Verifica se a lista está vazia. Se estiver, insere os produtos padrão no Banco.
    if (m_produtos.isEmpty()) {
        qDebug() << "Banco vazio. Inserindo dados de teste...";
        adicionarProduto("Pão de Alho Tradicional", 15.00, 10);
        adicionarProduto("Pão de Alho Picante", 16.50, 0); // Estoque 0 -> "Sob Encomenda"
    }
}

QList<QObject*> CatalogoController::produtos() const
{
    return m_produtos;
}

void CatalogoController::adicionarProduto(const QString &nome, double preco, int estoque)
{
    // CONFIGURAÇÃO DA QUERY (Baseado no Slide 11 - Named Binding)
    // Usamos :nome, :preco, :estoque como "placeholders" [cite: 93-94]
    QSqlQuery query;
    query.prepare("INSERT INTO produto (nome, preco, estoque) VALUES (:nome, :preco, :estoque)");

    // VINCULAÇÃO DOS VALORES (Baseado no Slide 11 - bindValue) [cite: 95-97]
    query.bindValue(":nome", nome);
    query.bindValue(":preco", preco);
    query.bindValue(":estoque", estoque);

    // Executa o comando no banco de dados [cite: 98]
    if (!query.exec()) {
        qCritical() << "Erro ao adicionar produto no BD:" << query.lastError().text();
        return;
    }

    qDebug() << "Produto salvo no banco com sucesso!";

    // Após salvar no banco, recarregamos a lista da memória para atualizar a tela
    carregarProdutosDoBanco();
}
void CatalogoController::carregarProdutosDoBanco()
{
    qDeleteAll(m_produtos);
    m_produtos.clear();

    // ALTERAÇÃO 1: Adicionei "id" no SELECT para buscar o número dele
    QSqlQuery query("SELECT id, nome, preco, estoque FROM produto");

    while (query.next()) {
        // ALTERAÇÃO 2: Lemos o ID do banco
        int id = query.value("id").toInt();
        QString nome = query.value("nome").toString();
        double preco = query.value("preco").toDouble();
        int estoque = query.value("estoque").toInt();

        Produto *p = new Produto(nome, preco, estoque, this);

        // ALTERAÇÃO 3: IMPORTANTE! Salvamos o ID dentro do objeto
        p->setId(id);

        m_produtos.append(p);
    }

    emit produtosChanged();
}
