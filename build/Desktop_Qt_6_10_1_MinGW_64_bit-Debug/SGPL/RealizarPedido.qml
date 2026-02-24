import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: paginaPedido
    background: Rectangle { color: "#f4f4f4" }

    property var carrinho: ({})

    header: ToolBar {
        background: Rectangle { color: "#b22222" }
        RowLayout {
            anchors.fill: parent
            ToolButton {
                contentItem: Text {
                    text: "◀ Voltar"
                    color: "white"
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                onClicked: paginaPedido.StackView.view.pop()
            }
            Label {
                text: "Realizar Pedido"
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
        anchors.margins: 15
        spacing: 15

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: catalogo.produtos
            clip: true
            spacing: 12

            delegate: Rectangle {
                width: ListView.view.width
                height: 90
                color: "white"
                radius: 8
                border.color: modelData.sobEncomenda ? "#ffa500" : "#ddd"
                border.width: 2

                property int qtdSelecionada: paginaPedido.carrinho[modelData.nome] || 0

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 15

                    ColumnLayout {
                        Text { text: modelData.nome; font.bold: true; font.pixelSize: 16 }
                        Text { text: "Preço: R$ " + modelData.preco.toFixed(2); color: "#666" }
                        Rectangle {
                            width: 100; height: 20; radius: 10
                            color: modelData.sobEncomenda ? "#fff3e0" : "#e8f5e9"
                            Text {
                                anchors.centerIn: parent
                                text: modelData.sobEncomenda ? "SOB ENCOMENDA" : "PRONTA ENTREGA"
                                font.pixelSize: 10; font.bold: true
                                color: modelData.sobEncomenda ? "#ef6c00" : "#2e7d32"
                            }
                        }
                    }

                    Item { Layout.fillWidth: true }

                    RowLayout {
                        spacing: 10
                        Button {
                            width: 28; height: 28
                            contentItem: Text { text: "−"; color: "white"; font.bold: true; font.pixelSize: 16; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; bottomPadding: 2 }
                            background: Rectangle { color: qtdSelecionada > 0 ? "#b22222" : "#cccccc"; radius: 14 }
                            onClicked: {
                                if (qtdSelecionada > 0) {
                                    var novoCarrinho = Object.assign({}, paginaPedido.carrinho)
                                    novoCarrinho[modelData.nome] = qtdSelecionada - 1
                                    paginaPedido.carrinho = novoCarrinho
                                }
                            }
                        }
                        Text {
                            text: qtdSelecionada
                            font.pixelSize: 16; font.bold: true; color: qtdSelecionada > 0 ? "black" : "#cccccc"
                            Layout.minimumWidth: 20; horizontalAlignment: Text.AlignHCenter
                        }
                        Button {
                            width: 28; height: 28
                            contentItem: Text { text: "+"; color: "white"; font.bold: true; font.pixelSize: 16; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; bottomPadding: 2 }
                            background: Rectangle { color: "#2e7d32"; radius: 14 }
                            onClicked: {
                                var novoCarrinho = Object.assign({}, paginaPedido.carrinho)
                                novoCarrinho[modelData.nome] = qtdSelecionada + 1
                                paginaPedido.carrinho = novoCarrinho
                            }
                        }
                    }
                }
            }
        }
        
        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: "#cccccc"
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.preferredHeight: 250
            clip: true

            ColumnLayout {
                width: parent.width
                spacing: 10

                TextField {
                    id: enderecoField
                    Layout.fillWidth: true
                    placeholderText: "Endereço de entrega"
                }
                
                ComboBox {
                    id: pagamentoField
                    Layout.fillWidth: true
                    model: ["Dinheiro", "PIX", "Cartão de Crédito", "Cartão de Débito"]
                }

                TextField {
                    id: agendamentoField
                    Layout.fillWidth: true
                    placeholderText: "Data/Hora de Agendamento (Opcional)"
                }

                Button {
                    text: "Finalizar Pedido"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    background: Rectangle { color: "#b22222"; radius: 8 }
                    contentItem: Text { text: "Finalizar Pedido"; color: "white"; font.bold: true; font.pixelSize: 16; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }

                    onClicked: {
                        pedidoController.limparItens()
                        var temSobEncomenda = false
                        var qtdTotal = 0

                        for (var i = 0; i < catalogo.produtos.length; i++) {
                            var p = catalogo.produtos[i]
                            var q = paginaPedido.carrinho[p.nome] || 0
                            if (q > 0) {
                                pedidoController.adicionarItem(p, q)
                                qtdTotal += q
                                if (p.sobEncomenda) {
                                    temSobEncomenda = true
                                }
                            }
                        }

                        if (qtdTotal === 0) {
                            mensagem.text = "Selecione pelo menos um item."
                            mensagem.color = "red"
                            return
                        }

                        if (enderecoField.text === "") {
                            mensagem.text = "O endereço é obrigatório."
                            mensagem.color = "red"
                            return
                        }

                        if (temSobEncomenda && agendamentoField.text === "") {
                            mensagem.text = "Itens sob encomenda exigem data/hora de agendamento!"
                            mensagem.color = "red"
                            return
                        }

                        var id = pedidoController.realizarPedido(enderecoField.text, pagamentoField.currentText, agendamentoField.text)
                        
                        if (id !== -1) {
                            mensagem.text = "Sucesso! Pedido #" + id + " realizado."
                            mensagem.color = "green"
                            paginaPedido.carrinho = {}
                            enderecoField.text = ""
                            agendamentoField.text = ""
                        } else {
                            mensagem.text = "Erro ao processar o pedido."
                            mensagem.color = "red"
                        }
                    }
                }

                Label {
                    id: mensagem
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }
}