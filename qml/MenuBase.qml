/*
    MenuBase.qml

    The file for the screen for name inputs, while displaying the game card/img.
*/

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

    property var imageSource

    // Background MouseArea, used so that you can drop the keyboard and
    // bring it back up when selecting textField.
    MouseArea {
        anchors.fill: parent
        onPressed: {
            // Remove focus from any focused item
            playerName.focus = false
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        anchors.bottom: parent.bottom
        visible: Qt.inputMethod.visible //only show when input method is active
        width: parent.width
        externalLanguageSwitchEnabled: true
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
                source: imageSource
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
                    id: nameText
                    text: 'NAME:'
                    font.family: "1UP!" // Text font
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
                    font.family: "1UP!"
                    font.bold: true
                    font.pointSize: nameText.font.pointSize
                    color: "black"
                    Layout.preferredWidth: -1
                    onTextChanged: {
                        playerName.text = playerName.text.toUpperCase() // Actually make all characters uppercase
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            playerName.forceActiveFocus()
                        }
                    }

                    background: Rectangle {
                        color: "white" // Default background color
                        radius: 4
                    }

                    // Define the color animation for the TextField
                    ColorAnimation {
                        id: backgroundAnimation
                        running: false // Not running initially
                        target: playerName.background
                        property: "color"
                        from: "red"
                        to: "white"
                        duration: 500 // 0.5 seconds duration
                    }

                    // Function to trigger the background color animation
                    function triggerErrorAnimation() {
                        backgroundAnimation.from = "red"; // Ensure it starts from red
                        backgroundAnimation.start(); // Start the animation
                    }
                    EnterKeyAction.label: "Play"
                    Keys.onReleased: {
                        if (event.key === Qt.Key_Return) {
                            if (playerName.text.trim().length === 0|| profanityChecker.check(playerName.text.trim()) === false) {
                                playerName.triggerErrorAnimation() // Trigger the animation if the TextField is empty
                            } else {
                                // save username
                                root.username = playerName.text.trim()
                                homeBarBase.updateUsername()

                                // Proceed with the game logic
                                base.visible = false
                                gameBase.visible = true
                                gameBase.startGame()
                            }
                        }
                    }
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

                contentItem: Text {
                    text: "PLAY"
                    color: "black"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 72 * root.scaleFactor
                    font.family: "1UP!"
                    font.bold: true
                }

                background: Rectangle {
                    color: Qt.rgba(1, 1, 1, 0.6)
                    radius: 72 * root.scaleFactor
                    border.color: "black"
                    border.width: 12 * root.scaleFactor
                }

                onPressed: {
                    if (playerName.text.trim().length === 0 || profanityChecker.check(playerName.text.trim()) === false) {
                        playerName.triggerErrorAnimation() // Trigger the animation if the TextField is empty
                    } else {
                        // save username
                        root.username = playerName.text.trim()
                        homeBarBase.updateUsername()

                        // Proceed with the game logic
                        base.visible = false
                        gameBase.visible = true
                        gameBase.startGame()

                    }
                }
            }
        }
    }

    ProfanityChecker {
        id: profanityChecker
    }
}
