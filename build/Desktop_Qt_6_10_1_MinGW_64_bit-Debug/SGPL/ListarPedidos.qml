import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: paginaListaPedidos
    background: Rectangle { color: "#f4f4f4" }

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
                text: "Listar Pedidos"
                font.pixelSize: 18
                font.bold: true
                color: "white"
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter
            }
            Item { Layout.preferredWidth: 60 }
        }
    }

    Component.onCompleted: {
        listaPedidos.model = pedidoController.listarPedidos()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        Button {
            text: "Atualizar Lista"
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            background: Rectangle { color: "#2e7d32"; radius: 5 }
            contentItem: Text { text: "Atualizar Lista"; color: "white"; font.bold: true; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }

            onClicked: {
                listaPedidos.model = pedidoController.listarPedidos()
            }
        }

        ListView {
            id: listaPedidos
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 10

            delegate: Rectangle {
                width: listaPedidos.width
                height: 110
                border.width: 1
                border.color: "#cccccc"
                radius: 8

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 2

                    Text { text: "Total: R$ " + modelData.total().toFixed(2); font.bold: true; font.pixelSize: 16 }
                    Text { text: "Endereço: " + modelData.endereco; font.pixelSize: 14 }
                    Text { text: "Pag. / Agendamento: " + modelData.pagamento + " | " + (modelData.agendamento === "" ? "Imediato" : modelData.agendamento); font.pixelSize: 12; color: "#555" }
                    Text { text: "Status: " + modelData.status; font.pixelSize: 12; color: "#b22222"; font.bold: true }
                    Text { text: "Qtd Itens: " + modelData.itens().length; font.pixelSize: 12 }
                }
            }
        }
    }
}