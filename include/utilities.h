#ifndef UTILITIES_H
#define UTILITIES_H

#include <QUrl>

// this namespace is intended to house general utlity constants and functions that can be used by ANY other file in the project

namespace Utilities
{
enum game {Trivia = 0, GuessTheLogo = 1, Tetroos = 2, Hopper = 3, Pong = 4, Checkers = 5};

inline QUrl getGameQML(game game)
{
    switch (game)
    {
    case Trivia:
        return QUrl("qrc:/qml/qml/TriviaGame.qml");
    case GuessTheLogo:
        return QUrl("qrc:/qml/qml/GuessTheLogoGame.qml");
    default:
        throw "Requested game QML file does not exist yet!"; // TODO: update this function when more qml files are added
    }
}
}

#endif // UTILITIES_H
