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

    ColumnLayout{
        id: baseLayout
        anchors.fill: parent
        spacing: 0

        // Define the background of the game
        Rectangle {
            id: gameArea
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.verticalStretchFactor: 6
            Layout.minimumHeight: 1
            //anchors.fill: parent
            color: "#4CAF50"  // Green background to simulate a field

            // Score and Time display at the top
            RowLayout {
                id: topBar
                anchors.top: parent.top
                width: parent.width
                height: 50
                spacing: 20



                // Score Section
                Rectangle {
                    id: scoreBox
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#D2B48C"  // Light brown background for the score
                    border.color: "black"
                    Text {
                        anchors.centerIn: parent
                        text: "Score: 0"
                        font.pixelSize: 20
                        color: "navy"
                    }
                }

                // Time Section
                Rectangle {
                    id: timeBox
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#D2B48C"  // Light brown background for the time
                    border.color: "black"
                    Text {
                        anchors.centerIn: parent
                        text: "Time: 0"
                        font.pixelSize: 20
                        color: "navy"
                    }
                }
            }

            // AI-controlled paddle at the top
            Rectangle {
                id: aiPaddle
                width: 100
                height: 20
                color: "blue"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 60
            }

            // Player-controlled paddle at the bottom
            Rectangle {
                id: playerPaddle
                width: 100
                height: 20
                color: "red"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20

                // Functions to move the paddle
                function moveLeft() {
                    playerPaddle.x = Math.max(0, playerPaddle.x - 40 * scaleFactor)
                }

                function moveRight() {
                    playerPaddle.x = Math.min(gameArea.width - playerPaddle.width, playerPaddle.x + 40 * scaleFactor)
                }
            }

            // Ball (represented by the dog)
            // Image {
            //     id: ball
            //     source: "file:///Users/neeleshkatkukojwala/Desktop/QT_COB/cob-taylor-games/build/Qt_6_7_2_for_macOS-Debug/gamefiles/Zoccer/zippy_icon.png"
            //     width: 30
            //     height: 30
            //     anchors.verticalCenter: playerPaddle.verticalCenter
            //     anchors.horizontalCenter: playerPaddle.horizontalCenter
            // }

            // Ball (represented as a white circle)
            Rectangle {
                id: ball
                width: 30
                height: 30
                color: "white"
                radius: 15  // Half of width and height to make it a circle
                anchors.verticalCenter: playerPaddle.verticalCenter
                anchors.horizontalCenter: playerPaddle.horizontalCenter
            }
        }
        // Control buttons to move the player paddle
    RowLayout {
        id: controlButtons
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20

        Button {
            id: leftButton
            text: "<"
            Layout.preferredWidth: 200
            Layout.preferredHeight: 80

            onPressed: playerPaddle.moveLeft()

            background: Rectangle {
                color: "black"
                opacity: 0.7
                border.color: "black"
                radius: 10
            }
        }

        Button {
            id: rightButton
            text: ">"
            Layout.preferredWidth: 200
            Layout.preferredHeight: 80

            onPressed: playerPaddle.moveRight()

            background: Rectangle {
                color: "black"
                opacity: 0.7
                border.color: "black"
                radius: 10
            }
        }
    }


        HomeBarBase {
            id: homeBarBase
            Layout.verticalStretchFactor: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 1

            // Home Button
            Button {
                id: homeButton
                text: "Home"
                Layout.preferredWidth: 80
                Layout.preferredHeight: 40
                onClicked: {
                    root.quit();  // Emit the quit signal to navigate back home
                }
                background: Rectangle {
                    color: "white"
                    opacity: 0.7
                    border.color: "black"
                    radius: 10
                }
            }
        }
    } // Column Layout
}
