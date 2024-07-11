/*
    TetroosGame.qml

    Main QML file for the Tetroos game.
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import QMLControllers

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

    TetroosController {
        id: controller
    }

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

            MenuBase {
                id: menuBase
                imageSource: "qrc:/menu/menufiles/TetroosPreview.png"
            }

            Item {
                id: gameBase
                anchors.fill: parent
                visible: false

                function startGame() {
                    controller.startGame();
                }

                Connections {
                    target: controller

                    onUpdateView: {
                        if (controller.isGameOver())
                        {
                            // TODO: do game over actions
                        }

                        scoreTextLabel.text = controller.getScore();

                        // fill in hold and next pieces

                        // update board
                        for (var x = 0; x <= 10; x++)
                        {
                            for (var y = 0; y <= 20; y++)
                            {
                                controller.getTextureAt()
                            }
                        }
                    }
                }

                // Column for the data being laid out.
                ColumnLayout {
                    id: gameLayout
                    anchors.fill: parent
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
                                        border.color: "black"
                                        border.width: 1
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
                                        border.color: "black"
                                        border.width: 1
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
                                        border.color: "black"
                                        border.width: 1
                                    }
                                }

                                Label { // The label for the actual variable of the level.
                                    id: levelVar
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    background: Rectangle {
                                        color: "#ffffff"
                                        border.color: "black"
                                        border.width: 1
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

                        RowLayout {
                            spacing: 15

                            Rectangle {
                                id: holdRectangle
                                Layout.preferredWidth: 350 * scaleFactor
                                Layout.preferredHeight: 350 * scaleFactor
                                Layout.alignment: Qt.AlignTop
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
                                        border.color: "black"
                                        border.width: 1
                                    }
                                }
                            }

                            // Begin game rectangle
                            Grid {
                                id: gameGrid
                                columns: 10
                                rows: 20
                                spacing: 0
                                width: 700 * scaleFactor
                                height: 1400 * scaleFactor

                                Repeater {
                                    model: 200 // 10 columns by 20 rows

                                    Item {
                                        width: gameGrid.width / gameGrid.columns
                                        height: gameGrid.height / gameGrid.rows

                                        property int row: index / gameGrid.columns
                                        property int col: index % gameGrid.columns
                                        property bool occupied: false
                                        property string imagePath: "qrc:/game/gamefiles/Tetroos/empty_image.png"

                                        Rectangle {
                                            id: rect
                                            anchors.fill: parent
                                            color: "white"
                                            border.color: "black"
                                            border.width: 1

                                            Image {
                                                id: cellImage
                                                anchors.fill: parent
                                                source: imagePath
                                            }
                                        }
                                    }
                                }

                                function updateCell(row, col, imagePath, occupied) {
                                    let cellIndex = row * gameGrid.columns + col;
                                    if(cellIndex >= 0 && cellIndex < gameGrid.children.length) {
                                        let cell = gameGrid.children[cellIndex];
                                        cell.imagePath = imagePath;
                                        cell.occupied = occupied;
                                    }
                                }
                            }
                        }
                    }

                    Rectangle {
                        id: buttonRect
                        Layout.verticalStretchFactor: 2
                        Layout.preferredHeight: 1
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: "transparent"

                        RowLayout {
                            spacing: 30

                            Button {
                                id: holdBtn

                                Text {
                                    text: "HOLD"
                                    font.family: "Bodoni MT Black"
                                    font.bold: true
                                    font.pointSize: 20
                                }

                                background: Rectangle {
                                    color: "white"
                                    opacity: 70
                                    border.color: "black"
                                    radius: 10
                                    implicitWidth: 150
                                    implicitHeight: 100
                                }
                            }

                            Button {
                                id: slamBtn

                                Text {
                                    text: "SLAM"
                                    font.family: "Bodoni MT Black"
                                    font.bold: true
                                    font.pointSize: 20
                                }

                                background: Rectangle {
                                    color: "white"
                                    opacity: 70
                                    border.color: "black"
                                    radius: 10
                                    implicitWidth: 150
                                    implicitHeight: 100
                                }
                            }

                            Rectangle {
                                id: fourBtnsRect
                                Layout.fillWidth: true
                                Layout.fillHeight: true

                                Button {
                                    id: leftBtn

                                    Text {
                                        text: "Left"
                                        font.family: "Bodoni MT Black"
                                        font.bold: true
                                        font.pointSize: 20
                                    }

                                    background: Rectangle {
                                        color: "white"
                                        opacity: 70
                                        border.color: "black"
                                        radius: 10
                                        implicitWidth: 150
                                        implicitHeight: 100
                                    }
                                }

                                Button {
                                    id: rightBtn

                                    Text {
                                        text: "Right"
                                        font.family: "Bodoni MT Black"
                                        font.bold: true
                                        font.pointSize: 20
                                    }

                                    background: Rectangle {
                                        color: "white"
                                        opacity: 70
                                        border.color: "black"
                                        radius: 10
                                        implicitWidth: 150
                                        implicitHeight: 100
                                    }
                                }

                                Button {
                                    id: downBtn

                                    Text {
                                        text: "Down"
                                        font.family: "Bodoni MT Black"
                                        font.bold: true
                                        font.pointSize: 20
                                    }

                                    background: Rectangle {
                                        color: "white"
                                        opacity: 70
                                        border.color: "black"
                                        radius: 10
                                        implicitWidth: 150
                                        implicitHeight: 100
                                    }
                                }

                                Button {
                                    id: rotateBtn

                                    Text {
                                        text: "Rotate"
                                        font.family: "Bodoni MT Black"
                                        font.bold: true
                                        font.pointSize: 20
                                    }

                                    background: Rectangle {
                                        color: "white"
                                        opacity: 70
                                        border.color: "black"
                                        radius: 10
                                        implicitWidth: 150
                                        implicitHeight: 100
                                    }
                                }
                            }
                        }
                    }
                }
            }
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
