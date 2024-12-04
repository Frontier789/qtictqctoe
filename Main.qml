pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import tictactoe.utils 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("QTicTacToe")

    Rectangle {
        id: board_background
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
                    text: textFromCellValue()
                    onClicked: ticTacToe.processUserChoice(index)
                    enabled: cellValue() == CellState.Empty

                    Layout.preferredWidth: parent.width / 3
                    Layout.fillHeight: true

                    function cellValue() {
                        if (ticTacToe === null) {
                            return CellState.Empty
                        }

                        return ticTacToe.cells[index]
                    }

                    function textFromCellValue() {
                        switch (cellValue()) {
                            case CellState.Empty: return "_";
                            case CellState.FullX: return "X";
                            case CellState.FullO: return "O";
                        }
                    }
                }
            }
        }
    }

    Shortcut {
        sequence: "Ctrl+R"
        onActivated: ticTacToe.reset()
    }
}
