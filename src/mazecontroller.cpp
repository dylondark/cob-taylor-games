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
    // populate board with random wall/passage values (TEMPORARY)
    board = new FlippedArray<std::array<Cell, 20>, 40>;

    for (int y = 0; y < 40; y++)
        for (int x = 0; x < 20; x++)
            (*board)[y][x] = {(bool)(rand() % 2), false};
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
    Starts the maze generation. To be called by QML after entering the game.
*/
void MazeController::startGame()
{
    // Randomized Prim's Algorithm

    // Start with a Grid full of Cells in state Blocked.
    for (int y = 0; y < 40; y++)
        for (int x = 0; x < 20; x++)
            (*board)[y][x] = {true, false};

    // Pick a random Cell, set it to state Passage and Compute its frontier cells.
    // A frontier cell of a Cell is a cell with distance 2 in state Blocked and within the grid.
    int startCellX = rand() % 20;
    int startCellY = rand() % 40;
    (*board)[startCellY][startCellX] = {false, false};
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
