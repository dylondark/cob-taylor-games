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
    property int gameEnum: 2

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
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.verticalStretchFactor: 6
            Layout.minimumHeight: 1

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
                            gameBase.visible = false;
                            gameOverBase.gameOverOps();
                        }

                        root.points = controller.getScore();
                        homeBarBase.updatePoints();

                        linesVar.text = controller.getLinesCleared();
                        levelVar.text = controller.getLevel();

                        // fill in hold and next pieces
                        holdView.setPiece(controller.getHoldPiece());
                        nextView.setPiece(controller.getNextPiece());

                    }
                }

                // The screen-width grid for data at the top.
                RowLayout {
                    id: dataRow
                    anchors.top: parent.top
                    width: parent.width
                    height: parent.height / 10
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
                                color: "black"
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
                                color: "black"
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
                    anchors.top: dataRow.bottom
                    width: parent.width
                    height: parent.height / 1.3
                    color: "transparent"

                    TetroosPieceView {
                        id: holdView
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: controller.left
                        height: width
                        labelText: "Hold"
                        fontFamily: textProperties.bodoniFont.family
                        fontPointSize: textProperties.bodoniFont.pointSize
                        fontBold: textProperties.bodoniFont.bold
                        fontColor: textProperties.textColor
                    }

                    // Begin game rectangle
                    TetroosController {
                        id: controller
                        anchors.top: parent.top
                        anchors.left: holdRectangle.right
                        anchors.centerIn: parent
                        height: parent.height
                        width: height / 2
                        smooth: false
                    }

                    TetroosPieceView {
                        id: nextView
                        anchors.top: parent.top
                        anchors.left: controller.right
                        anchors.right: parent.right
                        height: width
                        labelText: "Next"
                        fontFamily: textProperties.bodoniFont.family
                        fontPointSize: textProperties.bodoniFont.pointSize
                        fontBold: textProperties.bodoniFont.bold
                        fontColor: textProperties.textColor
                    }
                }

                RowLayout {
                    id: buttonRowLayout
                    anchors.top: midRect.bottom
                    anchors.bottom: parent.bottom
                    width: parent.width

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.horizontalStretchFactor: 2
                        Layout.preferredWidth: 1

                        Button {
                            id: holdBtn
                            anchors.fill: parent
                            anchors.topMargin: 100 * root.scaleFactor
                            anchors.bottomMargin: 100 * root.scaleFactor
                            anchors.leftMargin: 100 * root.scaleFactor
                            anchors.rightMargin: 100 * root.scaleFactor

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

                                anchors.fill: parent
                            }
                            onPressed:controller.holdAction()
                        }
                    }


                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.horizontalStretchFactor: 2
                        Layout.preferredWidth: 1

                        Button {
                            id: slamBtn

                            anchors.fill: parent
                            anchors.topMargin: 100 * root.scaleFactor
                            anchors.bottomMargin: 100 * root.scaleFactor
                            anchors.leftMargin: 100 * root.scaleFactor
                            anchors.rightMargin: 100 * root.scaleFactor

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
                                anchors.fill: parent
                            }
                            onPressed:controller.slamAction()
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.horizontalStretchFactor: 3
                        Layout.preferredWidth: 1

                        GridLayout {
                            columns: 3
                            rowSpacing: 20
                            columnSpacing: 20
                            anchors.fill: parent
                            anchors.topMargin: 20 * root.scaleFactor
                            anchors.bottomMargin: 20 * root.scaleFactor
                            anchors.leftMargin: 100 * root.scaleFactor
                            anchors.rightMargin: 100 * root.scaleFactor

                            Button {
                                id: leftBtn
                                Layout.row: 1
                                Layout.column: 0
                                Layout.alignment: Qt.AlignCenter
                                Layout.fillHeight: true
                                Layout.fillWidth: true

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
                                    anchors.fill: parent
                                }
                                onPressed: controller.leftAction()
                            }

                            Button {
                                id: rightBtn
                                Layout.row: 1
                                Layout.column: 2
                                Layout.fillHeight: true
                                Layout.fillWidth: true

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
                                    anchors.fill: parent

                                }
                                onPressed:controller.rightAction()
                            }

                            Button {
                                id: downBtn
                                Layout.row: 1
                                Layout.column: 1
                                Layout.fillHeight: true
                                Layout.fillWidth: true

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
                                    anchors.fill: parent
                                }
                                onPressed:controller.downAction()
                            }

                            Button {
                                id: rotateBtn
                                Layout.row: 0
                                Layout.column: 1
                                Layout.fillHeight: true
                                Layout.fillWidth: true

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
                                    anchors.fill: parent
                                }
                                onPressed:controller.rotateAction()
                            }
                        }
                    }
                }
            }

            Keys.onPressed: {
                switch (event.key) {
                case Qt.Key_Left:
                    controller.leftAction();
                    break;
                case Qt.Key_Right:
                    controller.rightAction();
                    break;
                case Qt.Key_Down:
                    controller.downAction();
                    break;
                case Qt.Key_Up:
                    controller.rotateAction();
                    break;
                case Qt.Key_X:
                    controller.slamAction();
                    break;
                case Qt.Key_C:
                    controller.holdAction();
                    break;
                default:
                    break;
                }
            }

            GameOverBase {
                id: gameOverBase
            }
        } // Gradient background rectangle.

        HomeBarBase {
            id: homeBarBase
            Layout.verticalStretchFactor: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 1
        }
    } // columnLayout for whole screen
}
