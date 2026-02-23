#ifndef CATALOGOCONTROLLER_H
#define CATALOGOCONTROLLER_H

#include <QObject>
#include <QList>
#include "produto.h"

class CatalogoController : public QObject
{
    Q_OBJECT
    // Expõe a lista completa de produtos para a interface visual
    Q_PROPERTY(QList<QObject*> produtos READ produtos NOTIFY produtosChanged)

public:
    explicit CatalogoController(QObject *parent = nullptr);

    // Getter da lista
    QList<QObject*> produtos() const;

    // Q_INVOKABLE permite que a interface gráfica chame esta função
    Q_INVOKABLE void adicionarProduto(const QString &nome, double preco, int estoque);

signals:
    void produtosChanged();

private:
    QList<QObject*> m_produtos;
};

#endif // CATALOGOCONTROLLER_H
