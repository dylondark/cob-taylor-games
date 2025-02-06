/*
    PongGame.qml

    Main QML file for the Pong game.
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
    //title: "Pong Game Layout"

    signal quit  // Signal to go to home screen or quit the game
    signal saveScore(int game, string username, int score)

    property real scaleFactor: height / 3840
    property int points: 0
    property string strName: "Pong"
    property string username: ""
    property int gameEnum: 4

    ColumnLayout{
        id: baseLayout
        anchors.fill: parent
        spacing: 0

        // Define the background of the game
        Rectangle {
            id: background
            Layout.preferredHeight: -1
            Layout.preferredWidth: -1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.verticalStretchFactor: 6

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#f3a469" }
                GradientStop { position: 1.0; color: "#3f51b1" }
            }

            MenuBase { // This opens the screen to input username at the beginning.
                id: menuBase
                imageSource: filepath + "/menufiles/PongMotion.png"
                // z: 1
            }

            Item {
                id: gameBase
                anchors.fill: parent
                visible: false
                // Put the code for the scores boxes here

                RowLayout {
                    id: topBar
                    anchors.top: parent.top
                    width: parent.width
                    height: 100
                    spacing: 20

                    // Score Section
                    // Player Score Section
                    Rectangle {
                        id: playerScoreBox
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "#D2B48C"
                        border.color: "black"
                        Text {
                            id: playerScoreText
                            anchors.centerIn: parent
                            text: "Player Score: " + (controller.playerScore !== undefined ? controller.playerScore : 0)
                            font.pixelSize: 24
                            color: "navy"
                            }
                        }
                    Rectangle {
                            id: aiScoreBox
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            color: "#D2B48C"
                            border.color: "black"
                            Text {
                                id: aiScoreText
                                anchors.centerIn: parent
                                text: "AI Score: " + (controller.aiScore !== undefined ? controller.aiScore : 0)
                                font.pixelSize: 24
                                color: "navy"
                            }
                        }

                    // Time Section
                    // Rectangle {
                    //     id: timeBox
                    //     Layout.fillWidth: true
                    //     Layout.fillHeight: true
                    //     color: "#D2B48C"  // Light brown background for the time
                    //     border.color: "black"
                    //     Text {
                    //         anchors.centerIn: parent
                    //         text: "Time: 0"
                    //         font.pixelSize: 20
                    //         color: "navy"
                    //     }
                    // }

                }


                PongController {
                    id: controller
                    anchors.top: parent.top
                    anchors.left: parent.right
                    anchors.centerIn: parent
                    height: 3040 * root.scaleFactor
                    width: 1550 * root.scaleFactor
                    smooth: false
                    focus: true  // Ensure PongController gets keyboard input

                    Component.onCompleted: {
                            console.log("Setting focus to PongController...");
                            controller.forceActiveFocus();
                            console.log("PongController focus status (QML):", controller.focus);
                        }

                    Keys.onPressed: event => {
                            console.log("Key Pressed in QML:", event.key);
                            controller.keyPressEvent(event);
                        }

                    Keys.onReleased: event => {
                            controller.keyReleaseEvent(event);
                        }
                }
                Connections {
                    target: controller
                    function onScoreUpdated() {
                        playerScoreText.text = "Player1 Score: " + controller.playerScore;
                        aiScoreText.text = "Player2 Score: " + controller.aiScore;
                    }
                }

                RowLayout {
                    id: playerControls
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 50

                    // Player 1 Controls
                    ColumnLayout {
                        spacing: 10

                        Text {
                            text: "Player 1 Controls"
                            font.pixelSize: 20
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                        }

                        RowLayout {
                            spacing: 10

                            // Timer for Player 1 Movement
                            Timer {
                                id: moveTimerPlayer1
                                interval: 50
                                running: false
                                repeat: true
                                onTriggered: {
                                    if (leftButtonPlayer1.pressed) {
                                        controller.moveLeftPaddle1();
                                    } else if (rightButtonPlayer1.pressed) {
                                        controller.moveRightPaddle1();
                                    }
                                }
                            }

                            Button {
                                id: leftButtonPlayer1
                                text: "Left"
                                onPressed: moveTimerPlayer1.start()
                                onReleased: moveTimerPlayer1.stop()
                                width: 200
                                height: 100
                            }

                            Button {
                                id: rightButtonPlayer1
                                text: "Right"
                                onPressed: moveTimerPlayer1.start()
                                onReleased: moveTimerPlayer1.stop()
                                width: 200
                                height: 100
                            }
                            Keys.onPressed: (event) => {
                                switch (event.key) {
                                    case Qt.Key_A: // Move Player Paddle Left
                                        controller.moveLeftPaddle1();
                                        break;
                                    case Qt.Key_S: // Move Player Paddle Right
                                        controller.moveRightPaddle1();
                                        break;
                                    case Qt.Key_Left: // Move AI Paddle Left
                                        controller.moveLeftPaddle2();
                                        break;
                                    case Qt.Key_Right: // Move AI Paddle Right
                                        controller.moveRightPaddle2();
                                        break;
                                    default:
                                        break;
                                }
                            }

                        }
                    }

                    // Player 2 Controls
                    ColumnLayout {
                        spacing: 10

                        Text {
                            text: "Player 2 Controls"
                            font.pixelSize: 20
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                        }

                        RowLayout {
                            spacing: 10

                            // Timer for Player 2 Movement
                            Timer {
                                id: moveTimerPlayer2
                                interval: 50
                                running: false
                                repeat: true
                                onTriggered: {
                                    if (leftButtonPlayer2.pressed) {
                                        controller.moveLeftPaddle2();
                                    } else if (rightButtonPlayer2.pressed) {
                                        controller.moveRightPaddle2();
                                    }
                                }
                            }

                            Button {
                                id: leftButtonPlayer2
                                text: "Left"
                                onPressed: moveTimerPlayer2.start()
                                onReleased: moveTimerPlayer2.stop()
                                width: 200
                                height: 100
                            }

                            Button {
                                id: rightButtonPlayer2
                                text: "Right"
                                onPressed: moveTimerPlayer2.start()
                                onReleased: moveTimerPlayer2.stop()
                                width: 200
                                height: 100
                            }
                        }
                    }
                }

            }
        }

        HomeBarBase {
            id: homeBarBase
            Layout.verticalStretchFactor: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 1

        }
    } // Column Layout
}
