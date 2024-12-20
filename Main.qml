pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import tictactoe.cellState 1.0
import tictactoe.gameState 1.0

Window {
    width: 640
    height: 480
    minimumWidth: 300
    minimumHeight: 300
    visible: true
    title: qsTr("QTicTacToe")

    Rectangle {
        id: board_background
        anchors.fill: parent
        color: "lightblue"

        Text {
            text: winText()
            color: "black"
            font.pixelSize: 15
            anchors.top: parent.top
            anchors.left: parent.left

            function winText()
            {
                if (ticTacToe === null) {
                    return "Exiting"
                }

                return "Human: " + ticTacToe.humanWins
            }
        }

        Text {
            text: winText()
            color: "black"
            font.pixelSize: 15
            anchors.top: parent.top
            anchors.right: parent.right

            function winText()
            {
                if (ticTacToe === null) {
                    return "Exiting"
                }

                return "Computer: " + ticTacToe.computerWins
            }
        }

        Text {
            text: stateText()
            color: "black"
            font.pixelSize: 24

            function stateText()
            {
                if (ticTacToe === null) {
                    return "Exiting"
                }

                switch (ticTacToe.gameState) {
                    case GameState.TurnOfPlayerO: return "Player O's turn.";
                    case GameState.TurnOfPlayerX: return "Player X's turn.";
                    case GameState.WonByPlayerO: return "Player O won!";
                    case GameState.WonByPlayerX: return "Player X won!";
                    case GameState.Draw: return "It's a draw!";
                    case GameState.MainMenu: return "Welcome to QTicTacToe!";
                }
            }

            anchors.horizontalCenter: parent.horizontalCenter
        }

        GridLayout {
            id: board_grid
            columns: 3
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: Math.min(parent.width, parent.height - 50)
            height: width
            visible: ticTacToe !== null && !ticTacToe.isInMenu

            Repeater {
                model: 9
                delegate: Button {
                    required property int index
                    text: textFromCellValue()
                    onClicked: ticTacToe.processUserChoice(index)
                    enabled: cellValue() == CellState.Empty && isPlayerTurn()
                    font.pixelSize: 35
                    palette.buttonText: colorFromCellValue()

                    Layout.preferredWidth: parent.width / 3
                    Layout.fillHeight: true

                    function cellValue() {
                        if (ticTacToe === null) {
                            return CellState.Empty
                        }

                        return ticTacToe.cells[index]
                    }

                    function isPlayerTurn() {
                        if (ticTacToe === null) {
                            return false
                        }

                        return !ticTacToe.isComputerTurn && !ticTacToe.isGameOver
                    }

                    function textFromCellValue() {
                        switch (cellValue()) {
                            case CellState.Empty: return "_";
                            case CellState.FullX: return "X";
                            case CellState.FullO: return "O";
                        }
                    }

                    function colorFromCellValue() {
                        switch (cellValue()) {
                            case CellState.Empty: return "black";
                            case CellState.FullX: return "blue";
                            case CellState.FullO: return "red";
                        }
                    }
                }
            }
        }

        GridLayout {
            columns: 2
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: Math.min(parent.width, parent.height - 50)
            height: width
            visible: ticTacToe !== null && ticTacToe.isInMenu

            Button {
                text: "Let the computer start"
                onClicked: ticTacToe.startGame(true)

                Layout.preferredWidth: parent.width / 2
                Layout.fillHeight: true
            }

            Button {
                text: "I would like to start"
                onClicked: ticTacToe.startGame(false)

                Layout.preferredWidth: parent.width / 2
                Layout.fillHeight: true
            }
        }
    }

    // NOTE: For debugging, not thread safe
    // Shortcut {
    //     sequence: "Ctrl+R"
    //     onActivated: ticTacToe.restart()
    // }
}
