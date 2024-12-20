/*
    mazecontroller.cpp

    Class definition for MazeController.
*/

#include "mazecontroller.h"
#include "qpainter.h"
#include <QPainter>

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
            // Access the current cell in the board (Assuming board is of type FlippedArray<Cell, 40, 20>)
            Cell& cell = (*board)[row][col];

            // Directly check if the cell is a wall by accessing the wall member
            bool isWall = cell.wall;

            // Set the brush color based on whether it's a wall or not
            if (isWall)
                painter->setBrush(QBrush(Qt::black));
            else
                painter->setBrush(QBrush(Qt::white));

            // Draw the individual grid cell with the appropriate color
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
