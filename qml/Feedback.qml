import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import Qt5Compat.GraphicalEffects
import QtQuick.VirtualKeyboard 2.15
import QMLControllers

Item {

    FeedbackController {
        id: fbcontroller
    }

    // Background MouseArea, used so that you can drop the keyboard and
    //bring it back up when selecting textField.
    MouseArea {
        anchors.fill: parent
        onPressed: {
            // Remove focus from any focused item
            feedbackInput.focus = false
        }
        //Ensure it doesn't swallow clicks but still allows feedbackInput to be clickable
        //propagateComposedEvents: true
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.bottomMargin: width * (2 / 3) // leave room for the keyboard
        Layout.alignment: Qt.AlignHCenter
        spacing: 0

        Text {
            id: feedbackText
            anchors.fill: parent
            font.pointSize: 60 * root.scaleFactor
            font.bold: true
            text: "This project is still in heavy development.\nIf you have any feedback, please share it with us!"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVTop
        }

        TextField {
            id: feedbackInput
            placeholderText: qsTr("Enter your feedback here...")
            Layout.preferredHeight: 80 * root.scaleFactor
            Layout.preferredWidth: parent.width
                                   * 0.8 // Adjust width as needed, example uses 80% of parent width
            Layout.alignment: Qt.AlignHCenter
            Layout.margins: 40 * root.scaleFactor
            font.pointSize: 40 * root.scaleFactor
            onPressed: { focus = true; inputPanel.visible = true; }
            onFocusChanged: gameOverTimer.restart()
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    feedbackInput.forceActiveFocus()
                }
            }

            EnterKeyAction.enabled: feedbackInput.text.length > 0
                                    || feedbackInput.inputMethodComposing
            EnterKeyAction.label: "Submit"
            Keys.onReleased: {
                if (event.key === Qt.Key_Return) {
                    fbcontroller.submit(root.strName, feedbackInput.text,
                                        root.username)
                    root.quit()
                }
            }
        }

        Button {
            id: submitButton
            text: qsTr("Submit")
            font.pointSize: 40 * root.scaleFactor
            font.bold: true
            Layout.preferredHeight: 80 * root.scaleFactor
            Layout.preferredWidth: parent.width
                                   * 0.3 // Adjust width as needed, example uses 30% of parent width
            Layout.alignment: Qt.AlignHCenter
            Layout.margins: 40 * root.scaleFactor
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    fbcontroller.submit(root.strName, feedbackInput.text,
                                        root.username)
                    root.quit()
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


        /* this is not how positioning should be done ideally, but this feedback item wont be
          in the final product and i dont really know how else to position it correctly while
          keeping it in the same file as the rest of the feedback items */
        y: 534 * root.scaleFactor
    }

    // timer logic to use when including in gameoverbase
    // close if this function returns true
    property var lastText: "" // save the last text entered in the submit button to see if anything new has been typed
    function timerEval() {
        if (inputPanel.visible) {
            if (feedbackInput.text == lastText)
                // if input has not changed, put down the keyboard
                submitButton.focus
                        = true // changing focus to another object deselects the textinput

            lastText = feedbackInput.text
            return false
        } else {
            // if keyboard is not up then just close
            return true
        }
    }
}
