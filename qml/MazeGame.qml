/*
    MazeGame.qml

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
    //title: "Maze Game Layout"

    signal quit  // Signal to go to home screen or quit the game
    signal saveScore(int game, string username, int score)

    property real scaleFactor: height / 3840
    property int points: 0
    property string strName: "Maze"
    property string username: ""
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
                        MazeController {
                            id: gameRect
                            width: 1550 * root.scaleFactor
                            height: 3040 * root.scaleFactor
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.verticalStretchFactor: 4
                            x: (parent.width - width) / 2
                            y: (parent.height - height) / 1.5

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
