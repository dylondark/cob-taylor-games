import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml

Rectangle {
    id: base
    color: "#fff7e9"

    property string labelText: "unset"

    ColumnLayout {
        anchors.fill: parent
        spacing: 10 * root.scaleFactor

        Label {
            id: holdLabel
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.verticalStretchFactor: 1
            text: base.labelText
            horizontalAlignment: Text.AlignHCenter
            font.family: textProperties.bodoniFont.family
            font.pointSize: textProperties.bodoniFont.pointSize
            font.bold: textProperties.bodoniFont.bold
            color: textProperties.textColor
            background: Rectangle {
                color: "#041e42"
            }
        }

        Rectangle {
            id: holdPieceRect
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.verticalStretchFactor: 4
            color: "#ffffff"
            border.color: "black"
            border.width: 1
        }
    }
}
