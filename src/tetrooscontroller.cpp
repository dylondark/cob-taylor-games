/*
    tetrooscontroller.cpp

    Class definition for TetroosController.
*/

#include "tetrooscontroller.h"

/*
    Constructor for TetroosController.
*/
TetroosController::TetroosController()
    : textures(loadTextures())
{
    // connect gameTimer timeout signal to timerTick slot method
    connect(&gameTimer, &QTimer::timeout, this, &TetroosController::timerTick);

    // connect updateView signal to slot in QML

    // populate board with empty values
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 20; x++)
            board[y][x] = {empty, 0, 0, false, 0, 0}; // empty block
}

/*
    Main game loop. Called every time a new action has happened.
    Calculates the new game state in response to the action and sends the signal to QML to display it.

    GameAction trigger: what action is triggering the game update.
*/
void TetroosController::updateGame(GameAction trigger)
{
    switch (trigger)
    {
    case TimerTick:

        break;
    case Left:

        break;
    case Right:

        break;
    case Down:

        break;
    case Rotate:

        break;
    case Slam:

        break;
    case Hold:

        break;
    }

    // tell QML to update
    emit updateView();
}

/*
    Internal action to move the active piece down one and merge it into the board.

    Returns whether or not the move was successful.
*/
bool mergePieceDown()
{
    // determine current position, rotation and type of active piece
    // get the PieceGrid for the active piece and attempt to merge into the board one down from where the active piece is
    // if it doesn't overlap with another non-silhouetted piece...
    //     erase the active piece from its current position
    //     rewrite the active piece into its new position
    //     return true
    // else
    //     return false
}
