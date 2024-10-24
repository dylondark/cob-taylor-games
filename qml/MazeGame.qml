import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml 2.15

Item {
    id: root
    width: 2160
    height: 3840

    signal quit
    signal saveScore(int game, string username, int score)

    property real scaleFactor: height / 3840
    property int points: 0
    property string strName: "Maze"
    property string username: ""
    property int gameEnum: 0
    property int moves: 0
    property int timer: 0

    // Dark blue background
    Rectangle {
        id: background
        anchors.fill: parent
        color: "#001f3f" // Dark blue background
    }

    ColumnLayout {
        id: baseLayout
        anchors.fill: parent
        spacing: 20 * scaleFactor

        // Time and Moves buttons at the upper middle side
        RowLayout {
            id: statusLayout
            Layout.fillWidth: true
            Layout.preferredHeight: 100 * scaleFactor
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter // Align top and center horizontally
            spacing: 20 * scaleFactor

            // Time button with custom style
            Rectangle {
                width: 200 * scaleFactor
                height: 80 * scaleFactor
                radius: 15 * scaleFactor
                color: "#005f99" // Aesthetic color
                border.color: "#003366"
                border.width: 3
                Text {
                    anchors.centerIn: parent
                    text: "Time: " + timer
                    font.pixelSize: 40 * scaleFactor
                    color: "white"
                }
            }

            // Moves button with custom style
            Rectangle {
                width: 200 * scaleFactor
                height: 80 * scaleFactor
                radius: 15 * scaleFactor
                color: "#005f99"
                border.color: "#003366"
                border.width: 3
                Text {
                    anchors.centerIn: parent
                    text: "Moves: " + moves
                    font.pixelSize: 40 * scaleFactor
                    color: "white"
                }
            }
        }

        // Maze grid layout (center of screen)
        GridLayout {
            id: mazeGrid
            Layout.fillHeight: true
            Layout.fillWidth: true
            columns: 10

            Repeater {
                model: 100 // Number of cells in the grid
                Rectangle {
                    width: parent.width / mazeGrid.columns
                    height: parent.height / mazeGrid.columns
                    color: model.index % 2 === 0 ? "#ffffff" : "#000000"
                    border.color: "#000000"
                    anchors.margins: 5 * scaleFactor
                }
            }
        }

        // Start button at the bottom center (Bigger than rest) with custom style
        RowLayout {
            id: startButtonLayout
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom

            Rectangle {
                width: 300 * scaleFactor
                height: 100 * scaleFactor
                radius: 20 * scaleFactor
                color: "#00cc66" // Start button green
                border.color: "#008040"
                border.width: 3
                Text {
                    anchors.centerIn: parent
                    text: "Start"
                    font.pixelSize: 60 * scaleFactor
                    color: "white"
                }
            }
        }

        // Directional buttons (bottom-right corner) with custom style
        GridLayout {
            id: controlsLayout
            columns: 3
            Layout.preferredHeight: 300 * scaleFactor
            Layout.preferredWidth: 300 * scaleFactor
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom // Aligning the directional pad to bottom-right corner
            //spacing: 10 * scaleFactor

            Item { } // Empty for top-left

            Rectangle {
                width: 80 * scaleFactor
                height: 80 * scaleFactor
                radius: 10 * scaleFactor
                color: "#3366cc"
                border.color: "#003399"
                border.width: 3
                Text {
                    anchors.centerIn: parent
                    text: "Up"
                    font.pixelSize: 30 * scaleFactor
                    color: "white"
                }
            }

            Item { } // Empty for top-right

            Rectangle {
                width: 80 * scaleFactor
                height: 80 * scaleFactor
                radius: 10 * scaleFactor
                color: "#3366cc"
                border.color: "#003399"
                border.width: 3
                Text {
                    anchors.centerIn: parent
                    text: "Left"
                    font.pixelSize: 30 * scaleFactor
                    color: "white"
                }
            }

            Rectangle {
                width: 80 * scaleFactor
                height: 80 * scaleFactor
                radius: 10 * scaleFactor
                color: "#3366cc"
                border.color: "#003399"
                border.width: 3
                Text {
                    anchors.centerIn: parent
                    text: "Down"
                    font.pixelSize: 30 * scaleFactor
                    color: "white"
                }
            }

            Rectangle {
                width: 80 * scaleFactor
                height: 80 * scaleFactor
                radius: 10 * scaleFactor
                color: "#3366cc"
                border.color: "#003399"
                border.width: 3
                Text {
                    anchors.centerIn: parent
                    text: "Right"
                    font.pixelSize: 30 * scaleFactor
                    color: "white"
                }
            }
        }
    }
}
