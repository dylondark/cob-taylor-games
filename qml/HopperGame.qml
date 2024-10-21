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
                z: 1
            }

            Item {
                id: gameBase
                anchors.fill: parent
                visible: false

                // Put the code for the scores boxes here
                Rectangle {
                    id: scoresRect
                    //anchors.top: parent
                }
                // Zippy Model
                Rectangle {
                    id: zippyModel
                    width: 150 * root.scaleFactor
                    height: 400 * root.scaleFactor
                    color: "#f19527"
                    x: (parent.width - width) / 4
                    y: floorRect.y - height // Starting position on the floor
                    z: 1

                    // Animation for Hopping
                    SequentialAnimation on y {
                        id: hopAnimation
                        running: false
                        loops: 1
                        PropertyAnimation { to: floorRect.y - (1200 * root.scaleFactor); duration: 500; easing.type: Easing.OutQuad } // Jump (reaches peak of height)
                        PropertyAnimation { to: floorRect.y - zippyModel.height; duration: 500; easing.type: Easing.InQuad } // Land
                    }
                    // Animation for "Sliding"
                    // Known bug: If you "Slide-Hop" AFTER "Hop-Slide", Zippy exits the bounds of the grass
                    SequentialAnimation on height {
                           id: slideAnimation
                           running: false
                           loops: 1
                           PropertyAnimation { to: 150 * root.scaleFactor; duration: 300; easing.type: Easing.OutQuad } // Duck down
                           PropertyAnimation { to: 400 * root.scaleFactor; duration: 300; easing.type: Easing.InQuad } // Return to original height
                       }
                }
                //Begin game rectangle
                Rectangle {
                    id: gameRect
                    width: 1750 * root.scaleFactor
                    height: 2800 * root.scaleFactor
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.verticalStretchFactor: 4
                    color: "#b5fffe"
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2
                    z: 0
                }
                // Floor Rectangle for Zippy to run on
                Rectangle {
                    id: floorRect
                    width: 1750 * root.scaleFactor
                    height: 600 * root.scaleFactor
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.verticalStretchFactor: 4
                    color: "#16bd10"
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 1.16
                    z: 0
                }

                ColumnLayout {
                    id: btnLayout
                    width: 400 * root.scaleFactor
                    height: 400 * root.scaleFactor
                    anchors.horizontalCenter: floorRect.horizontalCenter
                    anchors.top: floorRect.bottom
                    spacing: 10 * root.scaleFactor

                    Button {
                        id: hopBtn

                        background: Rectangle {
                            color: "white"
                            opacity: 0.7
                            border.color: "black"
                            radius: 100 * root.scaleFactor
                            width: parent.width
                            height: parent.height
                        }

                        contentItem: Text {
                                    text: "Hop!"
                                    font.pointSize: 70 * root.scaleFactor
                                    anchors.centerIn: parent
                                }

                        onClicked: {
                            if (!hopAnimation.running) {
                                hopAnimation.start(); // Start the hop animation
                            }
                        }
                    }

                    Button {
                        id: slideBtn
                        background: Rectangle {
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
                            width: parent.width
                            height: parent.height
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
