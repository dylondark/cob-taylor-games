/*
    PongGame.qml

    A preview of Zoccer, our Pong clone. Will be expanded later.
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
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
    property string strName: "Pong"
    property string username: ""
    property int gameEnum: 0 // Utilities number.

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
                GradientStop { position: 0.0; color: "#a86aa4" }
                GradientStop { position: 1.0; color: "#f3a469" }
                }

            PreviewBase {
                id: preview

                anchors.fill: parent

                logoSource: filepath + "/menufiles/PongMotionPreview.png"
                conceptSource: filepath + "/gamefiles/Zoccer/Zoccer.png"
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
