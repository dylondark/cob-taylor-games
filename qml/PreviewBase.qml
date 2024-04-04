import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    id: base

    property string logoSource // location of the image for the game logo
    property string conceptSource // location of the concept image

    Rectangle {
        Layout.verticalStretchFactor: 1
        Layout.preferredHeight: 1
        Layout.preferredWidth: -1
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: "transparent"

        Image {
            id: logo
            source: logoSource
            anchors.fill: parent
            anchors.margins: 80 * root.scaleFactor
            fillMode: Image.PreserveAspectFit
        }
    }

    Rectangle {
        Layout.verticalStretchFactor: 2
        Layout.preferredHeight: 1
        Layout.preferredWidth: -1
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: "transparent"

        Image {
            id: concept
            source: conceptSource
            anchors.fill: parent
            anchors.margins: 80 * root.scaleFactor
            fillMode: Image.PreserveAspectFit
        }
    }
}
