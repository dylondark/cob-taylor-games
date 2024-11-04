/*
    HopperGame.qml

    Main QML file for the Hopper game.
*/

import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts 1.15
import QtQml

// this game is in PREVIEW STATE
Item {
    id: root
    width: 2160
    height: 3840

    signal quit
    signal saveScore(int game, string username, int score)

    // will be emitted and picked up by mainwindow when the game wants to quit. must be present in every game!
    property real scaleFactor: height / 3840
    property int points: 0
    property string strName: "Hopper"
    property string username: ""
    property int gameEnum: 0 //Utilities number.


    ColumnLayout {
        id: baseLayout
        anchors.fill: parent
        spacing: 0

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
                imageSource: filepath + "/menufiles/Hopper.png"
            }

            Item { // This is the part of the code for all game events to be put in.
                id: gameBase
                anchors.fill: parent
                visible: false

                // The code for the scores boxes here
                Rectangle {
                    id: scoreBox
                    width: parent.width
                    height: 150 * root.scaleFactor
                    color: "#3f51b1"
                    anchors.left: parent.left
                    anchors.top: parent.top

                    // Shows score ran in meters in score box
                    Text {
                        id: scoreText
                        text: "Score: " + root.points + " meters"
                        font.pixelSize: 70 * root.scaleFactor
                        color: "white"
                        anchors.left: parent.left
                        anchors.leftMargin: 20 * root.scaleFactor
                        anchors.verticalCenter: parent.verticalCenter
                    }


                    // Displays the Timer measuring the time of each turn played
                    Text{
                        id: timeText
                        text: "Time: " + root.elapsedTime + "s"
                        font.pixelSize: 70 * root.scaleFactor
                        color: "white"
                        anchors.right: parent.right
                        anchors.rightMargin: 50 * root.scaleFactor
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                //Begin game rectangle
                Rectangle {
                    id: gameRect
                    width: 1750 * root.scaleFactor
                    height: 2800 * root.scaleFactor
                    anchors.centerIn: parent

                    Rectangle {
                        id: skyRect
                        width: 1750 * root.scaleFactor
                        height: 2800 * root.scaleFactor
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.verticalStretchFactor: 3
                        color: "#b5fffe"
                    }

                    // Floor Rectangle for Zippy to run on
                    Rectangle {
                        id: floorRect
                        width: 1750 * root.scaleFactor
                        height: 600 * root.scaleFactor
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.verticalStretchFactor: 1
                        anchors.bottom: parent.bottom
                        color: "#16bd10"
                    }

                    // Zippy Model
                    Image {
                        id: zippyModel
                        width: 850 * root.scaleFactor
                        height: 800 * root.scaleFactor
                        x: (parent.width - width) / 4
                        y: floorRect.y - height + 50 // Starting position on the floor

                        property bool isRunning: true

                        // Animation for zippy running that changes every 500 ticks
                        source: filepath + (isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png")
                        fillMode: Image.PreserveAspectFit
                        smooth: true

                        // Timer for Zippy Running
                        Timer {
                            id: runTimer
                            interval: 500
                            running: true
                            repeat: true
                            onTriggered: {
                                zippyModel.isRunning = !zippyModel.isRunning

                            }
                        }

                        // Animation for Hopping
                        SequentialAnimation on y {
                            id: hopAnimation
                            running: false
                            loops: 1

                            PropertyAction { target: zippyModel; property: "source"; value: filepath + "/gamefiles/Hopper/Jump.png" }
                            PropertyAction { target: runTimer; property: "running"; value: false }

                            PropertyAnimation { to: floorRect.y - (1200 * root.scaleFactor); duration: 500; easing.type: Easing.OutQuad } // Jump (reaches peak of height)
                            PropertyAnimation { to: floorRect.y - zippyModel.height + 50; duration: 500; easing.type: Easing.InQuad } // Land

                            PropertyAction { target: runTimer; property: "running"; value: true }
                            PropertyAction { target: zippyModel; property: "source"; value: filepath + (zippyModel.isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png") }
                        }

                        // Animation for "Sliding"
                        // Known bug: If you "Slide-Hop" AFTER "Hop-Slide", Zippy exits the bounds of the grass
                        SequentialAnimation on height {
                            id: slideAnimation
                            running: false
                            loops: 1

                            PropertyAction { target: zippyModel; property: "source"; value: filepath + "/gamefiles/Hopper/Slide.png" } // Set image to Jump.png at start
                            PropertyAction { target: runTimer; property: "running"; value: false } // Stop the Timer


                            PropertyAnimation { to: 400 * root.scaleFactor; duration: 300; easing.type: Easing.OutQuad } // Duck down
                            PropertyAnimation { to: 800 * root.scaleFactor; duration: 300; easing.type: Easing.InQuad } // Return to original height

                            PropertyAction { target: runTimer; property: "running"; value: true }
                            PropertyAction { target: zippyModel; property: "source"; value: filepath + (zippyModel.isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png") }
                        }
                    }
                }



                ColumnLayout {
                    id: btnLayout
                    width: 800 * root.scaleFactor
                    height: 400 * root.scaleFactor
                    anchors.horizontalCenter: gameRect.horizontalCenter
                    anchors.top: gameRect.bottom

                    Button {
                        id: hopBtn
                        implicitWidth: parent.width
                        implicitHeight: (btnLayout.height - btnLayout.spacing) / 2 // Dynamic height based on layout

                        background: Rectangle {
                            id: hopRect
                            color: "white"
                            opacity: 0.7
                            border.color: "black"
                            radius: 100 * root.scaleFactor
                            anchors.fill: parent
                        }

                        contentItem: Text {
                            text: "Hop!"
                            font.pointSize: 70 * root.scaleFactor
                            anchors.centerIn: parent.Center
                        }

                        onClicked: {
                            if (!hopAnimation.running) {
                                hopAnimation.start(); // Start the hop animation
                            }
                        }
                    }

                    Button {
                        id: slideBtn
                        implicitWidth: parent.width
                        implicitHeight: (btnLayout.height - btnLayout.spacing) / 2 // Dynamic height based on layout

                        background: Rectangle {
                            id:slideRect
                            color: "white"
                            opacity: 0.7
                            border.color: "black"
                            radius: 100 * root.scaleFactor
                            anchors.fill: parent
                        }

                        contentItem: Text {
                            text: "Slide!"
                            font.pointSize: 70 * root.scaleFactor
                            anchors.centerIn: parent
                        }

                        onClicked: {
                            if (!slideAnimation.running) {
                                slideAnimation.start(); // Start the slide/duck animation
                            }
                        }
                    }
                }
            }

            GameOverBase { // This calls a CPP file which saves the name and score to the leaderboard.
                id:gameOverBase
            }
        }

        HomeBarBase {
            id: homeBarBase
            Layout.verticalStretchFactor: 1
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
