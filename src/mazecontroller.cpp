/*
    mazecontroller.cpp

    Class definition for MazeController.
*/

#include "mazecontroller.h"
#include "qpainter.h"

/*
    Constructor for MazeController.
*/
MazeController::MazeController()
{
    // populate board with empty values
    board = new FlippedArray<std::array<Cell, 20>, 40>;
}

/*
    Destructor for MazeController.
*/
MazeController::~MazeController()
{

}

/*
    Paint a new frame onto the canvas.
*/
void MazeController::paint(QPainter* painter)
{
    painter->setBrush(QBrush(Qt::black));
    painter->drawRect(0, 0, width(), height());
}

/*
    Main game loop. Called every time a new action has happened.
    Calculates the new game state in response to the action and sends the signal to QML to display it.

    MazeAction trigger: what action is triggering the game update.
*/
void MazeController::updateGame(MazeAction trigger)
{
    switch (trigger)
    {
    case MazeAction::Left:
        break;
    case MazeAction::Right:
        break;
    case MazeAction::Up:
        break;
    case MazeAction::Down:
        break;
    case MazeAction::Generate:
        break;
    }

    update();
}
