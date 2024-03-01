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


    /*Timer {
        id: gameOverTimer
        interval: 15000 // 15 seconds
        onTriggered: root.quit()
    }*/

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

    Item {
        Layout.preferredHeight: -1
        Layout.preferredWidth: -1
        Layout.fillHeight: true
        Layout.fillWidth: true

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 20

            Text {
                id: feedbackText
                anchors.fill: parent
                font.pointSize: 144 * root.scaleFacotr
                font.bold: true
                text: "This game was made by 5 people trying to make it better than it is.\n Let us know what you think!"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVTop
            }

            TextField {
                id: feedbackInput
                placeholderText: qsTr("Enter your feedback here...")
                Layout.preferredHeight: 40 // Adjust based on your UI needs
                Layout.preferredWidth: parent.width * 0.8 // Adjust width as needed, example uses 80% of parent width
                Layout.alignment: Qt.AlignHCenter
                Layout.margins: 20
            }

            Button {
                id: submitButton
                text: qsTr("Submit")
                Layout.preferredHeight: 40 // Adjust based on your UI needs
                Layout.preferredWidth: parent.width * 0.3 // Adjust width as needed, example uses 30% of parent width
                Layout.alignment: Qt.AlignHCenter
                Layout.margins: 20
                onClicked: {
                    // Add your logic here for what happens when the button is clicked, e.g., send feedback to a server
                    console.log("Feedback submitted:", feedbackInput.text)
                }
            }
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        //Layout.Alignment: Qt.AlignHCenter | Qt.AlignBottom
        visible: Qt.inputMethod.visible //only show when input method is active
        width: parent.width
        externalLanguageSwitchEnabled: true
    }
}
