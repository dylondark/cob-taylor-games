/*
    mazecontroller.cpp

    Class definition for MazeController.
*/

#include "mazecontroller.h"
#include "qpainter.h"
#include <QPainter>



// init other data members

/*
    Constructor for MazeController.
*/
MazeController::MazeController()
{
    // populate board with random wall/passage values (TEMPORARY)
    board = new FlippedArray<std::array<Cell, 20>, 40>;

    for (int y = 0; y < 40; y++)
        for (int x = 0; x < 20; x++)
            (*board)[y][x] = {(bool)(rand() % 2), false, x, y};
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
    Starts the maze generation. To be called by QML after entering the game.
*/
void MazeController::startGame()
{
    // Randomized Prim's Algorithm

    // Start with a Grid full of Cells in state Blocked.
    for (int y = 0; y < 40; y++)
        for (int x = 0; x < 20; x++)
            (*board)[y][x].wall = true;

    // Pick a random Cell, set it to state Passage and Compute its frontier cells.
    // A frontier cell of a Cell is a cell with distance 2 in state Blocked and within the grid.
    int startCellX = rand() % 20;
    int startCellY = rand() % 40;
    (*board)[startCellY][startCellX].wall = false;
}


void MazeController::upAction()
{
    // Move piece down
    if (!gameOver)
    {
        // Update game state
        updateGame(MazeAction::Up);
    }
}

/*
    Move piece down action.
*/
void MazeController::downAction()
{
    // Move piece down
    if (!gameOver)
    {
        // Update game state
            updateGame(MazeAction::Down);
    }
}

/*
    Move piece left action.
*/
void MazeController::leftAction()
{
    // Move piece down
    if (!gameOver)
    {
        // Update game state
       updateGame(MazeAction::Left);
    }
}
/*
    Move piece right action.
*/
void MazeController::rightAction()
{
    // Move piece down
    if (!gameOver)
    {
        // Update game state
        updateGame(MazeAction::Right);
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
