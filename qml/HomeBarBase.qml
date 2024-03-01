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
        anchors.leftMargin: 40 * root.scaleFactor
        anchors.rightMargin: 40 * root.scaleFactor

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
                font.family: "The Next Font"
                anchors.fill: parent
                horizontalAlignment: Label.AlignLeft
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
            font.family: "The Next Font"
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
            font.family: "The Next Font"
            text: "0"
            horizontalAlignment: Label.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
            verticalAlignment: Label.AlignVCenter
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
        }
    }
}
