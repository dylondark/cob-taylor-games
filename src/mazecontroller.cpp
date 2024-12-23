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
    // seed rng
    srand(time(NULL));

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
    delete board;
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
    calculateFrontierCells((*board)[startCellY][startCellX]);
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

/*
    Calculates all frontier cells at a given cell and adds them to frontierCells.
*/
void MazeController::calculateFrontierCells(const Cell& cell)
{
    // Check all cells in 4 cardinal directions from the given cell and 2 away
    // If the cell is within the grid and is a wall, add it to frontierCells
    // If the cell is already in frontierCells, don't add it again

    // north cell
    if (cell.y + 2 >= 0 && (*board)[cell.y + 2][cell.x].wall)
    {
        // Check if the cell is already in frontierCells
        bool alreadyInFrontier = false;
        for (const Cell* frontierCell : frontierCells)
        {
            if (frontierCell->x == cell.x && frontierCell->y == cell.y - 2)
            {
                alreadyInFrontier = true;
                break;
            }
        }

        // If the cell is not already in frontierCells, add it
        if (!alreadyInFrontier)
        {
            frontierCells.push_back(&(*board)[cell.y + 2][cell.x]);
        }
    }

    // south cell
    if (cell.y - 2 >= 0 && (*board)[cell.y - 2][cell.x].wall)
    {
        // Check if the cell is already in frontierCells
        bool alreadyInFrontier = false;
        for (const Cell* frontierCell : frontierCells)
        {
            if (frontierCell->x == cell.x && frontierCell->y == cell.y - 2)
            {
                alreadyInFrontier = true;
                break;
            }
        }

        // If the cell is not already in frontierCells, add it
        if (!alreadyInFrontier)
        {
            frontierCells.push_back(&(*board)[cell.y - 2][cell.x]);
        }
    }

    // east cell
    if (cell.x + 2 >= 0 && (*board)[cell.y][cell.x + 2].wall)
    {
        // Check if the cell is already in frontierCells
        bool alreadyInFrontier = false;
        for (const Cell* frontierCell : frontierCells)
        {
            if (frontierCell->x == cell.x + 2 && frontierCell->y == cell.y)
            {
                alreadyInFrontier = true;
                break;
            }
        }

        // If the cell is not already in frontierCells, add it
        if (!alreadyInFrontier)
        {
            frontierCells.push_back(&(*board)[cell.y][cell.x + 2]);
        }
    }

    // west cell
    if (cell.x - 2 >= 0 && (*board)[cell.y][cell.x - 2].wall)
    {
        // Check if the cell is already in frontierCells
        bool alreadyInFrontier = false;
        for (const Cell* frontierCell : frontierCells)
        {
            if (frontierCell->x == cell.x - 2 && frontierCell->y == cell.y)
            {
                alreadyInFrontier = true;
                break;
            }
        }

        // If the cell is not already in frontierCells, add it
        if (!alreadyInFrontier)
        {
            frontierCells.push_back(&(*board)[cell.y][cell.x - 2]);
        }
    }
}
