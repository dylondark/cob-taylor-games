import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import Qt5Compat.GraphicalEffects
import QMLControllers
import QtQuick.VirtualKeyboard 2.15

Item {
    id: base
    anchors.fill: parent

    InputPanel {
        id:inputPanel
        z:99
        anchors.bottom: parent.bottom
        visible: true
        width: parent.width
        height: parent.height / 3
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 72 * root.scaleFactor

        Rectangle {
            id: menuImgRect
            color: "transparent"
            Layout.verticalStretchFactor: 6
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            anchors.margins: 72 * root.scaleFactor

            Image {
                id: menuImg
                source: "qrc:/menu/Logos-Buttons/trivia.png"
                width: parent.width
                height: parent.height
                fillMode: Image.PreserveAspectFit

                layer.enabled: true
                layer.effect: DropShadow {
                    horizontalOffset: 12 * root.scaleFactor
                    verticalOffset: 12 * root.scaleFactor
                    radius: 24.0 * root.scaleFactor
                    samples: (radius * 2) + 1
                    color: "#aa000000"
                    cached: true
                    transparentBorder: true
                }
            }
        }

        Item {
            id: nameItem
            Layout.verticalStretchFactor: 1
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent
                spacing: 10
                anchors.leftMargin: 600 * root.scaleFactor
                anchors.rightMargin: 600 * root.scaleFactor


                Text {
                    id:nameText
                    text: 'NAME:'
                    font.family: "1UP!" //Text font
                    font.bold: true
                    font.pointSize: 78 * root.scaleFactor
                    color: "black"
                    Layout.alignment: Qt.AlignVCenter // Vertically center align the text within its space
                }

                TextField {
                    id: playerName
                    maximumLength: 4
                    focus: true
                    Layout.fillWidth: true // Allow the text field to take up the remaining space
                    Layout.alignment: Qt.AlignVCenter // Vertically center align the text field
                    font.capitalization: Font.AllUppercase //make all characters look uppercase
                    Layout.preferredWidth: -1
                    onTextChanged: {
                        playerName.text = playerName.text.toUpperCase() //Actually make all characters uppercase
                    }
                    font.family: "1UP!"
                    font.bold: true
                    font.pointSize: nameText.font.pointSize
                }

            }

        }


        Rectangle {
            id: playRect
            color: "transparent"
            Layout.verticalStretchFactor: 6
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            anchors.margins: 72 * root.scaleFactor

            Button {
                id: playButton
                width: parent.width / 2
                height: parent.height / 6
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.height / 3
                font.pointSize: 72 * root.scaleFactor
                text: "PLAY"
                font.family: "1UP!"
                font.bold: true

                background: Rectangle {
                    color: Qt.rgba(1, 1, 1, 0.6)
                    radius: 72 * root.scaleFactor
                    border.color: "black"
                    border.width: 12 * root.scaleFactor
                }

                onClicked: {
                    base.visible = false;
                    gameBase.visible = true;
                    gameBase.questionOps();
                }
            }
        }
    }
}
