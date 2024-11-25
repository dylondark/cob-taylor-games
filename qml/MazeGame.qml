import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml 2.15
import QMLControllers

Item {
    id: root
    width: 2160
    height: 3840

    signal quit
    signal saveScore(int game, string username, int score)

    property real scaleFactor: height / 3840
    property int points: 0
    property string strName: "Maze"
    property string username: ""
    property int gameEnum: 5 // Utilities number.


    ColumnLayout {
        id: baseLayout
        anchors.fill: parent
        spacing: 0

        // Background Gradient
        Rectangle {
            id: background
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.verticalStretchFactor: 6
            Layout.minimumHeight: 1
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3f51b1" }
                GradientStop { position: 1.0; color: "#cc6b8e" }
            }


            // Menu Base
            MenuBase {
                id: menuBase
                imageSource: filepath + "/menufiles/MazePreview.png"
                anchors.centerIn: parent
            }

            // Start Screen
            Column {
                id: startScreen
                spacing: 40 * scaleFactor
                anchors.centerIn: parent
                visible: !gameBase.visible && !gameOverBase.visible
            }

            // Game Base - Game controls and logic
            Item {
                id: gameBase
                anchors.fill: parent
                visible: false

                function startGame() {
                    root.points = 0
                    gameBase.visible = true
                    startScreen.visible = false
                    gameOverBase.visible = false
                }

                function endGame() {
                    gameOverBase.showGameOver()
                }

                // Controls Layout - Directional Controls
                GridLayout {
                    id: controlsLayout
                    columns: 3
                    Layout.preferredHeight: 300 * scaleFactor
                    Layout.preferredWidth: 300 * scaleFactor
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom

                    Item {}

                    Rectangle {
                        width: 80 * scaleFactor
                        height: 80 * scaleFactor
                        radius: 10 * scaleFactor
                        color: "#3366cc"
                        border.color: "#003399"
                        border.width: 3
                        Text { text: "Up"; anchors.centerIn: parent; font.pixelSize: 30 * scaleFactor; color: "white" }
                    }

                    Item {}

                    Rectangle {
                        width: 80 * scaleFactor
                        height: 80 * scaleFactor
                        radius: 10 * scaleFactor
                        color: "#3366cc"
                        border.color: "#003399"
                        border.width: 3
                        Text { text: "Left"; anchors.centerIn: parent; font.pixelSize: 30 * scaleFactor; color: "white" }
                    }

                    Rectangle {
                        width: 80 * scaleFactor
                        height: 80 * scaleFactor
                        radius: 10 * scaleFactor
                        color: "#3366cc"
                        border.color: "#003399"
                        border.width: 3
                        Text { text: "Down"; anchors.centerIn: parent; font.pixelSize: 30 * scaleFactor; color: "white" }
                    }

                    Rectangle {
                        width: 80 * scaleFactor
                        height: 80 * scaleFactor
                        radius: 10 * scaleFactor
                        color: "#3366cc"
                        border.color: "#003399"
                        border.width: 3
                        Text { text: "Right"; anchors.centerIn: parent; font.pixelSize: 30 * scaleFactor; color: "white" }
                    }
                }
            }

            // Game Over Screen
            GameOverBase {
                id: gameOverBase
                anchors.fill: parent
                visible: false
            }

            Connections {
                target: gameBase
                onEndGame: gameOverBase.showGameOver()
            }


            MazeController {
                id: controller
                anchors.top: parent.top
                anchors.left: holdRectangle.right
                height: parent.height
                width: height / 2
            }

        }


    // Home Bar Base
    HomeBarBase {
        id: homeBarBase
        Layout.verticalStretchFactor: 1
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.minimumHeight: 1
    }
}
}
