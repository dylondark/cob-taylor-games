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
}

/*
    Main game loop. Called every time a new action has happened.
    Calculates the new game state in response to the action and sends the signal to QML to display it.

    GameAction trigger: what action is triggering the game update.
*/
void TetroosController::updateGame(GameAction trigger)
{

}
