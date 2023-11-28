import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: item1
    width: 2160
    height: 3840
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
                color: "#000000"
                text: qsTr("question")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.styleName: "Bold"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true
                font.pointSize: 72
                Layout.preferredHeight: -1
                Layout.preferredWidth: -1
                Layout.fillHeight: true
                Layout.verticalStretchFactor: 1
                scale: Math.min(item1.width / 2160, item1.height / 3840)
            }

            Image {
                id: image
                width: 50
                height: 50
                source: "qrc:/background/projecticons/controller3.png"
                fillMode: Image.PreserveAspectFit
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.verticalStretchFactor: 1
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
                Layout.verticalStretchFactor: 1

                Button {
                    id: btn1
                    width: 1040
                    height: 450
                    Text  {
                        id: btn1txt
                        text: "answer1"
                        anchors.centerIn: parent
                        font.pointSize: 18
                        scale: Math.min(btn1.width / width / 5, btn1.height / height / 5)
                    }

                    flat: false
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    display: AbstractButton.TextBesideIcon
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                }

                Button {
                    id: btn2
                    width: 1040
                    height: 450
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Text  {
                        id: btn2txt
                        text: "answer2"
                        anchors.centerIn: parent
                        font.pointSize: 18
                        scale: Math.min(btn2.width / width / 5, btn2.height / height / 5)
                    }
                    display: AbstractButton.TextBesideIcon
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                }

                Button {
                    id: btn3
                    width: 1040
                    height: 450
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Text  {
                        id: btn3txt
                        text: "answer3"
                        anchors.centerIn: parent
                        font.pointSize: 18
                        scale: Math.min(btn3.width / width / 5, btn3.height / height / 5)
                    }
                    display: AbstractButton.TextBesideIcon
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                }

                Button {
                    id: btn4
                    width: 1040
                    height: 450
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Text  {
                        id: btn4txt
                        text: "answer4"
                        anchors.centerIn: parent
                        font.pointSize: 18
                        scale: Math.min(btn4.width / width / 5, btn4.height / height / 5)
                    }
                    display: AbstractButton.TextBesideIcon
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                }
            }

        }
    }

}
