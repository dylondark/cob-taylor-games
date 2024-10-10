import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Pong Game Layout"

    signal goHome  // Signal to go to home screen or quit the game

    // Define the background of the game
    Rectangle {
        id: gameArea
        anchors.fill: parent
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

        // Home Button at the bottom right corner
        Button {
            id: homeButton
            text: "Home"
            width: 80
            height: 40
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottomMargin: 20

            onClicked: {
                goHome();  // Emit the goHome signal
            }
        }
    }

    // Handle the goHome signal to either quit the game or return to the main menu
    onGoHome: {
        // Implement the logic to quit the game or go to the home screen
        Qt.quit();  // This will quit the application, but you can link it to a home screen.
    }
}
