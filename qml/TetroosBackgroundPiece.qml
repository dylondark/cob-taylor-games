/*
    TetroosBackgroundPiece.qml

    QML file for the tetroos pieces on the background of the Tetroos game.
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml

Image {
    id: baseImg
    source: filepath + "/gamefiles/Tetroos/images/I.png"
    property real startingX: 0
    property real startingY: 0
    property real endingY: 0
    property real pauseDuration: 0
    visible: true

    // animation to move the image
    SequentialAnimation {
        running: true
        loops: Animation.Infinite
        // randomly pick a starting x and y and move to random ending y
        ScriptAction {
            script: {
                baseImg.width = Math.random() * (300 * root.scaleFactor) + 50
                baseImg.height = baseImg.width / 2
                baseImg.visible = true
                // pick starting x between 0 and width
                baseImg.startingX = Math.random() * root.width
                // pick starting y in first half of screen
                baseImg.startingY = Math.random() * root.height / 2
                // pick ending Y in second half of screen
                baseImg.endingY = Math.random() * root.height / 2 + root.height / 2
            }
        }

        PathAnimation {
            running: true
            target: baseImg
            path: Path {
                startX: baseImg.startingX
                startY: baseImg.startingY
                PathLine {
                    x: baseImg.startingX
                    y: baseImg.endingY
                }
            }
            duration: Math.random() * 10000 + 2000
        }

        // randomly choose a pause duration before restarting the animation
        ScriptAction {
            script: {
                baseImg.pauseDuration = Math.random() * 5000
                baseImg.visible = false
            }
        }

        PauseAnimation {
            duration: baseImg.pauseDuration
        }
    }
}
