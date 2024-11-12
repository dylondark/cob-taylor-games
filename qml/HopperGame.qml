/*
    HopperGame.qml

    Main QML file for the Hopper game.
*/

import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts 1.15
import QtQml

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
    property int metersRan: 0

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

                //Begin game rectangle
                Rectangle {
                    id: gameRect
                    width: 1750 * root.scaleFactor
                    height: 2800 * root.scaleFactor
                    anchors.horizontalCenter: parent.horizontalCenter
                    y: (parent.height - height) / 2 - 200 * root.scaleFactor

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

                    // Zippy Hitbox
                    Rectangle {
                        id: zippyHitBox
                        anchors.centerIn: zippyModel
                        width: 425 * root.scaleFactor
                        height: 550 * root.scaleFactor
                        color: "transparent"
                    }

                    //Zippy Model
                    Image {
                        id: zippyModel
                        width: 850 * root.scaleFactor
                        height: 700 * root.scaleFactor
                        x: (parent.width - width) - 950 * root.scaleFactor
                        y: floorRect.y - height + 50 // Starting position on the floor

                        property bool isRunning: true

                        // Animation for zippy running that changes every 500 ticks
                        source: filepath + (isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png")
                        fillMode: Image.PreserveAspectFit
                        smooth: true
                        asynchronous: true

                        // Timer for Zippy Running
                        Timer {
                            id: runTimer
                            interval: 500
                            running: true
                            repeat: true
                            onTriggered: {
                                zippyModel.isRunning = !zippyModel.isRunning
                                root.metersRan += 1;
                            }
                        }

                        // Timer for counting seconds when the round starts
                           Timer {
                               id: roundTimer
                               interval: 1000 // 1000 ms = 1 second
                               running: false // Initially stopped
                               repeat: true // Continuously counts up
                               onTriggered: {
                                   gameBase.elapsedTime += 1
                               }
                           }

                           // Function to start the round and begin the timer
                           function startRound() {
                               gameBase.roundTime = 0;// Resets the time
                               root.metersRan = 0;
                               roundTimer.start(); // Starts the timer
                           }


                        // Animation for Hopping
                        SequentialAnimation on y {
                            id: hopAnimation
                            running: false
                            loops: 1

                            PropertyAction { target: zippyModel; property: "source"; value: filepath + "/gamefiles/Hopper/Jump.png" }
                            PropertyAction { target: runTimer; property: "running"; value: false }

                            PropertyAnimation { to: floorRect.y - (1200 * root.scaleFactor); duration: 500; easing.type: Easing.OutQuad } // Jump (reaches peak of height)
                            PropertyAnimation { to: floorRect.y - zippyModel.height + 50; duration: 500; easing.type: Easing.InQuad } // Land

                            PropertyAction { target: runTimer; property: "running"; value: true }
                            PropertyAction { target: zippyModel; property: "source"; value: filepath + (zippyModel.isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png") }
                        }

                        // Animation for "Sliding"
                        // Known bug: If you "Slide-Hop" AFTER "Hop-Slide", Zippy exits the bounds of the grass
                        SequentialAnimation on height {
                            id: slideAnimation
                            running: false
                            loops: 1

                            PropertyAction { target: zippyModel; property: "source"; value: filepath + "/gamefiles/Hopper/Slide.png" } // Set image to Jump.png at start
                            PropertyAction { target: runTimer; property: "running"; value: false } // Stop the Timer


                            PropertyAnimation { to: 400 * root.scaleFactor; duration: 300; easing.type: Easing.OutQuad } // Duck down
                            PropertyAnimation { to: 700 * root.scaleFactor; duration: 300; easing.type: Easing.InQuad } // Return to original height

                            PropertyAction { target: runTimer; property: "running"; value: true }
                            PropertyAction { target: zippyModel; property: "source"; value: filepath + (zippyModel.isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png") }
                        }
                    }


                    //Cloud Background Image
                    Image {
                        id: cloud
                        width: 250
                        height: 150
                        source: filepath + "/gamefiles/Hopper/Cloud.png"
                        x: parent.width
                        y: floorRect.y - 1040  // Cloud in the sky

                        // Animation for rock movement
                        PropertyAnimation on x {
                            from: 850 * root.scaleFactor
                            to: 0
                            duration: 8000  // Adjust speed
                            loops: Animation.Infinite
                            running: true
                        }

                    }
                    Timer {
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
                                carAnimation.running = true;
                            } else if (obstacleType === 3) {
                                birdAnimation.running = true;
                            }
                        }
                    }

                    // Rock Obstacle
                    Image {
                        id: rock
                        width: 120
                        height: 100
                        source: filepath + "/gamefiles/Hopper/Rock.png"
                        x: parent.width
                        y: floorRect.y - 40  // Places the rock on the ground

                        // Animation for rock movement
                        PropertyAnimation on x {
                            id: rockAnimation
                            from: parent.width
                            to: -300
                            duration: 3000  // Adjust speed
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
                                if (rock.x < zippyHitBox.x + zippyHitBox.width &&
                                        rock.x + rock.width > zippyHitBox.x &&
                                        rock.y < zippyHitBox.y + zippyHitBox.height &&
                                        rock.y + rock.height > zippyHitBox.y) {
                                    console.log("Hit detected!")
                                    floorRect.color = "#FFFFFF"

                                    // You can stop the game or trigger a game-over logic here
                                }
                            }
                        }
                    }

                    // Car Obstacle
                    Image {
                        id: car
                        width: 200
                        height: 150
                        source: filepath + "/gamefiles/Hopper/car.png"
                        x: parent.width
                        y: 2000 * root.scaleFactor  // Place the car at the grass

                        // Animation for car movement
                        PropertyAnimation on x {
                            id: carAnimation
                            from: parent.width
                            to: -300
                            duration: 2000  // Adjust speed
                            loops: 1
                            running: false
                        }

                        // Car hit detection timer
                        Timer {
                            interval: 16  // Roughly 60 FPS
                            running: true
                            repeat: true
                            onTriggered: {
                                // Simple AABB collision detection
                                if (car.x < zippyHitBox.x + zippyHitBox.width &&
                                        car.x + car.width > zippyHitBox.x &&
                                        car.y < zippyHitBox.y + zippyHitBox.height &&
                                        car.y + car.height > zippyHitBox.y) {
                                    console.log("Hit detected!")
                                    floorRect.color = "#FF000"

                                    // You can stop the game or trigger a game-over logic here
                                }
                            }
                        }
                    }

                    // Bird obstacle
                    Image {
                        id: bird
                        width: 30
                        height: 20
                        source: filepath + "/gamefiles/Hopper/Bird.png"
                        x: parent.width
                        y: 300  // Place the bird at the top of the screen

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
                                if (bird.x < zippyHitBox.x + zippyHitBox.width &&
                                        bird.x + bird.width > zippyHitBox.x &&
                                        bird.y < zippyHitBox.y + zippyHitBox.height &&
                                        bird.y + bird.height > zippyHitBox.y) {
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
