import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml 2.15

Item {
    id: root
    width: 2160
    height: 3840

    property string playerName: ""

    // Background
    Rectangle {
        id: background
        anchors.fill: parent
        color: "#001f3f" // Dark blue background
    }

    ColumnLayout {
        id: startScreenLayout
        anchors.centerIn: parent
        spacing: 40 * scaleFactor

        // Title
        Text {
            text: "Maze Game"
            font.pixelSize: 100 * scaleFactor
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Name Input Field
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 10 * scaleFactor

            Label {
                text: "Name:"
                font.pixelSize: 50 * scaleFactor
                color: "white"
                Layout.alignment: Qt.AlignLeft
            }

            TextField {
                id: nameInput
                width: 400 * scaleFactor
                height: 80 * scaleFactor
                font.pixelSize: 40 * scaleFactor
                placeholderText: "Enter your name"
                onTextChanged: root.playerName = text
            }
        }

        // Play Button
        Button {
            text: "Play"
            font.pixelSize: 50 * scaleFactor
            width: 300 * scaleFactor
            height: 100 * scaleFactor
            onClicked: {
                console.log("Play button clicked! Starting game for", root.playerName)
                // Logic to transition to the game screen
            }
            background: Rectangle {
                radius: 20 * scaleFactor
                color: "#00cc66"
                border.color: "#008040"
                border.width: 3
            }
        }
    }
}
