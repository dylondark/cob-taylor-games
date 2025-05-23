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
    property int points: 0
    property string strName: "Pong"
    property string username: ""
    property int gameEnum: 4
    property int scoreDifference: 0

    ColumnLayout {
        id: baseLayout
        anchors.fill: parent
        spacing: 0

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
                imageSource: filepath + "/menufiles/Pong.png"
            }

            Connections {
                target: menuBase
                onPlayClicked: function(name) {
                    root.username = name
                    homeBarBase.updateUsername()
                    menuBase.visible = false
                    gameBase.visible = true
                    gameBase.startGame()
                }
            }

            Item {
                id: gameBase
                anchors.fill: parent
                visible: false

                function startGame() {
                    controller.startGame()
                }

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 0

                    // Scoreboard Row
                    RowLayout {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100 * scaleFactor
                        Layout.margins: 60 * scaleFactor
                        anchors.margins: 8 * scaleFactor
                        spacing: 20

                        Rectangle {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            color: "#D2B48C"
                            border.color: "black"

                            Text {
                                anchors.centerIn: parent
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "Player Score: " + controller.playerScore
                                font.pixelSize: 60 * scaleFactor
                                color: "navy"
                            }
                        }

                        Rectangle {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            color: "#D2B48C"
                            border.color: "black"

                            Text {
                                anchors.centerIn: parent
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "Zippy's Score: " + controller.aiScore
                                font.pixelSize: 60 * root.scaleFactor
                                color: "navy"
                            }
                        }
                    }

                    // Game Canvas Row
                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 2850 * root.scaleFactor
                        anchors.top: parent.top
                        anchors.topMargin: 530 * root.scaleFactor

                        PongController {
                            id: controller
                            anchors.centerIn: parent
                            width: 1550 * root.scaleFactor
                            height: 3040 * root.scaleFactor
                            smooth: false

                            onGameOverSignal: function() {
                                gameBase.visible = false;
                                gameOverBase.gameOverOps();
                            }

                            onScoreDifferenceCalculated: function(scoreDiff) {
                                root.scoreDifference = scoreDiff;
                                root.points = scoreDiff;
                                homeBarBase.updatePoints();
                            }
                        }
                    }

                    // Player Controls Row
                    RowLayout {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 300 * root.scaleFactor
                        Layout.topMargin: 40 * root.scaleFactor
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 60 * root.scaleFactor
                        Timer {
                            id: moveTimerPlayer1
                            interval: 50
                            running: false
                            repeat: true
                            onTriggered: {
                            if (leftButtonPlayer1.pressed) controller.moveLeftPaddle1();
                            else if (rightButtonPlayer1.pressed) controller.moveRightPaddle1();
                            }
                        }

                        Button {
                            anchors.top: parent.top
                            anchors.topMargin: 160 * root.scaleFactor
                            id: leftButtonPlayer1
                            //text: "Left"
                            onPressed: moveTimerPlayer1.start()
                            onReleased: moveTimerPlayer1.stop()
                            Layout.preferredWidth: 350 * root.scaleFactor
                            Layout.preferredHeight: 120 * root.scaleFactor

                            Image {
                                anchors.fill: parent
                                anchors.margins: 20 * root.scaleFactor
                                source: filepath + "/gamefiles/Zoccer/images/left-arrow.png"
                                fillMode: Image.PreserveAspectFit
                                smooth: true
                            }
                        }

                        Button {
                            anchors.top: parent.top
                            anchors.topMargin: 160 * scaleFactor
                            id: rightButtonPlayer1
                            //text: "Right"
                            onPressed: moveTimerPlayer1.start()
                            onReleased: moveTimerPlayer1.stop()
                            Layout.preferredWidth: 350 * root.scaleFactor
                            Layout.preferredHeight: 120 * root.scaleFactor

                            Image {
                                anchors.fill: parent
                                anchors.margins: 20 * root.scaleFactor
                                source: filepath + "/gamefiles/Zoccer/images/right-arrow.png"
                                fillMode: Image.PreserveAspectFit
                                smooth: true
                            }
                        }


                    }
                }
            }

            GameOverBase {
                id: gameOverBase
            }
        }

        // Home Bar Row
        HomeBarBase {
            id: homeBarBase
            Layout.verticalStretchFactor: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 1
        }
    }
}
