/*
    HopperGame.qml

    Main QML file for the Hopper game.
*/

import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQml
import QMLControllers

// this game is in PREVIEW STATE
Item {
    id: root
    width: 2160
    height: 3840

    signal quit
    signal saveScore(int game, string username, int score)

    // will be emitted and picked up by mainwindow when the game wants to quit. must be present in every game!
    property real scaleFactor: height / 3840
    property int points: 0
    property string strName: "Hopper"
    property string username: ""
    property int gameEnum: 0

    ColumnLayout {
        id: baseLayout
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: background
            Layout.preferredHeight: -1
            Layout.preferredWidth: -1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.verticalStretchFactor: 6

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#f3a469" }
                GradientStop { position: 1.0; color: "#3f51b1" }
            }

            MenuBase { // This opens the screen to input username at the beginning.
                id: menuBase
                imageSource: filepath + "/menufiles/Hopper.png"
            }

            Item { // This is the part of the code for all game events to be put in.
                id: gameBase
                anchors.fill: parent
                visible: false
                property int elapsedTime: 0

                QMLImagePreloader {
                    id: loader

                    Component.onCompleted: {
                        // Add images to preload here
                        // DONT add filepath in front of the paths here. It is already done in the C++ code.
                        loader.addImage("/gamefiles/Hopper/Run1.png");
                        loader.addImage("/gamefiles/Hopper/Run2.png");
                        loader.addImage("/gamefiles/Hopper/Jump.png");
                        loader.addImage("/gamefiles/Hopper/Slide.png");
                    }
                }

                // The code for the scores boxes here
                Rectangle {
                    id: scoreBox
                    width: parent.width
                    height: 150 * root.scaleFactor
                    color: "#3f51b1"
                    anchors.left: parent.left
                    anchors.top: parent.top

                    // Shows score ran in meters in score box
                    Text {
                        id: scoreText
                        text: "Score: " + root.points + " meters"
                        font.pixelSize: 70 * root.scaleFactor
                        color: "white"
                        anchors.left: parent.left
                        anchors.leftMargin: 20 * root.scaleFactor
                        anchors.verticalCenter: parent.verticalCenter
                    }


                    // Displays the Timer measuring the time of each turn played
                    Text{
                        id: timeText
                        text: "Time: " + gameBase.elapsedTime + "s"
                        font.pixelSize: 70 * root.scaleFactor
                        color: "white"
                        anchors.right: parent.right
                        anchors.rightMargin: 50 * root.scaleFactor
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                // Begin game rectangle
                Rectangle {
                    id: gameRect
                    width: 1750 * root.scaleFactor
                    height: 2800 * root.scaleFactor
                    anchors.horizontalCenter: parent.horizontalCenter
                    y: (parent.height - height) / 2 - 200 * root.scaleFactor

                    // Function to start the round and begin the timer
                    function startRound() {
                        gameBase.roundTime = 0;// Resets the time
                        roundTimer.start(); // Starts the timer
                    }

                    function checkCollision(object1, object2) {
                        return object1.x < object2.x + object2.width &&
                                object1.x + object1.width > object2.x &&
                                object1.y < object2.y + object2.height &&
                                object1.y + object1.height > object2.y;
                    }



                    Rectangle {
                        id: skyRect
                        width: 1750 * root.scaleFactor
                        height: 2800 * root.scaleFactor
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.verticalStretchFactor: 3
                        color: "#b5fffe"
                    }

                    // Floor Rectangle for Zippy to run on
                    Rectangle {
                        id: floorRect
                        width: 1750 * root.scaleFactor
                        height: 600 * root.scaleFactor
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.verticalStretchFactor: 1
                        anchors.bottom: parent.bottom
                        color: "#16bd10"
                    }

                    // Zippy Hitboxes
                    Rectangle {
                        id: zippyBHitbox
                        anchors.centerIn: zippyModel
                        width: 225 * root.scaleFactor
                        height: 550 * root.scaleFactor
                        color: "red"
                    }

                    Rectangle {
                        id: zippyHHitbox
                        anchors.top: zippyModel.top
                        anchors.horizontalCenter: zippyModel.horizontalCenter
                        width: 400 * root.scaleFactor
                        height: 150 * root.scaleFactor
                        color: "green"
                    }

                    // Zippy Model
                    Image {
                        id: zippyModel
                        width: 850 * root.scaleFactor
                        height: 700 * root.scaleFactor
                        x: (parent.width - width) - 950 * root.scaleFactor
                        y: floorRect.y - height + 50 // Starting position on the floor

                        property bool isRunning: true

                        // Animation for zippy running that changes every 500 ticks
                        source: loader.getImage(isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png")
                        fillMode: Image.PreserveAspectFit
                        smooth: true // turn off if performance is bad
                        asynchronous: true
                        cache: false
                        retainWhileLoading: true // REQUIRES QT 6.8!!!

                        // Timer for Zippy Running
                        Timer {
                            id: runTimer
                            interval: 500
                            running: true
                            repeat: true
                            onTriggered: {
                                zippyModel.isRunning = !zippyModel.isRunning
                            }
                        }

                        // Timer for counting seconds when the round starts
                        Timer {
                            id: roundTimer
                            interval: 1000 // 1000 ms = 1 second
                            running: true // Initially stopped
                            repeat: true // Continuously counts up
                            onTriggered: {
                                gameBase.elapsedTime += 1;
                                root.points += 5;
                                homeBarBase.updatePoints();
                            }
                        }

                        // Animation for Hopping
                        SequentialAnimation on y {
                            id: hopAnimation
                            running: false
                            loops: 1

                            PropertyAction { target: zippyModel; property: "source"; value: loader.getImage("/gamefiles/Hopper/Jump.png") } // Set image to Jump.png at start
                            PropertyAction { target: runTimer; property: "running"; value: false }

                            PropertyAnimation { to: floorRect.y - (1200 * root.scaleFactor); duration: 500; easing.type: Easing.OutQuad } // Jump (reaches peak of height)
                            PropertyAnimation { to: floorRect.y - zippyModel.height + 50; duration: 500; easing.type: Easing.InQuad } // Land

                            PropertyAction { target: runTimer; property: "running"; value: true }
                            PropertyAction { target: zippyModel; property: "source"; value: loader.getImage(zippyModel.isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png") }
                        }

                        // Animation for "Sliding"
                        // Known bug: If you "Slide-Hop" AFTER "Hop-Slide", Zippy exits the bounds of the grass
                        SequentialAnimation on height {
                            id: slideAnimation
                            running: false
                            loops: 1

                            PropertyAction { target: zippyModel; property: "source"; value: loader.getImage("/gamefiles/Hopper/Slide.png") } // Set image to Jump.png at start
                            PropertyAction { target: runTimer; property: "running"; value: false } // Stop the Timer


                            PropertyAnimation { to: 400 * root.scaleFactor; duration: 300; easing.type: Easing.OutQuad } // Duck down
                            PropertyAnimation { to: 700 * root.scaleFactor; duration: 300; easing.type: Easing.InQuad } // Return to original height

                            PropertyAction { target: runTimer; property: "running"; value: true }
                            PropertyAction { target: zippyModel; property: "source"; value: loader.getImage(zippyModel.isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png") }
                        }
                    }


                    // Cloud Background Image
                    Image {
                        id: cloud
                        width: 250 * root.scaleFactor
                        height: 150 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Cloud.png"
                        x: parent.width
                        y: floorRect.y - 1040 * root.scaleFactor  // Cloud in the sky

                        // Animation for rock movement
                        PropertyAnimation on x {
                            from: 850 * root.scaleFactor
                            to: 0
                            duration: 8000  // Adjust speed
                            loops: Animation.Infinite
                            running: true
                        }
                    }

                    Timer { // Timer for obstacles coming out
                        id: obstacleTimer
                        interval: 3000
                        running: true
                        repeat: true
                        onTriggered: {
                            // Generate a random number between 1 and 3
                            let obstacleType = Math.floor(Math.random() * 3) + 1;

                            console.log(obstacleType)
                            // Trigger the appropriate obstacle animation
                            if (obstacleType === 1) {
                                rockAnimation.running = true;
                            } else if (obstacleType === 2) {
                                statueAnimation.running = true;
                            } else if (obstacleType === 3) {
                                birdAnimation.running = true;
                            }
                        }
                    }

                    // Rock Obstacle
                    Rectangle {
                        id: rockHitbox
                        width: 120 * root.scaleFactor
                        height: 100 * root.scaleFactor
                        anchors.centerIn: rock
                        color: "red"
                    }

                    Image {
                        id: rock
                        width: 120 * root.scaleFactor
                        height: 100 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Rock.png"
                        x: parent.width
                        y: floorRect.y - 40 * root.scaleFactor  // Places the rock on the ground

                        // Animation for rock movement
                        PropertyAnimation on x {
                            id: rockAnimation
                            from: parent.width
                            to: -300
                            duration: 2750  // Adjust speed
                            loops: 1
                            running: false
                        }

                        // Rock hit detection timer
                        Timer {
                            id: rocktimer
                            interval: 16  // Roughly 60 FPS
                            running: true
                            repeat: true
                            onTriggered: {
                                // Simple AABB collision detection
                                if (gameRect.checkCollision(rockHitbox, zippyHitbox)) {
                                    console.log("Hit detected!")
                                    floorRect.color = "#FFFFFF"

                                    // You can stop the game or trigger a game-over logic here
                                }
                            }
                        }
                    }

                    // statue Obstacle
                    Rectangle {
                        id: statueHitbox
                        width: 200 * root.scaleFactor
                        height: 500 * root.scaleFactor
                        anchors.centerIn: statue
                        color: "red"
                    }

                    Image {
                        id: statue
                        width: 200 * root.scaleFactor
                        height: 500 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/statue.png"
                        x: parent.width
                        y: floorRect.y - height + 50  // Place the statue at the grass

                        // Animation for statue movement
                        PropertyAnimation on x {
                            id: statueAnimation
                            from: parent.width
                            to: -300
                            duration: 3000  // Adjust speed
                            loops: 1
                            running: false
                        }

                        // statue hit detection timer
                        Timer {
                            interval: 16  // Roughly 60 FPS
                            running: true
                            repeat: true
                            onTriggered: {
                                // Simple AABB collision detection
                                if (gameRect.checkCollision(statueHitbox, zippyHitbox)) {
                                    console.log("Hit detected!")
                                    floorRect.color = "#FF000"

                                    // You can stop the game or trigger a game-over logic here
                                }
                            }
                        }
                    }

                    // Bird obstacle
                    Rectangle {
                        id: birdHitbox
                        width: 375 * root.scaleFactor
                        height: 350 * root.scaleFactor
                        anchors.centerIn: bird
                        color: "red"
                    }

                    Image {
                        id: bird
                        width: 350 * root.scaleFactor
                        height: 330 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Bird.png"
                        x: parent.width
                        y: 1200 * root.scaleFactor  // Place the bird at the top of the screen

                        // Animation for bird movement
                        PropertyAnimation on x {
                            id: birdAnimation
                            from: parent.width
                            to: -300
                            duration: 3000  // Adjust speed
                            loops: 1
                            running: false
                        }

                        // Bird hit detection timer
                        Timer {
                            interval: 16  // Roughly 60 FPS
                            running: true
                            repeat: true
                            onTriggered: {
                                // Simple AABB collision detection
                                if (gameRect.checkCollision(birdHitbox, zippyHitbox)) {
                                    console.log("Hit detected!")
                                    floorRect.color = "#FFFFFF"

                                    // You can stop the game or trigger a game-over logic here
                                }
                            }
                        }
                    }
                }

                ColumnLayout {
                    id: btnLayout
                    width: 800 * root.scaleFactor
                    height: 400 * root.scaleFactor
                    anchors.horizontalCenter: gameRect.horizontalCenter
                    y: gameRect.height + 350 * root.scaleFactor
                    spacing: 100 * root.scaleFactor

                    Button {
                        id: hopBtn
                        implicitWidth: parent.width
                        implicitHeight: (btnLayout.height - btnLayout.spacing) / 2 // Dynamic height based on layout

                        background: Rectangle {
                            id: hopRect
                            color: "white"
                            opacity: 0.7
                            border.color: "black"
                            radius: 100 * root.scaleFactor
                            anchors.fill: parent
                        }

                        contentItem: Text {
                            text: "Hop!"
                            font.pointSize: 70 * root.scaleFactor
                            anchors.centerIn: parent.Center
                        }

                        onClicked: {
                            if (!hopAnimation.running) {
                                hopAnimation.start(); // Start the hop animation
                            }
                        }
                    }

                    Button {
                        id: slideBtn
                        implicitWidth: parent.width
                        implicitHeight: (btnLayout.height - btnLayout.spacing) / 2 // Dynamic height based on layout

                        background: Rectangle {
                            id:slideRect
                            color: "white"
                            opacity: 0.7
                            border.color: "black"
                            radius: 100 * root.scaleFactor
                            anchors.fill: parent
                        }

                        contentItem: Text {
                            text: "Slide!"
                            font.pointSize: 70 * root.scaleFactor
                            anchors.centerIn: parent
                        }

                        onClicked: {
                            if (!slideAnimation.running) {
                                slideAnimation.start(); // Start the slide/duck animation
                            }
                        }
                    }
                }
            }

            GameOverBase { // This calls a CPP file which saves the name and score to the leaderboard.
                id:gameOverBase
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
