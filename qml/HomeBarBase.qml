import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import Qt5Compat.GraphicalEffects
import QMLControllers
import QtQuick.VirtualKeyboard 2.15

Rectangle {
    id: base
    color: "black"

    function updatePoints() {
        pointCounter.text = root.points
    }

    RowLayout {
        spacing: 140
        anchors.fill: parent

        Button {
            id: backButton
            text: "Back button"
            highlighted: bool
            onClicked: root.quit()
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
        }

        Label {
            id: userNameTxt
            color: "white"
            text: "Test"
            horizontalAlignment: Label.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            verticalAlignment: Label.AlignVCenter
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
        }

        Label {
            id: pointCounter
            color: "white"
            text: ""
            horizontalAlignment: Label.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
            verticalAlignment: Label.AlignVCenter
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
        }
    }
}
