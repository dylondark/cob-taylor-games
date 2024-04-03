import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    id: base

    property string logoSource // location of the image for the game logo
    property string conceptSource // location of the concept image

    Rectangle {
        Layout.verticalStretchFactor: 1
        Layout.preferredHeight: -1
        Layout.preferredWidth: -1
        Layout.fillHeight: true
        Layout.fillWidth: true

        Image {
            id: logo
            source: logoSource
            anchors.fill: parent
        }
    }

    Rectangle {
        Layout.verticalStretchFactor: 4
        Layout.preferredHeight: -1
        Layout.preferredWidth: -1
        Layout.fillHeight: true
        Layout.fillWidth: true

        Image {
            id: concept
            source: conceptSource
            anchors.fill: parent
        }
    }
}
