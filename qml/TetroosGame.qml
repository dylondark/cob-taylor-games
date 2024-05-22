/*
    TetroosGame.qml

    Main QML file for the Tetroos game.
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

    property real scaleFactor: height / 3840
    property int points: 0
    property string strName: "Tetroos"
    property string username: ""
    property int gameEnum: 0

    ColumnLayout {
        id: baseLayout
        anchors.fill: parent
        spacing: 0

        // The gradient background rectangle.
        Rectangle {
            id: background
            Layout.preferredHeight: -1
            Layout.preferredWidth: -1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.verticalStretchFactor: 6

            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "#3f51b1"
                }
                GradientStop {
                    position: 1.0
                    color: "#cc6b8e"
                }
            }

            // The screen-width rectangle for data at the top.
            Rectangle {
                id: dataRect
                width: background.width
                height: background.height / 8
                color: "#FFF7E9"
                anchors.top: parent.top

                RowLayout {
                    //anchors.centerIn: parent
                    spacing: 10

                    // The rectangle for # of lines cleared.
                    Rectangle {
                        id: linesRect
                        width: dataRect.width / 3 - 10
                        height: dataRect.height - 20

                        Column {
                            spacing: 10

                            Rectangle {
                                id: linesTextRect
                                width: linesRect.width
                                height: linesRect.height / 2 - 5
                                color: "#041E42"

                                Text {
                                    id: linesText
                                    text: "L i n e s"
                                    font.family: "Bodoni MT Black"
                                    font.italic: true
                                    verticalAlignment: Text.AlignVCenter
                                    style: Text.Outline
                                    horizontalAlignment: Text.AlignHCenter
                                    font.pointSize: 55
                                    color: "#FFF7E9"
                                    anchors.centerIn: parent
                                }
                            }

                            // This is the part with the actual number of lines cleared, it's a stub.
                            Rectangle {
                                id: linesVar
                                width: levelRect.width
                                height: levelRect.height / 2 - 5
                                color: "#041E42"
                            }
                        }
                    }

                    // The rectangle for the score.
                    Rectangle {
                        id: scoreRect
                        width: dataRect.width / 3 - 10
                        height: dataRect.height  - 20

                        Column {
                            spacing: 10

                            Rectangle {
                                id: scoreTextRect
                                width: scoreRect.width
                                height: scoreRect.height / 2 - 5
                                color: "#041E42"
                                Text {
                                    id: scoreText
                                    text: "S c o r e"
                                    font.family: "Bodoni MT Black"
                                    font.italic: true
                                    verticalAlignment: Text.AlignVCenter
                                    style: Text.Outline
                                    horizontalAlignment: Text.AlignHCenter
                                    font.pointSize: 55
                                    color: "#FFF7E9"
                                    anchors.centerIn: parent
                                }
                            }

                            // This is the part with the actual data for the score, this is a stub.
                            Rectangle {
                                id: scoreVar
                                width: scoreRect.width
                                height: scoreRect.height / 2 - 5
                                color: "#041E42"
                            }
                        }
                    }

                    // The rectangle for the level.
                    Rectangle {
                        id: levelRect
                        width: dataRect.width / 3 - 10
                        height: dataRect.height - 20

                        Column {
                            spacing: 10

                            Rectangle {
                                id:levelTextRect
                                width: levelRect.width - 10
                                height: levelRect.height / 2 - 5
                                color: "#041E42"
                                Text {
                                    id: levelText
                                    text: "L e v e l"
                                    font.family: "Bodoni MT Black"
                                    font.italic: true
                                    verticalAlignment: Text.AlignVCenter
                                    style: Text.Outline
                                    horizontalAlignment: Text.AlignHCenter
                                    font.pointSize: 55
                                    color: "#FFF7E9"
                                    anchors.centerIn: parent
                                }
                            }

                            // This is the part with the actual data for the levels, it's a stub.
                            Rectangle {
                                id: levelVar
                                width: levelRect.width - 10
                                height: levelRect.height / 2 - 5
                                color: "#041E42"
                            }
                        }
                    }
                }
            }
            /*
            // TODO: Hold rectangle next to game rectangle next to "next" rectangle
            Row {
                Rectangle {
                    id: holdRectangle
                    width: 100
                    height: 100

                    Column {

                        Rectangle {
                            id: holdRect
                            color: "#041E42"

                            Text {
                            text: "HOLD"
                            font.bold: true
                            font.pointSize: 25
                            horizontalAlignment: Text.AlignHCenter
                            }
                        }

                        Rectangle {
                            id: holdPieceRect
                            color: "#FFF7E9"
                        }
                    }
                }
            }
        }
*/
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
