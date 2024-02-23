import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import Qt5Compat.GraphicalEffects
import QMLControllers
import QtQuick.VirtualKeyboard 2.15

Item {
    id: root
    width: 2160
    height: 3840

    property real scaleFactor: height / 3840


    TriviaController {
        id: controller
    }

    ColumnLayout {
        id: baseLayout
        anchors.fill: parent

        Rectangle {
            id: background
            anchors.fill: parent
            anchors.centerIn: parent
            color: "#fff7e9"

            property real textSize: 300 * root.scaleFactor
            property string text1Color: "#588bff" // blue
            property string text2Color: "#ffd36c" // gold
            property int ms: 10000

            // background animation text rows
            Text {
                id: animText1
                y: 0
                text: "? ? ? ? ? ? ? ? ? ? ?"
                font.styleName: "The Next Font"
                font.pointSize: background.textSize
                font.wordSpacing: background.textSize
                font.bold: true
                color: background.text1Color

                SequentialAnimation on x {
                        loops: Animation.Infinite
                        PropertyAnimation { from: 0 - background.textSize * 2; to: 0; duration: background.ms; }
                    }
            }

            Text {
                id: animText2
                y: (root.height / 6)
                text: "? ? ? ? ? ? ? ? ? ? ?"
                font.styleName: "The Next Font"
                font.pointSize: background.textSize
                font.wordSpacing: font.pointSize
                font.bold: true
                color: background.text2Color

                SequentialAnimation on x {
                        loops: Animation.Infinite
                        PropertyAnimation { from: 0; to: 0 - background.textSize * 2; duration: background.ms; }
                    }
            }

            Text {
                id: animText3
                y: (root.height / 6) * 2
                text: "? ? ? ? ? ? ? ? ? ? ?"
                font.styleName: "The Next Font"
                font.pointSize: background.textSize
                font.wordSpacing: background.textSize
                font.bold: true
                color: background.text1Color

                SequentialAnimation on x {
                        loops: Animation.Infinite
                        PropertyAnimation { from: 0 - background.textSize * 2; to: 0; duration: background.ms; }
                    }
            }

            Text {
                id: animText4
                y: (root.height / 6) * 3
                text: "? ? ? ? ? ? ? ? ? ? ?"
                font.styleName: "The Next Font"
                font.pointSize: background.textSize
                font.wordSpacing: font.pointSize
                font.bold: true
                color: background.text2Color

                SequentialAnimation on x {
                        loops: Animation.Infinite
                        PropertyAnimation { from: 0; to: 0 - background.textSize * 2; duration: background.ms; }
                    }
            }

            Text {
                id: animText5
                y: (root.height / 6) * 4
                text: "? ? ? ? ? ? ? ? ? ? ?"
                font.styleName: "The Next Font"
                font.pointSize: background.textSize
                font.wordSpacing: background.textSize
                font.bold: true
                color: background.text1Color

                SequentialAnimation on x {
                        loops: Animation.Infinite
                        PropertyAnimation { from: 0 - background.textSize * 2; to: 0; duration: background.ms; }
                    }
            }

            Text {
                id: animText6
                y: (root.height / 6) * 5
                text: "? ? ? ? ? ? ? ? ? ? ?"
                font.styleName: "The Next Font"
                font.pointSize: background.textSize
                font.wordSpacing: font.pointSize
                font.bold: true
                color: background.text2Color

                SequentialAnimation on x {
                        loops: Animation.Infinite
                        PropertyAnimation { from: 0; to: 0 - background.textSize * 2; duration: background.ms; }
                    }
            }

            Item {
                id: menuBase
                anchors.fill: parent

                InputPanel {
                    id:inputPanel
                    z:99
                    anchors.bottom: parent.bottom
                    visible: true
                    width: parent.width
                    height: parent.height / 3
                }

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 72 * root.scaleFactor

                    Rectangle {
                        id: menuImgRect
                        color: "transparent"
                        Layout.verticalStretchFactor: 6
                        Layout.preferredHeight: 1
                        Layout.preferredWidth: 1
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        anchors.margins: 72 * root.scaleFactor

                        Image {
                            id: menuImg
                            source: "qrc:/menu/Logos-Buttons/trivia.png"
                            width: parent.width
                            height: parent.height
                            fillMode: Image.PreserveAspectFit

                            layer.enabled: true
                            layer.effect: DropShadow {
                                horizontalOffset: 12 * root.scaleFactor
                                verticalOffset: 12 * root.scaleFactor
                                radius: 24.0 * root.scaleFactor
                                samples: (radius * 2) + 1
                                color: "#aa000000"
                                cached: true
                                transparentBorder: true
                            }
                        }
                    }

                    Item {
                        id: nameItem
                        Layout.verticalStretchFactor: 1
                        Layout.preferredHeight: 1
                        Layout.preferredWidth: 1
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        RowLayout {
                            anchors.fill: parent
                            spacing: 10
                            anchors.leftMargin: 600 * root.scaleFactor
                            anchors.rightMargin: 600 * root.scaleFactor


                            Text {
                                id:nameText
                                text: 'NAME:'
                                font.family: "1UP!" //Text font
                                font.bold: true
                                font.pointSize: 78 * root.scaleFactor
                                color: "black"
                                Layout.alignment: Qt.AlignVCenter // Vertically center align the text within its space
                            }

                            TextField {
                                id: playerName
                                maximumLength: 4
                                focus: true
                                Layout.fillWidth: true // Allow the text field to take up the remaining space
                                Layout.alignment: Qt.AlignVCenter // Vertically center align the text field
                                font.capitalization: Font.AllUppercase //make all characters look uppercase
                                Layout.preferredWidth: -1
                                onTextChanged: {
                                    playerName.text = playerName.text.toUpperCase() //Actually make all characters uppercase
                                }
                                font.family: "1UP!"
                                font.bold: true
                                font.pointSize: nameText.font.pointSize
                            }

                        }

                    }


                    Rectangle {
                        id: playRect
                        color: "transparent"
                        Layout.verticalStretchFactor: 6
                        Layout.preferredHeight: 1
                        Layout.preferredWidth: 1
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        anchors.margins: 72 * root.scaleFactor

                        Button {
                            id: playButton
                            width: parent.width / 2
                            height: parent.height / 6
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.height / 3
                            font.pointSize: 72 * root.scaleFactor
                            text: "PLAY"
                            font.family: "1UP!"
                            font.bold: true

                            background: Rectangle {
                                color: Qt.rgba(1, 1, 1, 0.6)
                                radius: 72 * root.scaleFactor
                                border.color: "black"
                                border.width: 12 * root.scaleFactor
                            }

                            onClicked: {
                                menuBase.visible = false;
                                gameBase.visible = true;
                                gameBase.questionOps();
                            }
                        }
                    }
                }
            }

            Item {
                id: gameBase
                anchors.fill: parent
                visible: false

                property bool lock: false // "lock" the newQuestion func so it cant be ran more than once at a time
                property var buttons: [answer1Bg, answer2Bg, answer3Bg, answer4Bg]

                Timer {
                    id: timer
                    // cb: callback to a function we want to run afterward
                    // delayTime: milliseconds to wait
                    function setTimeout(cb, delayTime) {
                        timer.interval = delayTime;
                        timer.repeat = false;
                        timer.triggered.connect(cb);
                        timer.triggered.connect(function release () {
                            timer.triggered.disconnect(cb);
                            timer.triggered.disconnect(release);
                        });
                        timer.start();
                    }
                }

                PropertyAnimation {id: correctAnim; properties: "color"; to: "#5bee62"; duration: 100} // target is set dynamically to whichever is correct at the time
                PropertyAnimation {id: incorrectAnim1; properties: "color"; to: "#ff3030"; target: answer1Bg; duration: 100}
                PropertyAnimation {id: incorrectAnim2; properties: "color"; to: "#ff3030"; target: answer2Bg; duration: 100}
                PropertyAnimation {id: incorrectAnim3; properties: "color"; to: "#ff3030"; target: answer3Bg; duration: 100}
                PropertyAnimation {id: incorrectAnim4; properties: "color"; to: "#ff3030"; target: answer4Bg; duration: 100}

                function newQuestion(button: int) {
                    if (!lock) {
                        lock = true;

                        if (controller.getQuestion().correct == button) {
                            // correct answer
                            questionLabel.text = qsTr("Correct!")
                        }
                        else {
                            // incorrect answer
                            questionLabel.text = qsTr("Incorrect!")
                        }

                        // fade incorrect buttons to red
                        if (controller.getQuestion().correct != 1)
                            incorrectAnim1.start();
                        if (controller.getQuestion().correct != 2)
                            incorrectAnim2.start();
                        if (controller.getQuestion().correct != 3)
                            incorrectAnim3.start();
                        if (controller.getQuestion().correct != 4)
                            incorrectAnim4.start();

                        // fade the correct button to green
                        correctAnim.target = buttons[controller.getQuestion().correct - 1];
                        correctAnim.start();

                        timer.setTimeout(function(){ questionOps(); }, 3000);
                    }
                }

                function questionOps() {
                    controller.randQuestion();
                    questionLabel.text = controller.getQuestion().question;
                    answer1Txt.text = controller.getQuestion().ans1;
                    answer2Txt.text = controller.getQuestion().ans2;
                    answer3Txt.text = controller.getQuestion().ans3;
                    answer4Txt.text = controller.getQuestion().ans4;
                    questionImage.source = controller.getQuestion().img;
                    lock = false;

                    // reset colors
                    answer1Bg.color = "white";
                    answer2Bg.color = "white";
                    answer3Bg.color = "white";
                    answer4Bg.color = "white";
                }

                Rectangle {
                    id: timerBar
                    x: 0
                    y: 0
                    width: root.width
                    height: root.height / 30
                    color: "white"

                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 4
                        verticalOffset: 4
                        radius: 14.0
                        color: "#aa000000"
                        samples: (radius * 2) + 1
                        cached: false
                        transparentBorder: true
                    }
                }

                ColumnLayout {
                    id: gameLayout
                    anchors.fill: parent
                    anchors.margins: 60 * root.scaleFactor
                    layoutDirection: Qt.LeftToRight
                    spacing: 60 * root.scaleFactor

                    RowLayout {
                        id: timerBase
                        Layout.preferredHeight: -1
                        Layout.preferredWidth: -1
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.verticalStretchFactor: 1
                        layoutDirection: Qt.LeftToRight

                        Rectangle {
                            color: "transparent"
                            Layout.preferredHeight: -1
                            Layout.preferredWidth: -1
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            Text {
                                id: timeRemainingTxt
                                font.pointSize: 60 * root.scaleFactor
                                text: "time"
                                anchors.fill: parent
                                horizontalAlignment: Text.AlignLeft
                                verticalAlignment: Text.AlignBottom
                                fontSizeMode: Text.VerticalFit
                                font.bold: true

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 1
                                    verticalOffset: 1
                                    radius: 3.0
                                    color: "#aa000000"
                                    cached: false
                                    transparentBorder: true
                                }
                            }
                        }

                        Rectangle {
                            color: "transparent"
                            Layout.preferredHeight: -1
                            Layout.preferredWidth: -1
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            anchors.margins: 40 * root.scaleFactor

                            Text {
                                id: pointsRemainingTxt
                                font.pointSize: 60 * root.scaleFactor
                                anchors.fill: parent
                                text: "points"
                                horizontalAlignment: Text.AlignRight
                                verticalAlignment: Text.AlignBottom
                                fontSizeMode: Text.VerticalFit
                                font.bold: true

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 1
                                    verticalOffset: 1
                                    radius: 3.0
                                    color: "#aa000000"
                                    cached: false
                                    transparentBorder: true
                                }
                            }
                        }
                    }

                    Rectangle {
                        id: questionLabelBase
                        Layout.preferredHeight: -1
                        Layout.preferredWidth: -1
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "transparent"
                        Layout.verticalStretchFactor: 2

                        Label {
                            id: questionLabel
                            width: questionLabelBase.width / root.scaleFactor
                            height: questionLabelBase.height / root.scaleFactor
                            anchors.centerIn: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#000000"
                            text: qsTr("question")
                            font.styleName: "Bold"
                            font.pointSize: 72
                            scale: root.scaleFactor
                            wrapMode: Text.WordWrap
                            fontSizeMode: Text.VerticalFit

                            layer.enabled: true
                            layer.effect: DropShadow {
                                horizontalOffset: 2
                                verticalOffset: 2
                                radius: 5.0
                                color: "#aa000000"
                                cached: false
                                transparentBorder: true
                            }
                        }
                    }

                    Rectangle {
                        id: imageRect
                        Layout.preferredHeight: -1
                        Layout.preferredWidth: -1
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.verticalStretchFactor: 5
                        color: "transparent"

                        Image {
                            id: questionImage
                            width: imageRect.width
                            height: imageRect.height
                            source: "qrc:/game/gameassets/trivia/testimage.png"
                            fillMode: Image.PreserveAspectFit
                            smooth: true

                            layer.enabled: true
                            layer.effect: DropShadow {
                                horizontalOffset: 6
                                verticalOffset: 6
                                radius: 18.0
                                samples: (radius * 2) + 1
                                color: "#aa000000"
                                cached: true
                                transparentBorder: true
                            }
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
                        Layout.verticalStretchFactor: 5
                        rows: 2
                        columns: 2
                        anchors.bottomMargin: 0
                        columnSpacing: 40 * scaleFactor
                        rowSpacing: 40 * scaleFactor

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
                                font.pointSize: 48
                                text: "answer1"
                                scale: root.scaleFactor
                                width: answer1Btn.width / root.scaleFactor
                                height: answer1Btn.height / root.scaleFactor
                                wrapMode: Text.WordWrap
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.VerticalFit

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 1
                                    verticalOffset: 1
                                    radius: 4.0
                                    color: "#aa000000"
                                    cached: true
                                    transparentBorder: true
                                }
                            }

                            onClicked: gameBase.newQuestion(1)

                            background: Rectangle {
                                id: answer1Bg
                                color: "white"
                                radius: 72 * root.scaleFactor

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 6
                                    verticalOffset: 6
                                    radius: 18.0
                                    samples: (radius * 2) + 1
                                    color: "#aa000000"
                                    cached: false
                                    transparentBorder: true
                                }
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
                                font.pointSize: 48
                                text: "answer2"
                                scale: root.scaleFactor
                                width: answer2Btn.width / root.scaleFactor
                                height: answer2Btn.height / root.scaleFactor
                                wrapMode: Text.WordWrap
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.VerticalFit

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 1
                                    verticalOffset: 1
                                    radius: 4.0
                                    color: "#aa000000"
                                    cached: true
                                    transparentBorder: true
                                }
                            }

                            onClicked: gameBase.newQuestion(2)

                            background: Rectangle {
                                id: answer2Bg
                                color: "white"
                                radius: 72 * root.scaleFactor

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 6
                                    verticalOffset: 6
                                    radius: 18.0
                                    samples: (radius * 2) + 1
                                    color: "#aa000000"
                                    cached: false
                                    transparentBorder: true
                                }
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
                                font.pointSize: 48
                                text: "answer3"
                                scale: root.scaleFactor
                                width: answer3Btn.width / root.scaleFactor
                                height: answer3Btn.height / root.scaleFactor
                                wrapMode: Text.WordWrap
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.VerticalFit

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 1
                                    verticalOffset: 1
                                    radius: 4.0
                                    color: "#aa000000"
                                    cached: true
                                    transparentBorder: true
                                }
                            }

                            onClicked: gameBase.newQuestion(3)

                            background: Rectangle {
                                id: answer3Bg
                                color: "white"
                                radius: 72 * root.scaleFactor

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 6
                                    verticalOffset: 6
                                    radius: 18.0
                                    samples: (radius * 2) + 1
                                    color: "#aa000000"
                                    cached: false
                                    transparentBorder: true
                                }
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
                                font.pointSize: 48
                                text: "answer4"
                                scale: root.scaleFactor
                                width: answer4Btn.width / root.scaleFactor
                                height: answer4Btn.height / root.scaleFactor
                                wrapMode: Text.WordWrap
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.VerticalFit

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 1
                                    verticalOffset: 1
                                    radius: 4.0
                                    color: "#aa000000"
                                    cached: true
                                    transparentBorder: true
                                }
                            }

                            onClicked: gameBase.newQuestion(4)

                            background: Rectangle {
                                id: answer4Bg
                                color: "white"
                                radius: 72 * root.scaleFactor

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 6
                                    verticalOffset: 6
                                    radius: 18.0
                                    samples: (radius * 2) + 1
                                    color: "#aa000000"
                                    cached: false
                                    transparentBorder: true
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
