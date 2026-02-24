#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


#include "catalogocontroller.h"
#include "pedidoservice.h"
#include "PedidoController.h"

// Função auxiliar para configurar o Banco de Dados
void configurarBancoDeDados() {
    // 1. Configura e abre o banco (Slide Aula01b, pág 3) [cite: 9]
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sgpl_dados.db");

    if (!db.open()) {
        qCritical() << "Erro fatal: Não foi possível conectar ao banco de dados!"
                    << db.lastError().text();
        return;
    }
    qDebug() << "Banco de dados conectado com sucesso!";

    // Ativa chaves estrangeiras no SQLite (importante para integridade)
    QSqlQuery pragma("PRAGMA foreign_keys = ON;");

    QSqlQuery query;

    // 2. Tabela PRODUTO (Já existia)
    QString sqlProduto = "CREATE TABLE IF NOT EXISTS produto ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "nome TEXT NOT NULL, "
                         "preco REAL, "
                         "estoque INTEGER)";
    if (!query.exec(sqlProduto))
        qCritical() << "Erro tabela produto:" << query.lastError().text();

    // 3. Tabela PEDIDO [Novo]
    // Baseado na sua classe Pedido.cpp. Adicionamos ID como chave primária[cite: 451].
    QString sqlPedido = "CREATE TABLE IF NOT EXISTS pedido ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "endereco TEXT, "
                        "pagamento TEXT, "
                        "agendamento TEXT, "
                        "status TEXT, "
                        "data_criacao DATETIME DEFAULT CURRENT_TIMESTAMP)";
    if (!query.exec(sqlPedido))
        qCritical() << "Erro tabela pedido:" << query.lastError().text();

    // 4. Tabela ITEM_PEDIDO [Novo]
    // Esta tabela liga o Pedido ao Produto (Relacionamento N:N resolvido).
    // Usa Foreign Keys (chaves estrangeiras) para garantir que o pedido e o produto existam.
    QString sqlItem = "CREATE TABLE IF NOT EXISTS item_pedido ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "pedido_id INTEGER NOT NULL, "
                      "produto_id INTEGER NOT NULL, "
                      "quantidade INTEGER NOT NULL, "
                      "FOREIGN KEY(pedido_id) REFERENCES pedido(id), "
                      "FOREIGN KEY(produto_id) REFERENCES produto(id))";

    if (!query.exec(sqlItem)) {
        qCritical() << "Erro tabela item_pedido:" << query.lastError().text();
    } else {
        qDebug() << "Todas as tabelas foram verificadas/criadas com sucesso.";
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Define estilo básico para evitar erros visuais


    // Configura o banco ANTES de iniciar os controllers
    configurarBancoDeDados();

    QQmlApplicationEngine engine;

    CatalogoController catalogoController;
    PedidoService pedidoService;
    PedidoController pedidoController(&pedidoService);

    engine.rootContext()->setContextProperty("pedidoController", &pedidoController);
    engine.rootContext()->setContextProperty("catalogo", &catalogoController);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("SGPL", "Main");

    return app.exec();
}
