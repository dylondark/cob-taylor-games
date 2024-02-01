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
        id: controller
    }

    Rectangle {
        id: gameBase
        visible: true
        color: "#004c9d"
        anchors.fill: parent

        Component.onCompleted: questionOps(); // get the first question on startup
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

        PropertyAnimation {id: correctAnim; properties: "color"; to: "green"; duration: 100} // target is set dynamically to whichever is correct at the time
        PropertyAnimation {id: incorrectAnim1; properties: "color"; to: "red"; target: answer1Bg; duration: 100}
        PropertyAnimation {id: incorrectAnim2; properties: "color"; to: "red"; target: answer2Bg; duration: 100}
        PropertyAnimation {id: incorrectAnim3; properties: "color"; to: "red"; target: answer3Bg; duration: 100}
        PropertyAnimation {id: incorrectAnim4; properties: "color"; to: "red"; target: answer4Bg; duration: 100}

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

        ColumnLayout {
            id: gameLayout
            anchors.fill: parent
            layoutDirection: Qt.LeftToRight
            spacing: 1

            Rectangle {
                id: questionLabelBase
                Layout.preferredHeight: -1
                Layout.preferredWidth: -1
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "transparent"
                Layout.verticalStretchFactor: 1

                Label {
                    id: questionLabel
                    width: questionLabelBase.width / (gameBase.height / 3840)
                    height: questionLabelBase.height / (gameBase.height / 3840)
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "#000000"
                    text: qsTr("question")
                    font.styleName: "Bold"
                    font.pointSize: 72
                    scale: Math.min(gameBase.width / 2160, gameBase.height / 3840)
                    wrapMode: Text.WordWrap
                    fontSizeMode: Text.VerticalFit
                }
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
                    id: questionImage
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
                        font.pointSize: 48
                        text: "answer1"
                        scale: Math.min(gameBase.height / 3840, gameBase.height / 3840)
                        width: answer1Btn.width / (gameBase.height / 3840)
                        height: answer1Btn.height / (gameBase.height / 3840)
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        fontSizeMode: Text.VerticalFit
                    }

                    onClicked: gameBase.newQuestion(1)

                    background: Rectangle {
                        id: answer1Bg
                        color: "white"
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
                        scale: Math.min(gameBase.height / 3840, gameBase.height / 3840)
                        width: answer2Btn.width / (gameBase.height / 3840)
                        height: answer2Btn.height / (gameBase.height / 3840)
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        fontSizeMode: Text.VerticalFit
                    }

                    onClicked: gameBase.newQuestion(2)

                    background: Rectangle {
                        id: answer2Bg
                        color: "white"
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
                        scale: Math.min(gameBase.height / 3840, gameBase.height / 3840)
                        width: answer3Btn.width / (gameBase.height / 3840)
                        height: answer3Btn.height / (gameBase.height / 3840)
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        fontSizeMode: Text.VerticalFit
                    } 

                    onClicked: gameBase.newQuestion(3)

                    background: Rectangle {
                        id: answer3Bg
                        color: "white"
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
                        scale: Math.min(gameBase.height / 3840, gameBase.height / 3840)
                        width: answer4Btn.width / (gameBase.height / 3840)
                        height: answer4Btn.height / (gameBase.height / 3840)
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        fontSizeMode: Text.VerticalFit
                    }

                    onClicked: gameBase.newQuestion(4)

                    background: Rectangle {
                        id: answer4Bg
                        color: "white"
                    }
                }
            }
        }
    }
}
