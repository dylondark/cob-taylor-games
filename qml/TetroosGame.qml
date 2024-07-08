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
                spacing: 10

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
                                text: " L i n e s "
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
                                text: " S c o r e "
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
                                text: " L e v e l "
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
                    id: midRect
                    Layout.verticalStretchFactor: 5
                    Layout.preferredHeight: 1
                    Layout.fillHeight: true
                    color: "transparent"

                    Rectangle {
                        id: holdRectangle
                        width: 400 * scaleFactor
                        height: 400 * scaleFactor
                        Layout.alignment: Qt.AlignLeft
                        color: "#fff7e9"

                        ColumnLayout {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignHCenter
                            anchors.centerIn: parent
                            spacing: 10 * scaleFactor

                            Label {
                                id: holdLabel
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Layout.verticalStretchFactor: 1
                                text: " Hold "
                                font.family: textProperties.bodoniFont.family
                                font.pointSize: textProperties.bodoniFont.pointSize
                                font.bold: textProperties.bodoniFont.bold
                                color: textProperties.textColor
                                background: Rectangle {
                                    color: "#041e42"
                                }
                            }

                            Rectangle {
                                id: holdPieceRect
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Layout.verticalStretchFactor: 4
                                Layout.preferredHeight: 200 * scaleFactor
                                Layout.preferredWidth: 200 * scaleFactor
                                color: "#ffffff"
                            }
                        }
                    }

                    // Begin game rectangle
                    Grid {
                        id: gameGrid
                        columns: 10
                        rows: 20
                        spacing: 0
                        width: 1500 * scaleFactor
                        height: 2500 * scaleFactor


                        //Define the cell component
                        Component {
                            id: cellComponent

                            Item {
                                width: gameGrid.width / gameGrid.columns
                                height: gameGrid.height / gameGrid.rows
                                property string color: "white"
                                property bool occupied: false

                                Rectangle {
                                    id: rect
                                    anchors.fill: parent
                                    color: "white"
                                    border.color: "black"
                                    border.width: 1
                                    visible: occupied
                                }

                            }
                        }

                        function updateCell(row, col, color, occupied) {
                                    let cellIndex = row * gameGrid.columns + col;
                                    if (cellIndex >= 0 && cellIndex < gameGrid.children.length) {
                                        let cell = gameGrid.children[cellIndex];
                                        cell.color = color;
                                        cell.occupied = occupied;
                                    }
                                }
                    }

                    //Dynamically create grid cells.
                    Component.onCompleted: {
                        for (let row = 0; row < gameGrid.rows; row++) {
                            for (let col = 0; col < gameGrid.columns; col++) {
                                let cell = cellComponent.createObject (gameGrid);
                                cell.color = "white";
                                cell.occupied = false;
                            }
                        }
                    }


                    // Example usage to update a cell's color and occupied status
                        Timer {
                            interval: 10
                            running: true
                            repeat: true
                            onTriggered: {
                                let row = Math.floor(Math.random() * gameGrid.rows);
                                let col = Math.floor(Math.random() * gameGrid.columns);
                                gameGrid.updateCell(row, col, "red", true);
                            }
                        }

                    // End game grid
                }
            } // LineScoreLevel ColumnLayout bracket


        } // Gradient background rectangle.

        HomeBarBase {
            id: homeBarBase
            Layout.verticalStretchFactor: 1
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    } // columnLayout for whole screen
}
