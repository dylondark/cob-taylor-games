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
