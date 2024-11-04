/*
    utilities.h

    Class declaration for MainWindow.
*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <QUrl>
#include <QMessageBox>
#include <iostream>

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

inline void throwError(errorMessages error, QWidget* parent = nullptr)
{
    QString message;
    switch (error)
    {
    case FileOpenError:
        message = "An error occurred while attempting to read a necessary file.\nCheck that the necessary directories are present in the executable directory and/or that the -p CLI argument is correct.\n";
        QMessageBox::critical(parent, "cob-taylor-games - File Read Error", message);
        break;
    case FileWriteError:
        message = "An error ocurred while attempting to write to a file.\nCheck that the necessary files are in the correct location and have sufficient permissions.\n";
        QMessageBox::critical(parent, "cob-taylor-games - File Write Error", message);
        break;
    default:
        message = "An unknown error ocurred.\n";
        QMessageBox::critical(parent, "cob-taylor-games - Unknown Error", message);
    }

    std::cerr << message.toStdString();
    std::exit(1);
}
}

#endif // UTILITIES_H
