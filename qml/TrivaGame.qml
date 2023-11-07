import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    id: item1
    Rectangle {
        id: rectangle
        visible: true
        color: "#001fff"
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            anchors.fill: parent

            GridLayout {
                id: gridLayout
                width: 2160
                height: 1109
                anchors.bottom: parent.bottom
                Layout.fillWidth: true
                rows: 2
                columns: 2
                anchors.bottomMargin: 8

                Button {
                    id: button
                    width: 779
                    height: 313
                    text: qsTr("Button")
                }

                Button {
                    id: button1
                    text: qsTr("Button")
                }

                Button {
                    id: button2
                    text: qsTr("Button")
                }

                Button {
                    id: button3
                    text: qsTr("Button")
                }
            }

            Label {
                id: label
                width: 2152
                height: 498
                text: "Test"
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 200
                font.family: "Times New Roman"
                scale: 1
            }
        }
    }

}
