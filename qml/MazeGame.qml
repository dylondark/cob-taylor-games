/*
    MazeGame.qml

    Main QML file for the Maze game.
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
    property string strName: "Maze"
    property string username: ""
    property int gameEnum: 0 //Utilities number.

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
                     GradientStop { position: 0.0; color: "#f7c978" }
                     GradientStop { position: 1.0; color: "#f18271" }
                 }

            PreviewBase {
                id: preview

                anchors.fill: parent

                logoSource: filepath + "/menufiles/Maze.png"
                conceptSource: filepath + "/gamefiles/Checkers/CheckersInGamePreview.png"
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
