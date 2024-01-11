import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import QMLControllers

Item {
    id: root
    width: 2160
    height: 3840

    TriviaController {
    }


    Rectangle {
        id: gameBase
        visible: true
        color: "#004c9d"
        anchors.fill: parent

        ColumnLayout {
            id: gameLayout
            anchors.fill: parent
            layoutDirection: Qt.LeftToRight
            spacing: 1

            Label {
                id: questionLabel
                Layout.preferredHeight: -1
                Layout.preferredWidth: -1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.verticalStretchFactor: 1
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "#000000"
                text: qsTr("question")
                font.styleName: "Bold"
                font.pointSize: 72
                scale: Math.min(gameBase.width / 2160, gameBase.height / 3840)
            }

            Rectangle {
                id: imageRect
                Layout.preferredHeight: -1
                Layout.preferredWidth: -1
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.verticalStretchFactor: 2
                color: "transparent"

                Image {
                    width: imageRect.width
                    height: imageRect.height
                    source: "qrc:/game/gameassets/trivia/testimage.png"
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                }
            }

            GridLayout {
                id: answersLayout
                Layout.preferredHeight: -1
                Layout.preferredWidth: -1
                layoutDirection: Qt.LeftToRight
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.verticalStretchFactor: 2
                rows: 2
                columns: 2
                anchors.bottomMargin: 0

                Button {
                    id: answer1Btn
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    display: AbstractButton.TextBesideIcon

                    Text  {
                        id: answer1Txt
                        anchors.centerIn: parent
                        font.pointSize: 18
                        text: "answer1"
                        scale: Math.min(btn1.width / width / 5, btn1.height / height / 5)
                    }
                }

                Button {
                    id: answer2Btn
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    display: AbstractButton.TextBesideIcon

                    Text  {
                        id: answer2Txt
                        anchors.centerIn: parent
                        font.pointSize: 18
                        text: "answer2"
                        scale: Math.min(btn2.width / width / 5, btn2.height / height / 5)
                    }
                }

                Button {
                    id: answer3Btn
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    display: AbstractButton.TextBesideIcon

                    Text  {
                        id: answer3Txt
                        anchors.centerIn: parent
                        font.pointSize: 18
                        text: "answer3"
                        scale: Math.min(btn3.width / width / 5, btn3.height / height / 5)
                    } 
                }

                Button {
                    id: answer4Btn
                    Layout.preferredHeight: -1
                    Layout.preferredWidth: -1
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    display: AbstractButton.TextBesideIcon

                    Text  {
                        id: answer4Txt
                        anchors.centerIn: parent
                        font.pointSize: 18
                        text: "answer4"
                        scale: Math.min(btn4.width / width / 5, btn4.height / height / 5)
                    }
                }
            }
        }
    }
}
