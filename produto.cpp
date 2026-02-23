#include "produto.h"

Produto::Produto(QObject *parent)
    : QObject(parent), m_preco(0.0), m_estoque(0), m_sobEncomenda(true)
{
}

Produto::Produto(QString nome, double preco, int estoque, QObject *parent)
    : QObject(parent), m_nome(nome), m_preco(preco), m_estoque(estoque)
{
    atualizarStatusEncomenda();
}

QString Produto::nome() const { return m_nome; }
void Produto::setNome(const QString &nome) {
    if (m_nome != nome) {
        m_nome = nome;
        emit nomeChanged();
    }
}

double Produto::preco() const { return m_preco; }
void Produto::setPreco(double preco) {
    if (m_preco != preco) {
        m_preco = preco;
        emit precoChanged();
    }
}

int Produto::estoque() const { return m_estoque; }
void Produto::setEstoque(int estoque) {
    if (m_estoque != estoque) {
        m_estoque = estoque;
        emit estoqueChanged();
        atualizarStatusEncomenda(); // Gatilho do Requisito 1
    }
}

bool Produto::sobEncomenda() const { return m_sobEncomenda; }

// Regra de Negócio: Gestão de Disponibilidade e Produção
void Produto::atualizarStatusEncomenda() {
    bool novoStatus = (m_estoque <= 0);
    if (m_sobEncomenda != novoStatus) {
        m_sobEncomenda = novoStatus;
        emit sobEncomendaChanged(); // Avisa o sistema da mudança
    }
}


