import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: paginaVitrine
    background: Rectangle { color: "#f4f4f4" }

    header: ToolBar {
        background: Rectangle { color: "#b22222" }
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "◀ Voltar"
                font.bold: true
                contentItem: Text {
                    text: "◀ Voltar"
                    color: "white"
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                onClicked: paginaVitrine.StackView.view.pop()
            }
            Label {
                text: "Vitrine de Produtos"
                font.pixelSize: 18
                font.bold: true
                color: "white"
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter
            }
            Item { Layout.preferredWidth: 60 }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: catalogo.produtos
            clip: true
            spacing: 12

            delegate: Rectangle {
                width: ListView.view.width
                height: 90 // Aumentei um pouquinho para acomodar os botões bonitos
                color: "white"
                radius: 8
                border.color: modelData.sobEncomenda ? "#ffa500" : "#ddd"
                border.width: 2

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 15

                    ColumnLayout {
                        Text { text: modelData.nome; font.bold: true; font.pixelSize: 16 }
                        Text { text: "Preço: R$ " + modelData.preco.toFixed(2); color: "#666" }
                    }

                    Item { Layout.fillWidth: true }

                    // --- ÁREA DE CONTROLE DE ESTOQUE ---
                    ColumnLayout {
                        Layout.alignment: Qt.AlignRight
                        spacing: 8

                        RowLayout {
                            Layout.alignment: Qt.AlignRight
                            spacing: 10

                            // Botão de diminuir estoque (-)
                            Button {
                                width: 28; height: 28
                                contentItem: Text {
                                    text: "−" // Sinal de menos mais largo
                                    color: "white"
                                    font.bold: true
                                    font.pixelSize: 16
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    // Ajuste fino para centralizar o texto no botão
                                    bottomPadding: 2
                                }
                                background: Rectangle {
                                    // Fica cinza se for 0, vermelho se for maior que 0
                                    color: modelData.estoque > 0 ? "#b22222" : "#cccccc"
                                    radius: 14
                                }
                                onClicked: {
                                    if (modelData.estoque > 0) {
                                        modelData.estoque -= 1
                                    }
                                }
                            }

                            // Número do estoque atual
                            Text {
                                text: modelData.estoque
                                font.pixelSize: 16
                                font.bold: true
                                color: modelData.estoque > 0 ? "black" : "red"
                                Layout.minimumWidth: 20
                                horizontalAlignment: Text.AlignHCenter
                            }

                            // Botão de aumentar estoque (+)
                            Button {
                                width: 28; height: 28
                                contentItem: Text {
                                    text: "+"
                                    color: "white"
                                    font.bold: true
                                    font.pixelSize: 16
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    bottomPadding: 2
                                }
                                background: Rectangle {
                                    color: "#2e7d32" // Verde escuro
                                    radius: 14
                                }
                                onClicked: {
                                    modelData.estoque += 1
                                }
                            }
                        }

                        // Badge de Status da Encomenda
                        Rectangle {
                            Layout.alignment: Qt.AlignRight
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

    RoundButton {
        id: btnAdd
        text: "+"
        width: 60; height: 60
        anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.margins: 25
        contentItem: Text { text: "+"; color: "white"; font.pixelSize: 28; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; bottomPadding: 4 }
        background: Rectangle { color: "#b22222"; radius: 30 }
        onClicked: janelaCadastro.open()
    }

    Popup {
        id: janelaCadastro
        width: 320; height: 320; anchors.centerIn: parent; modal: true; focus: true
        background: Rectangle { color: "white"; radius: 10; border.color: "#ccc" }

        ColumnLayout {
            anchors.fill: parent; anchors.margins: 20; spacing: 15
            Text { text: "Novo Produto"; font.bold: true; font.pixelSize: 20; Layout.alignment: Qt.AlignHCenter }
            TextField { id: inputNome; Layout.fillWidth: true; placeholderText: "Nome do produto" }
            TextField { id: inputPreco; Layout.fillWidth: true; placeholderText: "Preço"; validator: RegularExpressionValidator { regularExpression: /^[0-9]+(\.[0-9]{1,2})?$/ } }
            TextField { id: inputEstoque; Layout.fillWidth: true; placeholderText: "Estoque inicial"; validator: IntValidator { bottom: 0 } }

            RowLayout {
                Layout.fillWidth: true; spacing: 10

                Button {
                    id: btnCancel
                    text: "Cancelar"
                    Layout.fillWidth: true
                    contentItem: Text { text: "Cancelar"; color: "white"; font.bold: true; horizontalAlignment: Text.AlignHCenter }
                    background: Rectangle { color: "#b22222"; radius: 5 }
                    onClicked: janelaCadastro.close()
                }

                Button {
                    id: btnSave
                    text: "Salvar"
                    Layout.fillWidth: true
                    contentItem: Text { text: "Salvar"; color: "white"; font.bold: true; horizontalAlignment: Text.AlignHCenter }
                    background: Rectangle { color: "#2e7d32"; radius: 5 }
                    onClicked: {
                        if (inputNome.text !== "" && inputPreco.text !== "" && inputEstoque.text !== "") {
                            catalogo.adicionarProduto(inputNome.text, parseFloat(inputPreco.text), parseInt(inputEstoque.text))
                            inputNome.text = ""; inputPreco.text = ""; inputEstoque.text = "";
                            janelaCadastro.close()
                        }
                    }
                }
            }
        }
    }
}
