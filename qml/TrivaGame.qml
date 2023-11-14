import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: item1
    Rectangle {
        id: rectangle
        visible: true
        color: "#004c9d"
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            anchors.fill: parent
            layoutDirection: Qt.LeftToRight
            spacing: 1




            Label {
                id: lblTitle
                width: 2160
                height: 275
                color: "#000000"
                text: qsTr("Akron Trivia")
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true
                font.family: "Times New Roman"
                font.pointSize: 50
                Layout.preferredHeight: -1
                Layout.preferredWidth: -1
                Layout.fillHeight: true
                Layout.verticalStretchFactor: 1
            }
            Label {
                id: lblQuestionText
                width: 2152
                height: 498
                color: "#000000"
                text: "Question"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: -1
                Layout.preferredWidth: -1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                font.pointSize: 50
                font.family: "Times New Roman"
                scale: 1
                Layout.verticalStretchFactor: 3
            }

            GridLayout {
                id: gridLayout
                width: 2160
                height: 1109
                Layout.preferredHeight: -1
                Layout.preferredWidth: -1
                layoutDirection: Qt.LeftToRight
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                rows: 2
                columns: 2
                anchors.bottomMargin: 0
                Layout.verticalStretchFactor: 3

                Button {
                    id: btn1
                    width: 1040
                    height: 450
                    text: qsTr("Button")
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    icon.color: "#ff0000"
                    icon.height: 1000
                    icon.width: 1000
                    icon.source: "../projecticons/aroo1.png"
                    font.pointSize: 400
                    display: AbstractButton.IconOnly
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                }

                Button {
                    id: btn2
                    width: 1040
                    height: 450
                    text: qsTr("Button")
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    icon.color: "#0000ff"
                    icon.height: 1000
                    icon.width: 1000
                    icon.source: "../projecticons/aroo1.png"
                    display: AbstractButton.IconOnly
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                }

                Button {
                    id: btn3
                    width: 1040
                    height: 450
                    text: qsTr("Button")
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    icon.color: "#00ff00"
                    icon.height: 1000
                    icon.width: 1000
                    icon.source: "../projecticons/aroo1.png"
                    highlighted: false
                    display: AbstractButton.IconOnly
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                }

                Button {
                    id: btn4
                    width: 1040
                    height: 450
                    text: qsTr("Button")
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    icon.color: "#ffff00"
                    icon.height: 1000
                    icon.width: 1000
                    icon.source: "../projecticons/aroo1.png"
                    display: AbstractButton.IconOnly
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                }
            }
        }
    }

}
