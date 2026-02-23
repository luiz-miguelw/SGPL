import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 400
    height: 600
    visible: true
    title: "SGPL - Gestão de Catálogo"
    color: "#f4f4f4"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Text {
            text: "Vitrine de Produtos"
            font.pixelSize: 24
            font.bold: true
            color: "#b22222" // Vermelho fogo/churrasco
        }

        // Lista de Produtos
        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: catalogo.produtos // Usa a lista que injetamos no main.cpp
            clip: true
            spacing: 10

            delegate: Rectangle {
                width: parent.width
                height: 80
                color: "white"
                radius: 8
                border.color: modelData.sobEncomenda ? "#ffa500" : "#ddd" // Laranja se for encomenda
                border.width: 2

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 15

                    ColumnLayout {
                        Text {
                            text: modelData.nome
                            font.bold: true
                            font.pixelSize: 16
                        }
                        Text {
                            text: "Preço: R$ " + modelData.preco.toFixed(2)
                            color: "#666"
                        }
                    }

                    Item { Layout.fillWidth: true } // Isso substitui o Spacer e empurra o estoque para a direita
                    ColumnLayout {
                        Layout.alignment: Qt.AlignRight
                        Text {
                            text: "Estoque: " + modelData.estoque
                            font.pixelSize: 12
                            color: modelData.estoque > 0 ? "green" : "red"
                        }
                        // Badge de Status (Regra de Negócio Visível)
                        Rectangle {
                            width: 100; height: 20
                            radius: 10
                            color: modelData.sobEncomenda ? "#fff3e0" : "#e8f5e9"
                            Text {
                                anchors.centerIn: parent
                                text: modelData.sobEncomenda ? "SOB ENCOMENDA" : "PRONTA ENTREGA"
                                font.pixelSize: 10
                                font.bold: true
                                color: modelData.sobEncomenda ? "#ef6c00" : "#2e7d32"
                            }
                        }
                    }
                }
            }
        }

        // Botão Simples para teste
        Button {
            Layout.fillWidth: true
            text: "Adicionar Novo Sabor (Teste)"
            onClicked: {
                // Chama a função do C++ diretamente!
                catalogo.adicionarProduto("Pão de Alho com Queijo", 18.90, 5)
            }
        }
    }
}
