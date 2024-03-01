import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import Qt5Compat.GraphicalEffects
import QtQuick.VirtualKeyboard 2.15

Item {

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
}
