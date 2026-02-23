#ifndef PRODUTO_H
#define PRODUTO_H

#include <QObject>
#include <QString>

class Produto : public QObject
{
    Q_OBJECT
    // Propriedades expostas para a Interface Visual
    Q_PROPERTY(QString nome READ nome WRITE setNome NOTIFY nomeChanged)
    Q_PROPERTY(double preco READ preco WRITE setPreco NOTIFY precoChanged)
    Q_PROPERTY(int estoque READ estoque WRITE setEstoque NOTIFY estoqueChanged)
    Q_PROPERTY(bool sobEncomenda READ sobEncomenda NOTIFY sobEncomendaChanged)

public:
    explicit Produto(QObject *parent = nullptr);
    Produto(QString nome, double preco, int estoque, QObject *parent = nullptr);

    // Getters
    QString nome() const;
    double preco() const;
    int estoque() const;
    bool sobEncomenda() const;

    // Setters
    void setNome(const QString &nome);
    void setPreco(double preco);
    void setEstoque(int estoque);

signals:
    // Sinais emitidos quando os dados mudam
    void nomeChanged();
    void precoChanged();
    void estoqueChanged();
    void sobEncomendaChanged();

private:
    QString m_nome;
    double m_preco;
    int m_estoque;
    bool m_sobEncomenda;

    void atualizarStatusEncomenda();
};

#endif // PRODUTO_H
