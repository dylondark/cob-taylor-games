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
            highlighted: false
            onClicked: root.quit()
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1

            Text {
                text: "< Back"
                color: "white"
                font.pointSize: 48 * root.scaleFactor
                anchors.fill: parent
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
            }

            background: Rectangle {
                color: "transparent"
                anchors.fill: parent
            }
        }

        Label {

            id: userNameTxt
            color: "white"
            text: "Test"
            font.pointSize: 48 * root.scaleFactor
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
            font.pointSize: 48 * root.scaleFactor
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
