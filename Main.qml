import QtQuick
import QtQuick.Controls

Window {
    id: mainWindow
    width: 450
    height: 700
    visible: true
    title: "SGPL - Sistema de Gestão"
    color: "#f4f4f4"

    // O StackView gerencia a navegação carregando os outros arquivos QML
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: "MenuPrincipal.qml"
    }
}
