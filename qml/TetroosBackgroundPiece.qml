/*
    TetroosBackgroundPiece.qml

    QML file for the tetroos pieces on the background of the Tetroos game.
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import QtQml

Image {
    id: baseImg
    property real startingX: 0
    property real startingY: 0
    property real endingY: 0
    property real pauseDuration: 2000
    property real animDuration: (Math.random() * 10000) + 2000
    opacity: 0
    visible: true

    // base animation for the cycle of the image
    SequentialAnimation {
        running: true
        loops: Animation.Infinite

        // randomly pick a starting x and y and move to random ending y
        ScriptAction {
            script: {
                baseImg.width = Math.random() * (300 * root.scaleFactor) + 50
                baseImg.height = baseImg.width / 2
                // pick starting x between 0 and width
                baseImg.startingX = Math.random() * root.width
                // pick starting y in first half of screen
                baseImg.startingY = Math.random() * root.height / 2
                // pick ending Y in second half of screen
                baseImg.endingY = Math.random() * root.height / 2 + root.height / 2

                // play fade in
                fadeInAnimation.start()
            }
        }

        ParallelAnimation {
            // movement
            PathAnimation {
                id: moveAnimation
                target: baseImg
                path: Path {
                    startX: baseImg.startingX
                    startY: baseImg.startingY
                    PathLine {
                        x: baseImg.startingX
                        y: baseImg.endingY
                    }
                }
                duration: baseImg.animDuration
            }

            // fade out
            SequentialAnimation {
                PauseAnimation {
                    duration: baseImg.animDuration - 1000
                }

                ScriptAction {
                    script: {
                        // play fade out
                        fadeOutAnimation.start()
                    }
                }
            }
        }

        // pause before starting the next cycle
        PauseAnimation {
            duration: baseImg.pauseDuration
        }
    }

    NumberAnimation {
        id: fadeInAnimation
        running: false
        loops: 1
        target: baseImg
        property: "opacity"
        to: 1
        duration: 1000
    }

    NumberAnimation {
        id: fadeOutAnimation
        running: false
        loops: 1
        target: baseImg
        property: "opacity"
        to: 0
        duration: 1000
    }

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
}
