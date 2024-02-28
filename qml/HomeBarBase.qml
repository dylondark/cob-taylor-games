import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
import Qt5Compat.GraphicalEffects
import QMLControllers
import QtQuick.VirtualKeyboard 2.15

Rectangle {
    id: homeBarBase
    color: "black"

    RowLayout {
        spacing: 140

        Button {
            id: backButton
            text: "Back button"
        }

        Label {
            id: userNameTxt
            color: "white"
            text: "Username here"
            horizontalAlignment: Label.AlignRight
        }

        Label {
            id: pointCounter
            color: "white"
            text: "Points here"
            horizontalAlignment: Label.AlignRight
        }
    }
}
