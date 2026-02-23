import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: paginaMenu // <-- O SEGREDO ESTÁ AQUI
    background: Rectangle { color: "#f4f4f4" }

    ColumnLayout {
        anchors.centerIn: parent
        width: 250
        spacing: 20

        Text {
            text: "Menu Principal"
            font.pixelSize: 28
            font.bold: true
            color: "#b22222"
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 30
        }

        // Botão Listagem
        Button {
            id: btnListagem
            text: "Listagem de Produtos"
            Layout.fillWidth: true
            Layout.preferredHeight: 50

            contentItem: Text {
                text: btnListagem.text
                font.pixelSize: 16
                font.bold: true
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                color: btnListagem.down ? "#8b1a1a" : "#b22222"
                radius: 8
            }

            // Usando o ID da página para achar o StackView
            onClicked: paginaMenu.StackView.view.push("VitrineProdutos.qml")
        }

        // Botão Pedido
        Button {
            id: btnPedido
            text: "Realizar Pedido"
            Layout.fillWidth: true
            Layout.preferredHeight: 50

            contentItem: Text {
                text: btnPedido.text
                font.pixelSize: 16
                font.bold: true
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                color: btnPedido.down ? "#8b1a1a" : "#b22222"
                radius: 8
            }

            onClicked: console.log("Ação: Redirecionar para tela de pedidos no futuro.")
        }
    }
}
