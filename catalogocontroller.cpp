#include "catalogocontroller.h"

CatalogoController::CatalogoController(QObject *parent)
    : QObject(parent)
{
    // DADOS DE TESTE INICIAIS
    // Assim Sque o sistema abrir, já teremos dois produtos cadastrados.
    // Note que o segundo tem estoque ZERO, então o seu sistema já deve
    // classificá-lo automaticamente como "Sob Encomenda"!
    adicionarProduto("Pão de Alho Tradicional", 15.00, 10);
    adicionarProduto("Pão de Alho Picante", 16.50, 0);
}

QList<QObject*> CatalogoController::produtos() const
{
    return m_produtos;
}

void CatalogoController::adicionarProduto(const QString &nome, double preco, int estoque)
{
    // Cria um novo produto na memória
    Produto *novoProduto = new Produto(nome, preco, estoque, this);

    // Adiciona o produto na nossa lista interna
    m_produtos.append(novoProduto);

    // Dispara o alarme avisando a interface visual que a lista cresceu
    emit produtosChanged();
}
