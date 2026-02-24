#include <QCoreApplication>
#include <QDebug>

#include "produto.h"
#include "itempedido.h"
#include "pedido.h"
#include "pedidoservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    qDebug() << "===== TESTE FUNCIONAL - PEDIDOS =====";

    // 1. Criar produtos (simulando catálogo)
    Produto *p1 = new Produto("Bolo de Chocolate", 50.0, 10);
    Produto *p2 = new Produto("Bolo de Morango", 60.0, 5);

    // 2. Criar itens do pedido
    QList<ItemPedido*> itensPedido1;
    itensPedido1.append(new ItemPedido(p1, 2)); // 2 chocolates
    itensPedido1.append(new ItemPedido(p2, 1)); // 1 morango

    // 3. Criar o serviço (sistema)
    PedidoService service;

    // 4. Realizar pedido
    int id1 = service.realizarPedido(itensPedido1, "Rua A, 123");

    qDebug() << "Pedido realizado com ID:" << id1;

    // Criar um segundo pedido (para testar listagem)
    QList<ItemPedido*> itensPedido2;
    itensPedido2.append(new ItemPedido(p2, 3)); // 3 morangos

    int id2 = service.realizarPedido(itensPedido2, "Rua B, 456");

    qDebug() << "Pedido realizado com ID:" << id2;

    // 5. Listar todos os pedidos do sistema
    qDebug() << "\n===== LISTAGEM DE PEDIDOS =====";

    QList<Pedido*> pedidos = service.listarPedidos();

    for (Pedido *pedido : pedidos)
    {
        qDebug() << "\nPedido:";
        qDebug() << "Total:" << pedido->total();

        // Listar itens do pedido
        for (ItemPedido *item : pedido->itens())
        {
            qDebug()
                << "Produto:" << item->nomeProduto()
                << "| Quantidade:" << item->quantidade()
                << "| Subtotal:" << item->subtotal();
        }
    }

    qDebug() << "\n===== FIM DO TESTE =====";

    return 0;
}