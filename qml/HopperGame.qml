/*
    HopperGame.qml

    Main QML file for the Hopper game.
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
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

                ColumnLayout {
                    id: btnLayout
                    width: 400 * root.scaleFactor
                    height: 800 * root.scaleFactor

                    Button {
                        id: hopBtn
                        anchors.topMargin: 100 * root.scaleFactor
                        anchors.bottomMargin: 100 * root.scaleFactor
                        anchors.leftMargin: 100 * root.scaleFactor
                        anchors.rightMargin: 100 * root.scaleFactor

                        background: Rectangle {
                            color: "white"
                            opacity: 70
                            border.color: "black"
                            radius: 10
                            anchors.fill: parent
                        }
                    }

                    Button {
                        id: slideBtn
                        height: 100 * root.scaleFactor
                        Layout.fillWidth: true
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
