/*
    utilities.h

    Class declaration for MainWindow.
*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <QUrl>
#include <QMessageBox>

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

enum errorMessages {FileOpenError, FileWriteError, QMLNotFoundError};

/*
    Get the URL of a game QML file to be used in the creation of the game's window/widget.

    Utilities::game game: Game to return the URL for
*/
QUrl getGameQML(game game);

void throwError(errorMessages error, QString file = "", QWidget* parent = nullptr);
}

#endif // UTILITIES_H
