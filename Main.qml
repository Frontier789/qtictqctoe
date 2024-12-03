import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("QTicTacToe")

    Rectangle {
        anchors.fill: parent
        color: "lightblue"

        GridLayout {
            id: board_grid
            columns: 3
            anchors.centerIn: parent
            width: Math.min(parent.width, parent.height)
            height: width

            Repeater {
                model: 9
                delegate: Button {
                    required property int index
                    text: "Button " + (index + 1)
                    onClicked: ticTacToe.processUserChoice(index)
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }
}
