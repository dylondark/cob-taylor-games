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
    property int gameEnum: 3

    function endGame() {
        gameBase.visible = false;
        gameOverBase.gameOverOps();
        roundTimer.stop();

        // send signal to put in user's score
        // change score value in label
    }

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
                        loader.addImage("/gamefiles/Hopper/ZippyRun.gif");
                        loader.addImage("/gamefiles/Hopper/Jump.png");
                        loader.addImage("/gamefiles/Hopper/Slide.png");
                        loader.addImage("/gamefiles/Hopper/Sky.png");
                        loader.addImage("/gamefiles/Hopper/Sky2.png");
                        loader.addImage("/gamefiles/Hopper/Sunrise.png");
                        loader.addImage("/gamefiles/Hopper/grass.zippyhopp.jpg");
                    }
                }

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
                            const obstacles = [rockHitbox, birdHitbox, rockCandyHitbox, statueHitbox, clockHitbox, soccerballHitbox, archHitbox, paintedRockHitbox]; // Array of obstacles to check against **ALL OBSTACLES BE INCLUDED**
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
                        } else if (heart1.visible) { // If reduceHearts is called while only one heart is left, the game is over.
                            heart1.visible = false;
                            endGame(); //endGame
                        }

                        // Start the timer after reducing a heart
                        heartTimer.restart();
                    }

                    Image {
                        id: sunriseImage
                        width: 1750 * root.scaleFactor
                        height: 2800 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Sunrise.png" // Initial background
                        opacity: 1
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.verticalStretchFactor: 3
                        asynchronous: true
                    }

                    Image {
                        id: skyImage
                        width: 1750 * root.scaleFactor
                        height: 2800 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Sky.png" // Initial background
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.verticalStretchFactor: 3
                        opacity: 0
                        asynchronous: true

                        Behavior on opacity {
                            NumberAnimation {
                                duration: 3000 // duration of sunset transition
                                easing.type: Easing.InOutQuad // MAKES TRANSITION SMOOTH
                            }
                        }
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
                        interval: 20000 // CHANGE FOR TIME, every 10000 is 10 seconds
                        running: true
                        repeat: false // Only run once
                        onTriggered: {
                            skyImage.visible = true; // Makes sunset visible
                            skyImage.opacity = 1; // Starts the animation
                            gameBase.gameStage = 2;
                            obstacleTimer.interval = 2000;
                            console.log("Game Difficulty has been set to 2");
                        }
                    }

                    Timer {
                        id: stage3Timer
                        interval: 40000 // CHANGE FOR TIME, every 10000 is 10 seconds
                        running: true
                        repeat: false // Only run once
                        onTriggered: {
                            sunsetImage.visible = true; // Makes sunset visible
                            sunsetImage.opacity = 1; // Starts the animation
                            gameBase.gameStage = 3;
                            obstacleTimer.interval = 1500;
                            console.log("Game Difficulty has been set to 3");
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
                            id: cloudAnimation
                            from: rightBar.x
                            to: leftBar.x - 800 * root.scaleFactor
                            duration: 8000  // Adjusts speed
                            loops: 1
                            running: false
                        }
                    }

                    // Secondary Cloud Background Image
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
                            id: cloudAnimation2
                            from: rightBar.x
                            to: leftBar.x - 800 * root.scaleFactor
                            duration: 14000  // Adjusts speed
                            loops: 1
                            running: false
                        }
                    }

                    // Goodyear Blimp
                    Image {
                        id: blimp
                        width: 450 * root.scaleFactor
                        height: 250 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/Blimp.png"
                        opacity: 0.8
                        x: parent.width
                        y: floorRect.y - 2200 * root.scaleFactor
                        asynchronous: true

                        // Animation for cloud movement
                        PropertyAnimation on x {
                            id: blimpAnimation
                            from: rightBar.x
                            to: leftBar.x - 800 * root.scaleFactor
                            duration: 28000  // Adjusts speed
                            loops: 1
                            running: false
                        }
                    }


                    // archPart
                    Image {
                        id: archBack
                        width: 450 * root.scaleFactor
                        height: 950 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/arch.png"
                        x: parent.width
                        y: floorRect.y - height + 150 * root.scaleFactor
                        asynchronous: true

                        // Animation for arch movement
                        PropertyAnimation on x {
                            id: archAnimationBack
                            from: parent.width
                            to: -300
                            duration: 3000 * ((parent.width + 195 * root.scaleFactor) / parent.width)
                            loops: 1
                            running: false
                        }
                    }

                    Rectangle {
                        id: archHitbox
                        width: 300 * root.scaleFactor
                        height: 300 * root.scaleFactor
                        anchors.top: archBack.top
                        anchors.right: archBack.right
                        anchors.topMargin: 10
                        color: "red"
                    }

                    // Zippy Hitboxes
                    Rectangle {
                        id: zippyBHitbox
                        anchors.centerIn: zippyContainer
                        width: 225 * root.scaleFactor
                        height: 550 * root.scaleFactor
                        color: "transparent"
                    }

                    Rectangle {
                        id: zippyHHitbox
                        anchors.top: zippyContainer.top
                        anchors.right: zippyContainer.right
                        anchors.rightMargin: 175 * root.scaleFactor
                        width: 75 * root.scaleFactor
                        height: 300 * root.scaleFactor
                        color: "transparent"
                    }

                    Item {
                        id: zippyContainer
                        width: 850 * root.scaleFactor
                        height: 700 * root.scaleFactor
                        x: (parent.width - width) - 950 * root.scaleFactor
                        y: floorRect.y - height + 125 * root.scaleFactor // Starting position on the floor

                        // Running animation (default)
                        AnimatedImage {
                            id: zippyModel
                            width: 850 * root.scaleFactor
                            height: 700 * root.scaleFactor
                            anchors.fill: parent
                            source: filepath + "/gamefiles/Hopper/ZippyRun.gif"
                            visible: true
                            fillMode: Image.PreserveAspectFit
                        }

                        // Jumping image (hidden by default)
                        Image {
                            id: zippyJump
                            width: 850 * root.scaleFactor
                            height: 700 * root.scaleFactor
                            anchors.fill: parent
                            source: filepath + "/gamefiles/Hopper/Jump.png"
                            visible: false
                            fillMode: Image.PreserveAspectFit
                        }
                        // Sliding image (hidden by default)
                        Image {
                            id: zippySlide
                            width: 850 * root.scaleFactor
                            height: 700 * root.scaleFactor
                            anchors.fill: parent
                            source: filepath + "/gamefiles/Hopper/Slide.png"
                            visible: false
                            fillMode: Image.PreserveAspectFit
                        }

                        // Jump animation
                        SequentialAnimation {
                            id: hopAnimation
                            running: false
                            loops: 1

                            // Switch to zippyJump image
                            PropertyAction { target: zippyModel; property: "visible"; value: false }
                            PropertyAction { target: zippyJump; property: "visible"; value: true }

                            // Makes Zippy Jump
                            PropertyAnimation {
                                target: zippyContainer
                                property: "y"
                                to: floorRect.y - (1200 * root.scaleFactor) // Jump peak
                                duration: 500
                                easing.type: Easing.OutQuad
                            }

                            // Returns Zippy to her original position
                            PropertyAnimation {
                                target: zippyContainer
                                property: "y"
                                to: floorRect.y - zippyModel.height + 50
                                duration: 500
                                easing.type: Easing.InQuad
                            }

                            // Switch Zippy back to the running animation
                            PropertyAction { target: zippyJump; property: "visible"; value: false }
                            PropertyAction { target: zippyModel; property: "visible"; value: true }
                        }
                        // Sliding Animation
                        SequentialAnimation {
                            id: slideAnimation
                            running: false
                            loops: 1

                            // Hide the running image (zippyModel) and show the sliding image (zippySlide)
                            PropertyAction { target: zippyModel; property: "visible"; value: false }
                            PropertyAction { target: zippySlide; property: "visible"; value: true }

                            // Slide effect by squashing the container (zippyContainer) via animating the height
                            PropertyAnimation {
                                target: zippyContainer
                                property: "height"
                                to: zippyContainer.height * 0.75 // Squash vertically to 75% of original height
                                duration: 450
                                easing.type: Easing.OutQuad
                            }

                            // Restore Zippy's container height to normal
                            PropertyAnimation {
                                target: zippyContainer
                                property: "height" // Restore height to original value
                                to: zippyContainer.height // Restore to original height
                                duration: 450
                                easing.type: Easing.InQuad
                            }

                            // Switch Zippy back to the running animation
                            PropertyAction { target: zippySlide; property: "visible"; value: false } // Hide sliding image
                            PropertyAction { target: zippyModel; property: "visible"; value: true } // Show running GIF
                        }




                        // Zippy's Healthbar
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
                    Timer { // Timer for obstacles coming out
                        id: obstacleTimer
                        interval: 3000
                        running: true
                        repeat: true

                        // Variables to track the last obstacle for each game stage
                        property int lastObstacleStage1: 0
                        property int lastObstacleStage2: 0
                        property int lastObstacleStage3: 0

                        onTriggered: {
                            // Generates a random number (change random() * X to # of obstacles)
                            if (gameBase.gameStage === 1) {
                                let obstacleType;
                                do {
                                    obstacleType = Math.floor(Math.random() * 3) + 1;
                                } while (obstacleType === lastObstacleStage1); // Loops until there are no repeat obstacles

                                lastObstacleStage1 = obstacleType; // Updates the most recent obstacle

                                console.log(obstacleType);
                                // Triggers corresponding obstacle
                                if (obstacleType === 1) {
                                    rockAnimation.running = true;
                                } else if (obstacleType === 2) {
                                    statueAnimation.running = true;
                                } else if (obstacleType === 3) {
                                    birdAnimation.running = true;
                                }
                            } else if (gameBase.gameStage === 2) {
                                let obstacleType;
                                do {
                                    obstacleType = Math.floor(Math.random() * 3) + 1;
                                } while (obstacleType === lastObstacleStage2); // Loops until there are no repeat obstacles

                                lastObstacleStage2 = obstacleType; // Updates the most recent obstacle

                                console.log(obstacleType);
                                if (obstacleType === 1) {
                                    rockCandyAnimation.running = true;
                                } else if (obstacleType === 2) {
                                    clockAnimation.running = true;
                                } else if (obstacleType === 3) {
                                    archAnimationFront.running = true;
                                    archAnimationBack.running = true;
                                }
                            } else if (gameBase.gameStage === 3) {
                                let obstacleType;
                                do {
                                    obstacleType = Math.floor(Math.random() * 3) + 1;
                                } while (obstacleType === lastObstacleStage3); // Loops until there are no repeat obstacles

                                lastObstacleStage3 = obstacleType; // Updates the most recent obstacle

                                console.log(obstacleType);
                                if (obstacleType === 1) {
                                    paintedRockAnimation.running = true;
                                } else if (obstacleType === 2) {
                                    clockAnimation.running = true;
                                }
                                else if (obstacleType === 3) {
                                    soccerballAnimation.running = true;
                                }
                            }
                        }
                    }
                    Timer { // Timer for the background decorations (cloud, blimp, etc)
                        id: backgroundTimer
                        interval: 10000
                        running: true
                        repeat: true
                        onTriggered: {
                            // Generates a random number (change random() * X to # of obstacles)
                            let decorationType = Math.floor(Math.random() *3) + 1;
                            //Triggers corresponding decoration
                            console.log(decorationType)
                            if (decorationType === 1) {
                                cloudAnimation.running = true;
                            } else if (decorationType === 2) {
                                cloudAnimation2.running = true;
                            } else if (decorationType === 3) {
                                blimpAnimation.running = true;
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

                    // paintedRock Hitbox
                    Rectangle {
                        id: paintedRockHitbox
                        width: 350 * root.scaleFactor
                        height: 350 * root.scaleFactor
                        anchors.centerIn: paintedRock
                        color: "red"
                    }

                    // paintedRock Obstacle
                    Image {
                        id: paintedRock
                        width: 450 * root.scaleFactor
                        height: 400 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/PaintedRock.png"
                        x: parent.width
                        y: floorRect.y - height + 50
                        asynchronous: true

                        // Animation for rock movement
                        PropertyAnimation on x {
                            id: paintedRockAnimation
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

                    // Clock Obstacle
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
                        width: 370 * root.scaleFactor
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
                        y: 1365 * root.scaleFactor
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

                    Rectangle {
                        id: soccerballHitbox
                        width: 350 * root.scaleFactor
                        height: 350 * root.scaleFactor
                        anchors.centerIn: soccerball
                        color: "red"
                    }

                    Image {
                        id: soccerball
                        width: 350 * root.scaleFactor
                        height: 350 * root.scaleFactor
                        source: filepath + "/gamefiles/Hopper/soccerball.png"
                        x: parent.width
                        y: 1400 * root.scaleFactor
                        asynchronous: true

                        // Combined animation for movement and rotation
                        SequentialAnimation {
                            id: soccerballAnimation
                            running: false
                            loops: 1

                            ParallelAnimation {
                                // Horizontal movement
                                PropertyAnimation {
                                    target: soccerball
                                    property: "x"
                                    from: parent.width
                                    to: -300
                                    duration: 2000 // Adjusts speed
                                }

                                // Rotation
                                PropertyAnimation {
                                    target: soccerball
                                    property: "rotation"
                                    from: 0
                                    to: 720 // Two full rotations
                                    duration: 2000 // Match movement duration
                                }
                            }
                        }
                }
                }

                Image { // archFront // archPart
                    id: archFront
                    width: 450 * root.scaleFactor
                    height: 950 * root.scaleFactor
                    source: filepath + "/gamefiles/Hopper/Arch2.png"
                    x: parent.width
                    y: floorRect.y - height + 365 * root.scaleFactor
                    asynchronous: true

                    // Change this to item with archFront and Back
                    PropertyAnimation on x {
                        id: archAnimationFront
                        from: parent.width + 195 * root.scaleFactor
                        to: -300
                        duration: (parent.width + 195 * root.scaleFactor - (-300)) / (parent.width - (-300)) * archAnimationBack.duration
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
                    Text {
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

                        Text {
                            text: "Hop!"
                            font.pointSize: 70 * root.scaleFactor
                            anchors.centerIn: parent
                        }

                        onClicked: {
                            if (!zippyModel.busy && !hopAnimation.running && !slideAnimation.running) {
                                hopAnimation.start(); // Starts the hop animation
                            }
                        }
                    }

                    Button {
                        id: slideBtn
                        implicitWidth: parent.width
                        implicitHeight: (btnLayout.height - btnLayout.spacing) / 2 // Dynamic height based on layout

                        background: Rectangle {
                            id: slideRect
                            color: "white"
                            opacity: 0.7
                            border.color: "black"
                            radius: 100 * root.scaleFactor
                            anchors.fill: parent
                        }

                        Text {
                            text: "Slide!"
                            font.pointSize: 70 * root.scaleFactor
                            anchors.centerIn: parent
                        }

                        onClicked: {
                            if (!zippyModel.busy && !hopAnimation.running && !slideAnimation.running) {
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
