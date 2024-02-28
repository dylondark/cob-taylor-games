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

    signal quit() // will be emitted and picked up by mainwindow when the game wants to quit. must be present in every game!

    property real scaleFactor: height / 3840
    property int points: 0


    GuessTheLogoController {
        id: controller
    }

    ColumnLayout {
        id: baseLayout
        anchors.fill: parent

        Rectangle {
            id: background
            Layout.preferredHeight: -1
            Layout.preferredWidth: -1
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "#fff7e9"
            Layout.verticalStretchFactor: 6

            property real textSize: 300 * root.scaleFactor
            property string text1Color: "#8097ff" // blue
            property string text2Color: "#ffd980" // gold
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

            MenuBase {
                id: menuBase
                imageSource : "qrc:/menu/Logos-Buttons/trivia.png"
            }

            Item {
                id: gameBase
                anchors.fill: parent
                visible: false

                property bool lock: false // "lock" the newQuestion func so it cant be ran more than once at a time
                property var buttons: [answer1Bg, answer2Bg, answer3Bg, answer4Bg]
                property int maxQuestions: 15
                property int questionNum: 0

                Timer {
                    id: questionCountdown
                    interval: 100
                    repeat: true
                    triggeredOnStart: false

                    property int questionSeconds: 15 // change this when adjusting question time
                    property int pointsRemaining: questionSeconds * 100

                    function beginCountdown() {
                        questionCountdown.pointsRemaining = questionCountdown.questionSeconds * 100; // reset pointsRemaining
                        pointsRemainingTxt.text = timerBase.pointsPrefix + questionCountdown.pointsRemaining;
                        timeRemainingTxt.text = timerBase.timePrefix + questionCountdown.questionSeconds;
                        timerBarAnim.start();
                        questionCountdown.start();
                    }

                    function triggerActions() {
                        questionCountdown.pointsRemaining -= 10;
                        pointsRemainingTxt.text = timerBase.pointsPrefix + questionCountdown.pointsRemaining; // update the score shown to the user

                        timeRemainingTxt.text = timerBase.timePrefix + (Math.ceil(pointsRemaining / 100)).toString().padStart(2, '0');

                        if (questionCountdown.pointsRemaining <= 0) {
                            questionCountdown.stop();
                            timerBarAnim.stop();
                            gameBase.endQuestion(5);
                        }
                    }

                    onTriggered: triggerActions()
                }


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

                function endQuestion(button: int) {
                    if (!lock) {
                        lock = true;

                        // stop the countdown
                        questionCountdown.stop();
                        timerBarAnim.stop();

                        if (controller.getQuestion().correct == button) {
                            // correct answer
                            questionLabel.text = qsTr("Correct!")
                            root.points += questionCountdown.pointsRemaining // add points to total
                        }
                        else if (button == 5) {
                            // ran out of time
                            questionLabel.text = "Time's Up!";
                        }
                        else {
                            // incorrect answer
                            questionLabel.text = qsTr("Incorrect!")
                            pointsRemainingTxt.text = timerBase.pointsPrefix + "0" // set points display to 0
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

                        if (gameBase.questionNum >= gameBase.maxQuestions)
                            timer.setTimeout(function(){ endGame(); }, 3000);
                        else
                            timer.setTimeout(function(){ newQuestion(); }, 3000);
                    }
                }

                function newQuestion() {
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

                    randomizeAnswers();

                    // update the questions completed
                    questionsRemainingTxt.text = timerBase.questionPrefix + (++gameBase.questionNum) + "/" + gameBase.maxQuestions;

                    questionCountdown.beginCountdown();
                }

                function endGame() {
                    gameBase.visible = false;
                    gameOverBase.gameOverOps();
                    // send signal to put in user's score
                    // change score value in label
                    // add extra line to congratulate user if they got a leaderboard spot
                }

                // randomize answer button order
                // done by shuffling the position of the buttons in the layout
                function randomizeAnswers() {
                    var indexes = [[0, 0], [0, 1], [1, 0], [1, 1]];
                    var nums = controller.randomizeFour(); // get array of 0-3 in random order

                    // apply layout positions
                    answer1Btn.Layout.row = indexes[nums[0]][0];
                    answer1Btn.Layout.column = indexes[nums[0]][1];
                    answer2Btn.Layout.row = indexes[nums[1]][0];
                    answer2Btn.Layout.column = indexes[nums[1]][1];
                    answer3Btn.Layout.row = indexes[nums[2]][0];
                    answer3Btn.Layout.column = indexes[nums[2]][1];
                    answer4Btn.Layout.row = indexes[nums[3]][0];
                    answer4Btn.Layout.column = indexes[nums[3]][1];
                }

                Rectangle {
                    id: timerBar
                    x: 0
                    y: 0
                    width: root.width
                    height: root.height / 36
                    color: "white"

                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 8 * root.scaleFactor
                        verticalOffset: 8 * root.scaleFactor
                        radius: 28.0 * root.scaleFactor
                        color: "#aa000000"
                        samples: (radius * 2) + 1
                        cached: false
                        transparentBorder: true
                    }

                    ParallelAnimation {
                        id: timerBarAnim
                            PropertyAnimation { target: timerBar; properties: "x"; from: 0; to: 0 - root.width * 1.02; duration: 15000; }
                            SequentialAnimation {
                                PropertyAnimation { target: timerBar; properties: "color"; from: "green"; to: "yellow"; duration: 7500; }
                                PropertyAnimation { target: timerBar; properties: "color"; from: "yellow"; to: "red"; duration: 5000; }
                            }
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

                        property string timePrefix: "Time Left: 0:"
                        property string questionPrefix: "Questions: "
                        property string pointsPrefix: "Points: "

                        Rectangle {
                            color: "transparent"
                            Layout.preferredHeight: -1
                            Layout.preferredWidth: -1
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            Text {
                                id: timeRemainingTxt
                                font.pointSize: 48 * root.scaleFactor
                                text: timerBase.timePrefix
                                anchors.fill: parent
                                horizontalAlignment: Text.AlignLeft
                                verticalAlignment: Text.AlignBottom
                                fontSizeMode: Text.VerticalFit
                                font.bold: true

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 2 * root.scaleFactor
                                    verticalOffset: 2 * root.scaleFactor
                                    radius: 6.0 * root.scaleFactor
                                    color: "#aa000000"
                                    samples: (radius * 2) + 1
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
                                id: questionsRemainingTxt
                                font.pointSize: 48 * root.scaleFactor
                                anchors.fill: parent
                                text: timerBase.questionPrefix
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignBottom
                                fontSizeMode: Text.VerticalFit
                                font.bold: true

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 2 * root.scaleFactor
                                    verticalOffset: 2 * root.scaleFactor
                                    radius: 6.0 * root.scaleFactor
                                    color: "#aa000000"
                                    samples: (radius * 2) + 1
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
                                font.pointSize: 48 * root.scaleFactor
                                anchors.fill: parent
                                text: timerBase.pointsPrefix
                                horizontalAlignment: Text.AlignRight
                                verticalAlignment: Text.AlignBottom
                                fontSizeMode: Text.VerticalFit
                                font.bold: true

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 2 * root.scaleFactor
                                    verticalOffset: 2 * root.scaleFactor
                                    radius: 6.0 * root.scaleFactor
                                    color: "#aa000000"
                                    samples: (radius * 2) + 1
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
                        Layout.verticalStretchFactor: 3

                        Label {
                            id: questionLabel
                            width: questionLabelBase.width
                            height: questionLabelBase.height
                            anchors.centerIn: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#000000"
                            text: qsTr("question")
                            font.styleName: "Bold"
                            font.pointSize: 72 * root.scaleFactor
                            wrapMode: Text.WordWrap
                            fontSizeMode: Text.VerticalFit

                            layer.enabled: true
                            layer.effect: DropShadow {
                                horizontalOffset: 3 * root.scaleFactor
                                verticalOffset: 3 * root.scaleFactor
                                radius: 6.0 * root.scaleFactor
                                color: "#aa000000"
                                samples: (radius * 2) + 1
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
                        Layout.verticalStretchFactor: 6
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
                                horizontalOffset: 12 * root.scaleFactor
                                verticalOffset: 12 * root.scaleFactor
                                radius: 36.0 * root.scaleFactor
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
                        Layout.verticalStretchFactor: 6
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
                                font.pointSize: 48 * root.scaleFactor
                                text: "answer1"
                                width: answer1Btn.width
                                height: answer1Btn.height
                                wrapMode: Text.WordWrap
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.VerticalFit

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 2 * root.scaleFactor
                                    verticalOffset: 2 * root.scaleFactor
                                    radius: 8.0 * root.scaleFactor
                                    color: "#aa000000"
                                    samples: (radius * 2) + 1
                                    cached: true
                                    transparentBorder: true
                                }
                            }

                            onClicked: gameBase.endQuestion(1)

                            background: Rectangle {
                                id: answer1Bg
                                color: "white"
                                radius: 72 * root.scaleFactor

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 12 * root.scaleFactor
                                    verticalOffset: 12 * root.scaleFactor
                                    radius: 36.0 * root.scaleFactor
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
                                font.pointSize: 48 * root.scaleFactor
                                text: "answer2"
                                width: answer2Btn.width
                                height: answer2Btn.height
                                wrapMode: Text.WordWrap
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.VerticalFit

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 2 * root.scaleFactor
                                    verticalOffset: 2 * root.scaleFactor
                                    radius: 8.0 * root.scaleFactor
                                    color: "#aa000000"
                                    samples: (radius * 2) + 1
                                    cached: true
                                    transparentBorder: true
                                }
                            }

                            onClicked: gameBase.endQuestion(2)

                            background: Rectangle {
                                id: answer2Bg
                                color: "white"
                                radius: 72 * root.scaleFactor

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 12 * root.scaleFactor
                                    verticalOffset: 12 * root.scaleFactor
                                    radius: 36.0 * root.scaleFactor
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
                                font.pointSize: 48 * root.scaleFactor
                                text: "answer3"
                                width: answer3Btn.width
                                height: answer3Btn.height
                                wrapMode: Text.WordWrap
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.VerticalFit

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 2 * root.scaleFactor
                                    verticalOffset: 2 * root.scaleFactor
                                    radius: 8.0 * root.scaleFactor
                                    color: "#aa000000"
                                    samples: (radius * 2) + 1
                                    cached: true
                                    transparentBorder: true
                                }
                            }

                            onClicked: gameBase.endQuestion(3)

                            background: Rectangle {
                                id: answer3Bg
                                color: "white"
                                radius: 72 * root.scaleFactor

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 12 * root.scaleFactor
                                    verticalOffset: 12 * root.scaleFactor
                                    radius: 36.0 * root.scaleFactor
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
                                font.pointSize: 48 * root.scaleFactor
                                text: "answer4"
                                width: answer4Btn.width
                                height: answer4Btn.height
                                wrapMode: Text.WordWrap
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.VerticalFit

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 2 * root.scaleFactor
                                    verticalOffset: 2 * root.scaleFactor
                                    radius: 8.0 * root.scaleFactor
                                    color: "#aa000000"
                                    samples: (radius * 2) + 1
                                    cached: true
                                    transparentBorder: true
                                }
                            }

                            onClicked: gameBase.endQuestion(4)

                            background: Rectangle {
                                id: answer4Bg
                                color: "white"
                                radius: 72 * root.scaleFactor

                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 12 * root.scaleFactor
                                    verticalOffset: 12 * root.scaleFactor
                                    radius: 36.0 * root.scaleFactor
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

            GameOverBase {
                id: gameOverBase
            }
        }

        HomeBarBase {
            id: homeBarBase
            Layout.verticalStretchFactor: 1
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
