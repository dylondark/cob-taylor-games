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
                property int gameStage: 1

                QMLImagePreloader {
                    id: loader

                    Component.onCompleted: {
                        // Add images to preload here
                        // DONT add filepath in front of the paths here. It is already done in the C++ code.
                        loader.addImage("/gamefiles/Hopper/Run1.png");
                        loader.addImage("/gamefiles/Hopper/Run2.png");
                        loader.addImage("/gamefiles/Hopper/Jump.png");
                        loader.addImage("/gamefiles/Hopper/Slide.png");
                        loader.addImage("/gamefiles/Hopper/Sky.png");
                        loader.addImage("/gamefiles/Hopper/Sky2.png");
                        loader.addImage("/gamefiles/Hopper/grass.zippyhopp.jpg");
                    }
                }

                // The code for the scores boxes here

                // Begin game rectangle
                Rectangle {
                    id: gameRect
                    width: 1750 * root.scaleFactor
                    height: 2800 * root.scaleFactor
                    anchors.horizontalCenter: parent.horizontalCenter
                    y: (parent.height - height) / 2 - 200 * root.scaleFactor

                    // Function for checking hitbox vs the object in the array
                    function checkCollision(object1, object2) {
                        return object1.x < object2.x + object2.width &&
                                object1.x + object1.width > object2.x &&
                                object1.y < object2.y + object2.height &&
                                object1.y + object1.height > object2.y;
                    }

                    // Function for checking the collision of a hitbox versus an obstacle in an array
                    function checkCollisions(hitboxes, obstaclesArray) {
                        // Check each hitbox against all obstacles
                        for (let i = 0; i < hitboxes.length; i++) {
                            for (let j = 0; j < obstaclesArray.length; j++) {
                                if (checkCollision(hitboxes[i], obstaclesArray[j])) {
                                    return true; // Return true immediately if a collision is detected
                                }
                            }
                        }
                        return false; // No collisions detected
                    }

                    // Timer to check collisions
                    Timer {
                        interval: 32  // Roughly 30 FPS
                        running: true
                        repeat: true
                        onTriggered: {
                            const hitboxes = [zippyHHitbox, zippyBHitbox]; // Array of zippy's two hitboxes
                            const obstacles = [rockHitbox, birdHitbox, rockCandyHitbox, statueHitbox, clockHitbox, duckHitbox]; // Array of obstacles to check against **ALL OBSTACLES BE INCLUDED**
                            if (gameRect.checkCollisions(hitboxes, obstacles)) {
                                    //console.log("Collision detected!");
                                    gameRect.reduceHearts();
                            }
                        }
                    }

                    // Timer to handle the 1-second cooldown
                    Timer {
                        id: heartTimer
                        interval: 1000 // 1 second
                        running: false
                        repeat: false
                    }

                    // Function to reduce hearts
                    function reduceHearts() {
                        if (heartTimer.running) {
                            return; // Skip if the timer is still running
                        }

                        // Check visibility of each heart and hide them one by one
                        if (heart3.visible) {
                            heart3.visible = false;
                        } else if (heart2.visible) {
                            heart2.visible = false;
                        } else if (heart1.visible) {
                            heart1.visible = false;
                        }

                        // Start the timer after reducing a heart
                        heartTimer.restart();
                    }


                    Image {
                        id: skyImage
                        width: 1750 * root.scaleFactor
                        height: 2800 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Sky.png" // Initial background
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.verticalStretchFactor: 3
                        asynchronous: true
                    }

                    Image {
                        id: sunsetImage
                        width: 1750 * root.scaleFactor
                        height: 2800 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Sky2.png" // Second background
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.verticalStretchFactor: 3
                        opacity: 0 // Starts at 0 opacity for transition
                        visible: false // Starts invisible
                        asynchronous: true

                        Behavior on opacity {
                            NumberAnimation {
                                duration: 3000 // duration of sunset transition
                                easing.type: Easing.InOutQuad // MAKES TRANSITION SMOOTH
                            }
                        }
                    }

                    Timer {
                        id: stage2Timer
                        interval: 15000 // CHANGE FOR TIME, every 10000 is 10 seconds
                        running: true
                        repeat: false // Only run once
                        onTriggered: {
                            sunsetImage.visible = true; // Makes sunset visible
                            sunsetImage.opacity = 1; // Starts the animation
                            gameBase.gameStage = 2;
                            obstacleTimer.interval = 2000;
                            console.log("Game Difficulty has been set to 2");
                        }
                    }

                    // Floor Rectangle for Zippy to run on
                    Image {
                        id: floorRect
                        width: 1750 * root.scaleFactor
                        height: 600 * root.scaleFactor
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.verticalStretchFactor: 1
                        anchors.bottom: parent.bottom
                        source: filepath + "/gamefiles/Hopper/grass.zippyhopp.jpg"
                        asynchronous: true


                    }
                    // Cloud Background Image
                    Image {
                        id: cloud
                        width: 650 * root.scaleFactor
                        height: 650 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Cloud.png"
                        opacity: 0.6
                        x: parent.width
                        y: floorRect.y - 1540 * root.scaleFactor  // Cloud in the sky
                        asynchronous: true

                        // Animation for cloud movement
                        PropertyAnimation on x {
                            from: rightBar.x
                            to: leftBar.x - 800 * root.scaleFactor
                            duration: 8000  // Adjusts speed
                            loops: Animation.Infinite
                            running: true
                        }
                    }

                    Image {
                        id: cloud2
                        width: 650 * root.scaleFactor
                        height: 450 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Cloud2.png"
                        opacity: 0.4
                        x: parent.width
                        y: floorRect.y - 2140 * root.scaleFactor  // Cloud in the sky
                        asynchronous: true

                        // Animation for cloud movement
                        PropertyAnimation on x {
                            from: rightBar.x
                            to: leftBar.x - 800 * root.scaleFactor
                            duration: 14000  // Adjusts speed
                            loops: Animation.Infinite
                            running: true
                        }
                    }

                    Image {
                        id: blimp
                        width: 450 * root.scaleFactor
                        height: 250 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Blimp.png"
                        opacity: 0.8
                        x: parent.width
                        y: floorRect.y - 2200 * root.scaleFactor  // Blimp in the sky
                        asynchronous: true

                        // Animation for cloud movement
                        PropertyAnimation on x {
                            from: rightBar.x
                            to: leftBar.x - 800 * root.scaleFactor
                            duration: 28000  // Adjusts speed
                            loops: Animation.Infinite
                            running: true
                        }
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
                        anchors.right: zippyModel.right
                        anchors.rightMargin: 175 * root.scaleFactor
                        width: 75 * root.scaleFactor
                        height: 300 * root.scaleFactor
                        color: "red"
                    }

                    // Zippy Model
                    Image {
                        id: zippyModel
                        width: 850 * root.scaleFactor
                        height: 700 * root.scaleFactor
                        x: (parent.width - width) - 950 * root.scaleFactor
                        y: floorRect.y - height + 50 // Starting position on the floor
                        asynchronous: true

                        property bool isRunning: true

                        // Animation for zippy running that changes every 500 ticks
                        source: loader.getImage(isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png")
                        fillMode: Image.PreserveAspectFit
                        smooth: true // turn off if performance is bad
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

                            PropertyAction { target: zippyModel; property: "source"; value: loader.getImage("/gamefiles/Hopper/Jump.png") } // Sets image to Jump.png at start
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

                            PropertyAction { target: zippyModel; property: "source"; value: loader.getImage("/gamefiles/Hopper/Slide.png") } // Sets image to Slide.png at start
                            PropertyAction { target: runTimer; property: "running"; value: false } // Stops the Timer


                            PropertyAnimation { to: 400 * root.scaleFactor; duration: 300; easing.type: Easing.OutQuad } // Duck down
                            PropertyAnimation { to: 700 * root.scaleFactor; duration: 300; easing.type: Easing.InQuad } // Return to original height

                            PropertyAction { target: runTimer; property: "running"; value: true }
                            PropertyAction { target: zippyModel; property: "source"; value: loader.getImage(zippyModel.isRunning ? "/gamefiles/Hopper/Run1.png" : "/gamefiles/Hopper/Run2.png") }
                        }

                        Row {
                            spacing: 10 * root.scaleFactor // Adjust spacing between hearts
                            anchors.top: zippyModel.top
                            anchors.horizontalCenter: zippyModel.horizontalCenter
                            anchors.topMargin: -200 * root.scaleFactor

                            Image {
                                id: heart1
                                source: filepath + "/gamefiles/Hopper/ZippyHeart.png"
                                width: 200 * root.scaleFactor
                                height: 200 * root.scaleFactor
                                asynchronous: true
                            }

                            Image {
                                id: heart2
                                source: filepath + "/gamefiles/Hopper/ZippyHeart.png"
                                width: 200 * root.scaleFactor
                                height: 200 * root.scaleFactor
                                asynchronous: true
                            }

                            Image {
                                id: heart3
                                source: filepath + "/gamefiles/Hopper/ZippyHeart.png"
                                width: 200 * root.scaleFactor
                                height: 200 * root.scaleFactor
                                asynchronous: true
                            }
                        }
                    }



                    Timer { // Timer for obstacles coming out
                        id: obstacleTimer
                        interval: 3000
                        running: true
                        repeat: true
                        onTriggered: {
                            // Generates a random number (change random() * X to # of obstacles)
                            if (gameBase.gameStage === 1) {
                                let obstacleType = Math.floor(Math.random() *3) + 1;
                                console.log(obstacleType)
                                //Triggers corresponding obstacle
                                if (obstacleType === 1) {
                                    rockAnimation.running = true;
                                } else if (obstacleType === 2) {
                                    statueAnimation.running = true;
                                } else if (obstacleType === 3) {
                                    birdAnimation.running = true;
                                }
                            }
                            else if (gameBase.gameStage === 2) {
                                let obstacleType = Math.floor(Math.random() * 3) + 1;
                                console.log(obstacleType)
                                if (obstacleType === 1 ) {
                                    rockCandyAnimation.running = true;
                                } else if (obstacleType === 2) {
                                    clockAnimation.running = true;
                                } else if (obstacleType === 3) {
                                    duckAnimation.running = true;
                                }
                            }
                        }
                    }

                    // Rock Hitbox
                    Rectangle {
                        id: rockHitbox
                        width: 350 * root.scaleFactor
                        height: 350 * root.scaleFactor
                        anchors.centerIn: rock
                        color: "red"
                    }
                    // Rock Obstacle
                    Image {
                        id: rock
                        width: 450 * root.scaleFactor
                        height: 400 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Rock.png"
                        x: parent.width
                        y: floorRect.y - height + 50
                        asynchronous: true

                        // Animation for rock movement
                        PropertyAnimation on x {
                            id: rockAnimation
                            from: parent.width
                            to: -300
                            duration: 2750  // Adjusts speed
                            loops: 1
                            running: false
                        }
                    }

                    // statue Obstacle
                    Rectangle {
                        id: statueHitbox
                        width: 150 * root.scaleFactor
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
                        y: floorRect.y - height + 50
                        asynchronous: true

                        // Animation for statue movement
                        PropertyAnimation on x {
                            id: statueAnimation
                            from: parent.width
                            to: -300
                            duration: 3000  // Adjusts speed
                            loops: 1
                            running: false
                        }
                    }

                    // rockCandy Obstacle
                    Rectangle {
                        id: rockCandyHitbox
                        width: 150 * root.scaleFactor
                        height: 500 * root.scaleFactor
                        anchors.centerIn: rockCandy
                        color: "red" // was red
                    }

                    Image {
                        id: rockCandy
                        width: 200 * root.scaleFactor
                        height: 500 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/rockCandy.png"
                        x: parent.width
                        y: floorRect.y - height + 50
                        asynchronous: true

                        // Animation for rockCandy movement
                        PropertyAnimation on x {
                            id: rockCandyAnimation
                            from: parent.width
                            to: -300
                            duration: 3000  // Adjusts speed
                            loops: 1
                            running: false
                        }
                    }

                    // clock Obstacle
                    Rectangle {
                        id: clockHitbox
                        width: 125 * root.scaleFactor
                        height: 500 * root.scaleFactor
                        anchors.centerIn: clock
                        color: "red"
                    }

                    Image {
                        id: clock
                        width: 200 * root.scaleFactor
                        height: 500 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/clock.png"
                        x: parent.width
                        y: floorRect.y - height + 50
                        asynchronous: true

                        // Animation for clock movement
                        PropertyAnimation on x {
                            id: clockAnimation
                            from: parent.width
                            to: -300
                            duration: 3000  // Adjusts speed
                            loops: 1
                            running: false
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
                        y: 1200 * root.scaleFactor
                        asynchronous: true

                        // Animation for bird movement
                        PropertyAnimation on x {
                            id: birdAnimation
                            from: parent.width
                            to: -300
                            duration: 3000  // Adjusts speed
                            loops: 1
                            running: false
                        }
                    }
                }
                // duck Hitbox
                    Rectangle {
                        id: duckHitbox
                        width: 450 * root.scaleFactor
                        height: 400 * root.scaleFactor
                        anchors.centerIn: duck
                        color: "red"
                }
                // duck Obstacle
                    Image {
                        id: duck
                        width: 450 * root.scaleFactor
                        height: 400 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/duck.png"
                        x: parent.width
                        y: floorRect.y - height - 90
                        asynchronous: true

                    // Animation for duck movement
                        PropertyAnimation on x {
                            id: duckAnimation
                            from: parent.width
                            to: -300
                            duration: 2750  // Adjusts speed
                            loops: 1
                            running: false
                    }
                }

                // Blocks obstacles on left side
                Rectangle {
                    id: leftBar
                    width: (parent.width - gameRect.width) / 2
                    height: parent.height
                    anchors.left: parent.left
                    anchors.top: parent.top
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#f3a469" }
                        GradientStop { position: 1.0; color: "#3f51b1" }
                    }
                }

                // Blocks obstacles on right side
                Rectangle {
                    id: rightBar
                    width: (parent.width - gameRect.width) / 2
                    height: parent.height
                    anchors.right: parent.right
                    anchors.top: parent.top
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#f3a469" }
                        GradientStop { position: 1.0; color: "#3f51b1" }
                    }
                }
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


                    // Displays the Timer measuring the time elapsed
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
                            anchors.centerIn: parent.center
                        }

                        onClicked: {
                            if (!hopAnimation.running) {
                                hopAnimation.start(); // Starts the hop animation
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
                            anchors.centerIn: parent.center
                        }

                        onClicked: {
                            if (!slideAnimation.running) {
                                slideAnimation.start(); // Starts the slide animation
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
