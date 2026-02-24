import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
// REMOVI O IMPORT QUE DAVA ERRO

Page {
    id: paginaPedido
    background: Rectangle { color: "#f8f9fa" }

    property var carrinho: ({})
    property double totalPedido: 0.0

    onCarrinhoChanged: {
        var soma = 0.0
        for (var i = 0; i < catalogo.produtos.length; i++) {
            var p = catalogo.produtos[i]
            var qtd = carrinho[p.nome] || 0
            if (qtd > 0) {
                soma += p.preco * qtd
            }
        }
        totalPedido = soma
    }

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

        // LISTA DE PRODUTOS
        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: catalogo.produtos
            clip: true
            spacing: 12

            delegate: Rectangle {
                width: ListView.view.width
                height: 95
                color: "white"
                radius: 10
                // EM VEZ DE SOMBRA, USAMOS UMA BORDA SUTIL
                border.color: modelData.sobEncomenda ? "#ffa500" : "#e0e0e0"
                border.width: modelData.sobEncomenda ? 2 : 1

                property int qtdSelecionada: paginaPedido.carrinho[modelData.nome] || 0

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 15

                    ColumnLayout {
                        Text { text: modelData.nome; font.bold: true; font.pixelSize: 16; color: "#333" }
                        Text { text: "Preço: R$ " + modelData.preco.toFixed(2); color: "#666" }

                        Rectangle {
                            width: 110; height: 22; radius: 4
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

                    // CONTROLES DE QUANTIDADE
                    RowLayout {
                        spacing: 10
                        Button {
                            width: 32; height: 32
                            contentItem: Text { text: "−"; color: "white"; font.pixelSize: 18; font.bold: true; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; bottomPadding: 2 }
                            background: Rectangle { color: qtdSelecionada > 0 ? "#b22222" : "#e0e0e0"; radius: 6 }
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
                            font.pixelSize: 18; font.bold: true; color: qtdSelecionada > 0 ? "#333" : "#cccccc"
                            Layout.minimumWidth: 24; horizontalAlignment: Text.AlignHCenter
                        }
                        Button {
                            width: 32; height: 32
                            contentItem: Text { text: "+"; color: "white"; font.pixelSize: 18; font.bold: true; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; bottomPadding: 2 }
                            background: Rectangle { color: "#2e7d32"; radius: 6 }
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

        Rectangle { Layout.fillWidth: true; height: 1; color: "#e0e0e0" }

        // ÁREA DE CHECKOUT (FORMULÁRIO)
        ScrollView {
            Layout.fillWidth: true
            Layout.preferredHeight: 330
            clip: true

            Component {
                id: inputBackground
                Rectangle {
                    color: parent.activeFocus ? "white" : "#f5f5f5"
                    border.color: parent.activeFocus ? "#b22222" : "#e0e0e0"
                    border.width: parent.activeFocus ? 2 : 1
                    radius: 8
                    Behavior on border.color { ColorAnimation { duration: 150 } }
                }
            }

            ColumnLayout {
                width: parent.width - 20
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 15

                // CARTÃO DE TOTAL (Sem sombra, com borda destaque)
                Rectangle {
                    Layout.fillWidth: true
                    height: 70
                    color: "white"
                    radius: 12
                    border.color: "#ddd"
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 20
                        ColumnLayout {
                            spacing: 2
                             Text { text: "Total a pagar"; font.pixelSize: 14; color: "#666" }
                        }
                        Item { Layout.fillWidth: true }
                        Text {
                            text: "R$ " + paginaPedido.totalPedido.toFixed(2)
                            font.pixelSize: 26; font.bold: true; color: "#b22222"
                        }
                    }
                }

                Text { text: "Dados para Entrega"; font.bold: true; font.pixelSize: 16; color: "#333" }

                TextField {
                    id: enderecoField
                    Layout.fillWidth: true
                    Layout.preferredHeight: 45
                    placeholderText: "📍 Endereço completo"
                    font.pixelSize: 14
                    leftPadding: 15
                    background: inputBackground.createObject(enderecoField)
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12
                    ComboBox {
                        id: pagamentoField
                        Layout.fillWidth: true
                        Layout.preferredHeight: 45
                        font.pixelSize: 14
                        leftPadding: 15
                        model: ["💳 Cartão de Crédito", "💳 Cartão de Débito", "💵 Dinheiro", "💠 PIX"]
                        background: Rectangle {
                            color: parent.activeFocus ? "white" : "#f5f5f5"
                            border.color: parent.activeFocus ? "#b22222" : "#e0e0e0"
                            border.width: parent.activeFocus ? 2 : 1
                            radius: 8
                        }
                    }
                    TextField {
                        id: agendamentoField
                        Layout.fillWidth: true
                        Layout.preferredHeight: 45
                        placeholderText: "📅 Agendar (Opcional)"
                        font.pixelSize: 14
                        leftPadding: 15
                        background: inputBackground.createObject(agendamentoField)
                    }
                }

                Button {
                    id: btnFinalizar
                    Layout.fillWidth: true
                    Layout.preferredHeight: 55
                    Layout.topMargin: 10

                    contentItem: Text {
                        text: "✅ FINALIZAR PEDIDO"
                        color: "white"; font.bold: true; font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        color: btnFinalizar.pressed ? "#8b1a1a" : "#b22222"
                        radius: 12
                    }

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
                                if (p.sobEncomenda) { temSobEncomenda = true }
                            }
                        }

                        if (qtdTotal === 0) {
                            mostrarMensagem("Selecione pelo menos um item.", true)
                            return
                        }
                        if (enderecoField.text === "") {
                            mostrarMensagem("O endereço é obrigatório.", true)
                            return
                        }
                        if (temSobEncomenda && agendamentoField.text === "") {
                            mostrarMensagem("Itens sob encomenda exigem agendamento!", true)
                            return
                        }

                        var id = pedidoController.realizarPedido(enderecoField.text, pagamentoField.currentText, agendamentoField.text)

                        if (id !== -1) {
                            mostrarMensagem("Sucesso! Pedido #" + id + " realizado.", false)
                            paginaPedido.carrinho = {}
                            paginaPedido.totalPedido = 0.0
                            enderecoField.text = ""
                            agendamentoField.text = ""
                        } else {
                            mostrarMensagem("Erro ao processar o pedido.", true)
                        }
                    }
                }

                Rectangle {
                    id: boxMensagem
                    Layout.fillWidth: true
                    Layout.preferredHeight: msgLabel.implicitHeight + 20
                    visible: msgLabel.text !== ""
                    color: isError ? "#ffebee" : "#e8f5e9"
                    radius: 8
                    border.color: isError ? "#ef5350" : "#66bb6a"
                    property bool isError: false
                    Text {
                        id: msgLabel
                        anchors.centerIn: parent
                        text: ""
                        font.bold: true
                        color: parent.isError ? "#c62828" : "#2e7d32"
                        width: parent.width - 20
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }
    }

    function mostrarMensagem(texto, erro) {
        msgLabel.text = texto
        boxMensagem.isError = erro
        resetMsgTimer.restart()
    }

    Timer {
        id: resetMsgTimer
        interval: 5000
        onTriggered: msgLabel.text = ""
    }
}
