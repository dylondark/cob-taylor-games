/*
    mazeGame.qml

    Main QML file for the Maze game.
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import QMLControllers

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
    property int gameEnum: 6 //Utilities number.

    // Begin game rectangle

}

