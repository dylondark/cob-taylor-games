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

    Item { // Since layouts can only inherit text properties, I'm defining them here for the text in the score boxes.
        id: textProperties
        property alias bodoniFont: bodoniText.font
        property color textColor: "#fff7e9"

        Text {
            id: bodoniText
            font.family: "Bodoni MT Heavy Italic"
            font.bold: true
            font.pointSize: 60 * scaleFactor
        }
    }

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

            // Column for the data being laid out.
            ColumnLayout {
            anchors.fill: background
            spacing: 0

                // The screen-width grid for data at the top.
                RowLayout {
                    id: dataRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: 1
                    Layout.verticalStretchFactor: 1
                    Layout.fillHeight: true
                    spacing: 0

                    Rectangle {
                        id: linesRect
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                        color: "#fff7e9"

                        ColumnLayout {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignHCenter
                            anchors.centerIn: parent
                            spacing: 10 * scaleFactor

                                Label {
                                    id: linesTextLabel
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    text: "L i n e s"
                                    font.family: textProperties.bodoniFont.family
                                    font.pointSize: textProperties.bodoniFont.pointSize
                                    font.bold: textProperties.bodoniFont.bold
                                    color: textProperties.textColor
                                    background: Rectangle {
                                        color: "#041e42"
                                    }
                                }

                                Label { // The label for the actual variable of lines.
                                    id: linesVar
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    background: Rectangle {
                                        color: "#ffffff"
                                    }
                                }
                        }
                    } // LinesRect bracket

                    Rectangle {
                        id: scoreRect
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.preferredHeight: 1
                        color: "#fff7e9"

                        ColumnLayout {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignHCenter
                            anchors.centerIn: parent
                            spacing: 10 * scaleFactor

                            Label {
                                id: scoreTextLabel
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: "S c o r e"
                                font.family: textProperties.bodoniFont.family
                                font.pointSize: textProperties.bodoniFont.pointSize
                                font.bold: textProperties.bodoniFont.bold
                                color: textProperties.textColor
                                background: Rectangle {
                                    color: "#041e42"
                                }
                            }

                            Label { // The label for the actual variable of the score.
                                id: scoreVar
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                background: Rectangle {
                                    color: "#ffffff"
                                }
                            }
                        }
                    } // scoreRect bracket

                    Rectangle {
                        id: levelRect
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.preferredHeight: 1
                        color: "#fff7e9"

                        ColumnLayout {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignHCenter
                            anchors.centerIn: parent
                            spacing: 10 * scaleFactor

                            Label {
                                id: levelTextLabel
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: "L e v e l"
                                font.family: textProperties.bodoniFont.family
                                font.pointSize: textProperties.bodoniFont.pointSize
                                font.bold: textProperties.bodoniFont.bold
                                color: textProperties.textColor
                                background: Rectangle {
                                    color: "#041e42"
                                }
                            }

                            Label { // The label for the actual variable of the level.
                                id: levelVar
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                background: Rectangle {
                                    color: "#ffffff"
                                }
                            }
                        }
                    } // levelRect bracket
                } // dataRow RowLayout bracket.


                // TODO: Hold rectangle next to game rectangle next to "next" rectangle
                Rectangle {
                    Layout.verticalStretchFactor: 5
                    Layout.preferredHeight: 1
                    Layout.fillHeight: true
                    color: "#ffffff"
                /*
                    Row {

                        Rectangle {
                            id: holdRectangle
                            width: 100
                            height: 100
                            Layout.alignment: Qt.AlignLeft

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
                    }*/
                }
            } // ColumnLayout bracket
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
