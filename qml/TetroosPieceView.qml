import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml

Rectangle {
    id: base
    color: "#fff7e9"

    property string labelText: "unset"
    property var fontFamily
    property var fontPointSize
    property var fontBold
    property var fontColor

    function setPiece(piece) {
        switch (piece) {
        case 'I':
            pieceImg.source = filepath + "/gamefiles/Tetroos/images/I.png";
            break;
        case 'J':
            pieceImg.source = filepath + "/gamefiles/Tetroos/images/J.png";
            break;
        case 'L':
            pieceImg.source = filepath + "/gamefiles/Tetroos/images/L.png";
            break;
        case 'O':
            pieceImg.source = filepath + "/gamefiles/Tetroos/images/O.png";
            break;
        case 'S':
            pieceImg.source = filepath + "/gamefiles/Tetroos/images/S.png";
            break;
        case 'T':
            pieceImg.source = filepath + "/gamefiles/Tetroos/images/T.png";
            break;
        case 'Z':
            pieceImg.source = filepath + "/gamefiles/Tetroos/images/Z.png";
            break;
        default:
            pieceImg.source = "";
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10 * root.scaleFactor

        Label {
            id: label
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.verticalStretchFactor: 1
            text: base.labelText
            horizontalAlignment: Text.AlignHCenter
            font.family: base.fontFamily
            font.pointSize: base.fontPointSize
            font.bold: base.fontBold
            color: base.fontColor
            background: Rectangle {
                color: "#041e42"
            }
        }

        Rectangle {
            id: pieceImgBg
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.verticalStretchFactor: 4
            color: "#ffffff"
            border.color: "black"
            border.width: 1


            Image {
                id: pieceImg
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                smooth: false
                asynchronous: true
                source: ""
            }
        }
    }
}
