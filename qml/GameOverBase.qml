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
        interval: 30000 // 15 seconds
        repeat: true
        onTriggered: {
            if (feedbackBase.timerEval()) {
                root.quit()
            }
        }
    }

    // run this function to show the game over screen and automatically send quit signal
    function gameOverOps() {
        base.visible = true
        gameOverTimer.start()
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

    Feedback {
        id: feedbackBase
        Layout.preferredHeight: -1
        Layout.preferredWidth: -1
        Layout.fillHeight: true
        Layout.fillWidth: true
    }
}
