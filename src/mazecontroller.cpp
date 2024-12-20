/*
    mazecontroller.cpp

    Class definition for MazeController.
*/

#include "mazecontroller.h"
#include "qpainter.h"
#include <algorithm>
#include <QPainter>
#include <QBuffer>
#include "tetrooscontroller.h"
#include "cliparser.h"
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
    unsigned cellWidth = this->width() / 20;
    unsigned cellHeight = this->height() / 40;

    // Loop through each cell of the grid and draw them
    for (unsigned row = 0; row < 40; ++row)
    {
        for (unsigned col = 0; col < 20; ++col)
        {
            // Draw each grid cell as a rectangle
            painter->drawRect(col * cellWidth, row * cellHeight, cellWidth, cellHeight);
        }
    }
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
