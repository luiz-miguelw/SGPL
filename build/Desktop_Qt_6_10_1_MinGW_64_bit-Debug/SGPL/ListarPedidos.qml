import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: paginaListaPedidos
    background: Rectangle { color: "#f8f9fa" }

    // --- CORREÇÃO DO CARREGAMENTO ---
    // 1. Carrega assim que a tela é criada
    Component.onCompleted: {
        listaPedidos.model = pedidoController.listarPedidos()
    }

    // 2. Carrega também se a tela ficar visível novamente (ex: voltando de outra tela)
    onVisibleChanged: {
        if (visible) {
            listaPedidos.model = pedidoController.listarPedidos()
        }
    }
    // -------------------------------

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
                onClicked: paginaListaPedidos.StackView.view.pop()
            }
            Label {
                text: "Histórico de Pedidos"
                font.pixelSize: 18
                font.bold: true
                color: "white"
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter
            }
            ToolButton {
                contentItem: Text {
                    text: "↻"
                    color: "white"
                    font.pixelSize: 24
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                onClicked: listaPedidos.model = pedidoController.listarPedidos()
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 15

        ListView {
            id: listaPedidos
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 12

            // O modelo começa vazio e é preenchido automaticamente
            model: []

            delegate: Rectangle {
                width: ListView.view.width
                height: 140
                color: "white"
                radius: 12
                border.color: "#e0e0e0"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 15
                    spacing: 8

                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "Pedido #" + modelData.id
                            font.bold: true; font.pixelSize: 16; color: "#333"
                        }
                        Item { Layout.fillWidth: true }
                        Rectangle {
                            color: modelData.status === "Realizado" ? "#e8f5e9" : "#fff3e0"
                            radius: 4
                            width: labelStatus.implicitWidth + 16; height: 22
                            Text {
                                id: labelStatus
                                anchors.centerIn: parent
                                text: modelData.status
                                font.pixelSize: 11; font.bold: true
                                color: modelData.status === "Realizado" ? "#2e7d32" : "#ef6c00"
                            }
                        }
                    }

                    Rectangle { Layout.fillWidth: true; height: 1; color: "#f0f0f0" }

                    RowLayout {
                        spacing: 10
                        Text { text: "📍"; font.pixelSize: 14 }
                        Text {
                            text: modelData.endereco
                            font.pixelSize: 14; color: "#555"
                            Layout.fillWidth: true; elide: Text.ElideRight
                        }
                    }

                    RowLayout {
                        spacing: 10
                        Text { text: "💳"; font.pixelSize: 14 }
                        Text { text: modelData.pagamento; font.pixelSize: 13; color: "#666" }
                        Text { text: "•"; color: "#ccc" }
                        Text { text: "📅"; font.pixelSize: 14 }
                        Text {
                            text: modelData.agendamento === "" ? "Entrega Imediata" : modelData.agendamento
                            font.pixelSize: 13; color: "#666"
                        }
                    }

                    Item { Layout.fillHeight: true }

                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "Total:"
                            font.pixelSize: 14; color: "#666"
                            Layout.alignment: Qt.AlignVCenter
                        }

                        Text {
                            // Agora isso vai mostrar o valor correto!
                            text: "R$ " + modelData.total.toFixed(2)
                            font.bold: true; font.pixelSize: 18; color: "#b22222"
                            Layout.alignment: Qt.AlignVCenter
                        }
                    }
                }
            }
        }
    }
}
