#ifndef PRODUTO_H
#define PRODUTO_H

#include <QObject>

class Produto : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString nome READ nome WRITE setNome NOTIFY nomeChanged)
    Q_PROPERTY(double preco READ preco WRITE setPreco NOTIFY precoChanged)
    Q_PROPERTY(int estoque READ estoque WRITE setEstoque NOTIFY estoqueChanged)
    Q_PROPERTY(bool sobEncomenda READ sobEncomenda NOTIFY estoqueChanged)

public:
    explicit Produto(QObject *parent = nullptr);
    Produto(const QString &nome, double preco, int estoque, QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    QString nome() const;
    void setNome(const QString &nome);

    double preco() const;
    void setPreco(double preco);

    int estoque() const;
    void setEstoque(int estoque);

    bool sobEncomenda() const;

signals:
    void idChanged();
    void nomeChanged();
    void precoChanged();
    void estoqueChanged();
    void produtoChanged(); // Sinal genérico caso precise

private:
    int m_id = -1;
    QString m_nome;
    double m_preco;
    int m_estoque;
};

#endif // PRODUTO_H
