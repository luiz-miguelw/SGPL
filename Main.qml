import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: mainWindow
    width: 450
    height: 700
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
            color: "#b22222"
        }

        // --- LISTAGEM DE PRODUTOS ---
        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: catalogo.produtos
            clip: true
            spacing: 10

            delegate: Rectangle {
                width: ListView.view.width
                height: 80
                color: "white"
                radius: 8
                border.color: modelData.sobEncomenda ? "#ffa500" : "#ddd"
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

                    Item { Layout.fillWidth: true }

                    ColumnLayout {
                        Layout.alignment: Qt.AlignRight
                        Text {
                            text: "Estoque: " + modelData.estoque
                            font.pixelSize: 12
                            color: modelData.estoque > 0 ? "green" : "red"
                        }
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
    }

    // --- BOTÃO FLUTUANTE DE ADICIONAR (+) ---
    RoundButton {
        text: "+"
        font.pixelSize: 28
        width: 60
        height: 60
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 25
        palette.button: "#b22222"
        palette.buttonText: "white"

        // Ao clicar, abre a janela de cadastro
        onClicked: janelaCadastro.open()
    }

    // --- JANELA DE CADASTRO (POPUP MODAL) ---
    Popup {
        id: janelaCadastro
        width: 320
        height: 300
        anchors.centerIn: parent
        modal: true // Escurece o fundo e bloqueia cliques fora
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        background: Rectangle {
            color: "white"
            radius: 10
            border.color: "#ccc"
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 15

            Text {
                text: "Novo Produto"
                font.bold: true
                font.pixelSize: 20
                Layout.alignment: Qt.AlignHCenter
            }

            TextField {
                id: inputNome
                Layout.fillWidth: true
                placeholderText: "Nome do produto"
            }

            TextField {
                id: inputPreco
                Layout.fillWidth: true
                placeholderText: "Preço (ex: 15.50)"
                validator: RegularExpressionValidator { regularExpression: /^[0-9]+(\.[0-9]{1,2})?$/ }
            }

            TextField {
                id: inputEstoque
                Layout.fillWidth: true
                placeholderText: "Estoque inicial"
                validator: IntValidator { bottom: 0 }
            }

            // Botoes de Ação
            RowLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight
                spacing: 10
                Layout.topMargin: 10

                Button {
                    text: "Cancelar"
                    onClicked: {
                        janelaCadastro.close()
                    }
                }

                Button {
                    text: "Salvar"
                    palette.button: "#2e7d32" // Verde
                    palette.buttonText: "white"
                    onClicked: {
                        // Só salva se os campos estiverem preenchidos
                        if (inputNome.text !== "" && inputPreco.text !== "" && inputEstoque.text !== "") {

                            // 1. Envia para o C++
                            catalogo.adicionarProduto(
                                inputNome.text,
                                parseFloat(inputPreco.text),
                                parseInt(inputEstoque.text)
                            )

                            // 2. Limpa os campos para o próximo uso
                            inputNome.text = ""
                            inputPreco.text = ""
                            inputEstoque.text = ""

                            // 3. Fecha a janela com sucesso
                            janelaCadastro.close()
                        }
                    }
                }
            }
        }
    }
}
