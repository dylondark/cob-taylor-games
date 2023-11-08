import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

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
                id: label1
                width: 2160
                height: 275
                color: "#000000"
                text: qsTr("Test 2")
                horizontalAlignment: Text.AlignHCenter
                font.family: "Times New Roman"
                font.pointSize: 200
                Layout.preferredHeight: 275
                Layout.preferredWidth: 2160
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillHeight: false
            }
            Label {
                id: label
                width: 2152
                height: 498
                color: "#000000"
                text: "Test"
                horizontalAlignment: Text.AlignHCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pointSize: 200
                font.family: "Times New Roman"
                scale: 1
            }

            GridLayout {
                id: gridLayout
                width: 2160
                height: 1109
                anchors.bottom: parent.bottom
                Layout.preferredHeight: 960
                Layout.preferredWidth: 2160
                layoutDirection: Qt.LeftToRight
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: false
                Layout.fillWidth: false
                rows: 2
                columns: 2
                anchors.bottomMargin: 0

                Button {
                    id: button1
                    width: 1040
                    height: 450
                    text: qsTr("Button")
                    icon.color: "#ff0000"
                    icon.height: 1000
                    icon.width: 1000
                    icon.source: "../projecticons/aroo1.png"
                    font.pointSize: 400
                    display: AbstractButton.IconOnly
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 450
                    Layout.preferredWidth: 1040
                }

                Button {
                    id: button2
                    width: 1040
                    height: 450
                    text: qsTr("Button")
                    icon.color: "#0000ff"
                    icon.height: 1000
                    icon.width: 1000
                    icon.source: "../projecticons/aroo1.png"
                    display: AbstractButton.IconOnly
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 450
                    Layout.preferredWidth: 1040
                }

                Button {
                    id: button3
                    width: 1040
                    height: 450
                    text: qsTr("Button")
                    icon.color: "#00ff00"
                    icon.height: 1000
                    icon.width: 1000
                    icon.source: "../projecticons/aroo1.png"
                    highlighted: false
                    display: AbstractButton.IconOnly
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 450
                    Layout.preferredWidth: 1040
                }

                Button {
                    id: button4
                    width: 1040
                    height: 450
                    text: qsTr("Button")
                    icon.color: "#ffff00"
                    icon.height: 1000
                    icon.width: 1000
                    icon.source: "../projecticons/aroo1.png"
                    display: AbstractButton.IconOnly
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 450
                    Layout.preferredWidth: 1040
                }
            }
        }
    }

}
