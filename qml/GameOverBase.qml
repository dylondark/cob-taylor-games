/*
    GameOverBase.qml

    Contains the game over screen to be shown at the end of each game.
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import Qt5Compat.GraphicalEffects
import QtQuick.VirtualKeyboard 2.15

ColumnLayout {
    id: base
    anchors.fill: parent
    visible: false
    anchors.centerIn: parent

    Timer {
        id: gameOverTimer
        interval: 15000 // 15 seconds
        repeat: true
        onTriggered: {
                root.quit()
        }
    }

    /*
        Shows the game over screen and automatically sends quit signal
    */
    function gameOverOps() {
        base.visible = true;
        gameOverTimer.start();
        root.saveScore(root.gameEnum, root.username, root.points);
        // TODO: tell user if they got a score on the leaderboard
    }

    Item {
        Layout.preferredHeight: -1
        Layout.preferredWidth: -1
        Layout.fillHeight: true
        Layout.fillWidth: true

        Text {
            id: gameOverText
            anchors.fill: parent
            font.pointSize: 144 * root.scaleFactor
            font.bold: true
            text: "Game Over!\nThanks for playing!"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignBottom
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            layer.enabled: true
            layer.effect: DropShadow {
                horizontalOffset: 8 * root.scaleFactor
                verticalOffset: 8 * root.scaleFactor
                radius: 24.0 * root.scaleFactor
                samples: (radius * 2) + 1
                color: "#aa000000"
                cached: false
                transparentBorder: true
            }
        }
    }

    Item {
        Layout.preferredHeight: -1
        Layout.preferredWidth: -1
        Layout.fillHeight: true
        Layout.fillWidth: true

        Text {
            id: gameOverScoreText
            anchors.fill: parent
            font.pointSize: 72 * root.scaleFactor
            font.bold: true
            text: "Your score: " + root.points
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            layer.enabled: true
            layer.effect: DropShadow {
                horizontalOffset: 4 * root.scaleFactor
                verticalOffset: 4 * root.scaleFactor
                radius: 12.0 * root.scaleFactor
                samples: (radius * 2) + 1
                color: "#aa000000"
                cached: false
                transparentBorder: true
            }
        }
    }

    Item {
        Layout.preferredHeight: -1
        Layout.preferredWidth: -1
        Layout.fillHeight: true
        Layout.fillWidth: true

        Text {
            id: gameOverQuestions
            anchors.fill: parent
            font.pointSize: 72 * root.scaleFactor
            font.bold: true
            text: gameBase.questionsCorrect + "/" + gameBase.maxQuestions + " questions correct!"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            visible: root.gameEnum === 0 || root.gameEnum === 1

            layer.enabled: true
            layer.effect: DropShadow {
                horizontalOffset: 4 * root.scaleFactor
                verticalOffset: 4 * root.scaleFactor
                radius: 12.0 * root.scaleFactor
                samples: (radius * 2) + 1
                color: "#aa000000"
                cached: false
                transparentBorder: true
            }
        }
    }
}
