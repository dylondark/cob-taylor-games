/*
    utilities.cpp

    Implementation for Utilities namespace.
*/

#include "utilities.h"
#include <iostream>

/*
    Get the URL of a game QML file to be used in the creation of the game's window/widget.

    Utilities::game game: Game to return the URL for
*/
QUrl Utilities::getGameQML(game game)
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
        Utilities::throwError(QMLNotFoundError);
    }
}

void Utilities::throwError(errorMessages error, QWidget* parent)
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
    case QMLNotFoundError:
        message = "An error ocurred while attempting to load a QML file that doesn't exist.\nCheck your usage of the Utilities::getGameQML() function.\n";
        QMessageBox::critical(parent, "cob-taylor-games - QML File Not Found Error", message);
        break;
    default:
        message = "An unknown error ocurred.\n";
        QMessageBox::critical(parent, "cob-taylor-games - Unknown Error", message);
    }

    std::cerr << message.toStdString();
    std::exit(1);
}

