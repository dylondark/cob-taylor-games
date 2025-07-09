/*
    MazeGame.qml

    Main QML file for the Maze Game.
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import QMLControllers

Item {
    id: root
    width: 2160
    height: 3840
    signal quit
    signal saveScore(int game, string username, int score)

    property real scaleFactor: height / 3840
    property int points: 30000
    property string strName: "Maze"
    property string username: ""

    ColumnLayout {
        id: baseLayout
        anchors.fill: parent
        spacing: 0

        // Background
        Rectangle {
            id: background
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.verticalStretchFactor: 6

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#f3a469" }
                GradientStop { position: 1.0; color: "#3f51b1" }
            }

            MenuBase {
                id: menuBase
                imageSource: filepath + "/menufiles/PongMotion.png"
            }

            Item {
                id: gameBase
                anchors.fill: parent
                visible: false

                function startGame() {
                    controller.startGame();
                }

                Component.onCompleted: homeBarBase.updatePoints();

                Rectangle {
                    id: dataRow
                    anchors.top: parent.top
                    width: parent.width
                    height: parent.height / 10
                    color: "#D2B48C"
                    border.color: "black"

                    ColumnLayout {
                        anchors.fill: parent
                        //spacing: 40 * root.scaleFactor

                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Text {
                                id: timeRemainingTitle
                                anchors.centerIn: parent
                                text: "Time Remaining:"
                                font.pixelSize: 60 * root.scaleFactor
                                font.bold: true
                                color: "navy"
                            }
                        }

                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Text {
                                id: timeRemainingValue
                                anchors.centerIn: parent
                                text: "5:00:00"
                                font.pixelSize: 120 * root.scaleFactor
                                font.bold: true
                                color: "navy"
                            }
                        }
                    }
                }

                // Maze Controller (Only One Instance)
                MazeController {
                    id: controller
                    width: 1550 * root.scaleFactor
                    height: 3040 * root.scaleFactor
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.verticalStretchFactor: 4
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 1.5
                    onMazeGenerated: {
                        console.log("Maze generated! Timer starts now.");
                        gameTimer.running = true;  // Start the timer
                        gameTimer.restart();       // Restart to ensure it runs
                    }
                }
                // Timer to Start Counting in MM:SS:MS Format
                Timer {
                    id: gameTimer
                    interval: 10  // Runs every 10 milliseconds (0.01s)
                    repeat: true
                    running: false  // Initially off

                    property int elapsedTime: 300000  // Total elapsed time in milliseconds

                    onTriggered: {
                        if (controller.isGameOver())
                        {
                            gameBase.visible = false;
                            gameOverBase.gameOverOps();
                            gameTimer.running = false;  // Stop the timer
                            return; // Exit if the game is over
                        }

                        elapsedTime -= 10;  // Decrease by 10ms each tick
                        points -= 1; // Decrease by 1 pt each tick
                        homeBarBase.updatePoints();

                        // Convert elapsed time to MM:SS:MS format
                        var minutes = Math.floor(elapsedTime / 60000);
                        var seconds = Math.floor((elapsedTime % 60000) / 1000);
                        var milliseconds = (elapsedTime % 1000) / 10;  // Get two-digit MS

                        // Format to always show two digits (e.g., 02:05:09)
                        var formattedTime =
                            (minutes < 10 ? "0" + minutes : minutes) + ":" +
                            (seconds < 10 ? "0" + seconds : seconds) + ":" +
                            (milliseconds < 10 ? "0" + milliseconds : milliseconds);

                        // Update UI
                        timeRemainingValue.text = formattedTime;

                        // Re-enable for debugging.
                        //console.log("Stopwatch running: " + formattedTime);
                    }
                }
                // Button Layout
                Item {
                    id: buttonLayout
                    Layout.preferredHeight: 400 * root.scaleFactor
                    Layout.preferredWidth: parent.width
                    anchors.top: controller.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: true

                    GridLayout {
                        id: buttonGrid
                        columns: 3
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Button { // UP
                            id: upBtn
                            Layout.row: 0
                            Layout.column: 1
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredWidth: 50
                            Layout.preferredHeight: 80
                            background: Rectangle {
                                color: "white"
                                opacity: 70
                                border.color: "black"
                                radius: 10
                                anchors.fill: parent
                                Image {
                                    anchors.fill: parent
                                    source: filepath + "/gamefiles/Tetroos/UpArrow.png"
                                    fillMode: Image.PreserveAspectFit
                                    smooth: true
                                }
                            }
                            onPressed: controller.upAction()
                        }

                        Button { // LEFT
                            id: leftBtn
                            Layout.row: 1
                            Layout.column: 0
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 100
                            background: Rectangle {
                                color: "white"
                                opacity: 70
                                border.color: "black"
                                radius: 10
                                anchors.fill: parent
                                Image {
                                    anchors.fill: parent
                                    source: filepath + "/gamefiles/Tetroos/LftArrow.png"
                                    fillMode: Image.PreserveAspectFit
                                    smooth: true
                                }
                            }
                            onPressed: controller.leftAction()
                        }

                        Button { // DOWN
                            id: downBtn
                            Layout.row: 1
                            Layout.column: 1
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 100
                            background: Rectangle {
                                color: "white"
                                opacity: 70
                                border.color: "black"
                                radius: 10
                                anchors.fill: parent
                                Image {
                                    anchors.fill: parent
                                    source: filepath + "/gamefiles/Tetroos/DwnArrow.png"
                                    fillMode: Image.PreserveAspectFit
                                    smooth: true
                                }
                            }
                            onPressed: controller.downAction()
                        }

                        Button { // RIGHT
                            id: rightBtn
                            Layout.row: 1
                            Layout.column: 2
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 100
                            background: Rectangle {
                                color: "white"
                                opacity: 70
                                border.color: "black"
                                radius: 10
                                anchors.fill: parent
                                Image {
                                    anchors.fill: parent
                                    source: filepath + "/gamefiles/Tetroos/RtArrow.png"
                                    fillMode: Image.PreserveAspectFit
                                    smooth: true
                                }
                            }
                            onPressed: controller.rightAction()
                        }
                    }
                }
            }

            GameOverBase {
                id: gameOverBase
            }
        }

        HomeBarBase {
            id: homeBarBase
            Layout.verticalStretchFactor: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 1
        }
    }

    // Keyboard Controls
    Keys.onPressed: {
        switch (event.key) {
        case Qt.Key_Left:
            controller.leftAction();
            break;
        case Qt.Key_Right:
            controller.rightAction();
            break;
        case Qt.Key_Down:
            controller.downAction();
            break;
        case Qt.Key_Up:
            controller.upAction();
            break;
        }
    }
}
