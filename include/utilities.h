/*
    utilities.h

    Class declaration for MainWindow.
*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <QUrl>

/*
    Utilities namespace

    This namespace is intended to house general utlity constants and functions that can be used by ANY other file in the project
*/
namespace Utilities
{

/*
    Enum for selecting games.
    Named in accordance to the "official game names" from the project standards.
*/
enum game {Trivia = 0, GuessTheLogo = 1, Tetroos = 2, Hopper = 3, Pong = 4, Checkers = 5};

enum errorMessages {FileOpenError, FileWriteError};

/*
    Get the URL of a game QML file to be used in the creation of the game's window/widget.

    Utilities::game game: Game to return the URL for
*/
inline QUrl getGameQML(game game)
{
    switch (game)
    {
    case Trivia:
        return QUrl("qrc:/qml/qml/TriviaGame.qml");
    case GuessTheLogo:
        return QUrl("qrc:/qml/qml/GuessTheLogoGame.qml");
    case Tetroos:
        return QUrl("qrc:/qml/qml/TetroosGame.qml");
    case Hopper:
        return QUrl("qrc:/qml/qml/HopperGame.qml");
    case Pong:
        return QUrl("qrc:/qml/qml/PongGame.qml");
    case Checkers:
        return QUrl("qrc:/qml/qml/CheckersGame.qml");
    default:
        throw "Requested game QML file does not exist yet!"; // TODO: better error handling than throwing a string
    }
}
}

#endif // UTILITIES_H
