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
    // seed rng
    srand(time(NULL));

    // populate board with random wall/passage values (TEMPORARY)
    board = new FlippedArray<std::array<Cell, BOARD_WIDTH>, BOARD_HEIGHT>;

    for (int y = 0; y < BOARD_HEIGHT; y++)
        for (int x = 0; x < BOARD_WIDTH; x++)
            (*board)[y][x] = {(bool)(rand() % 2), false, x, y};

    startGame();
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
    unsigned cellWidth = this->width() / BOARD_WIDTH;
    unsigned cellHeight = this->height() / BOARD_HEIGHT;

    // Loop through each cell of the grid and draw them
    for (unsigned row = 0; row < BOARD_HEIGHT; ++row)
    {
        for (unsigned col = 0; col < BOARD_WIDTH; ++col)
        {
            // Access the current cell in the board (Assuming board is of type FlippedArray<Cell, BOARD_HEIGHT, BOARD_WIDTH>)
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
    for (int y = 0; y < BOARD_HEIGHT; y++)
        for (int x = 0; x < BOARD_WIDTH; x++)
            (*board)[y][x].wall = true;

    // Pick a random Cell, set it to state Passage and Compute its frontier cells.
    // A frontier cell of a Cell is a cell with distance 2 in state Blocked and within the grid.
    int startCellX = rand() % BOARD_WIDTH;
    int startCellY = rand() % BOARD_HEIGHT;
    (*board)[startCellY][startCellX].wall = false;
    calculateFrontierCells((*board)[startCellY][startCellX]);

    // While the list of frontier cells is not empty:
    while (!frontierCells.empty())
    {
        // Pick a random frontier cell from the list of frontier cells.
        int frontierCellIndex = rand() % frontierCells.size();
        Cell* frontierCell = frontierCells[frontierCellIndex];

        // Let neighbors(frontierCell) = All cells in distance 2 in state Passage.
        std::vector<Cell*> neighbors;
        if (frontierCell->y + 2 < BOARD_HEIGHT && !((*board)[frontierCell->y + 2][frontierCell->x].wall))
            neighbors.push_back(&(*board)[frontierCell->y + 2][frontierCell->x]);
        if (frontierCell->y - 2 >= 0 && !((*board)[frontierCell->y - 2][frontierCell->x].wall))
            neighbors.push_back(&(*board)[frontierCell->y - 2][frontierCell->x]);
        if (frontierCell->x + 2 < BOARD_WIDTH && !((*board)[frontierCell->y][frontierCell->x + 2].wall))
            neighbors.push_back(&(*board)[frontierCell->y][frontierCell->x + 2]);
        if (frontierCell->x - 2 >= 0 && !((*board)[frontierCell->y][frontierCell->x - 2].wall))
            neighbors.push_back(&(*board)[frontierCell->y][frontierCell->x - 2]);

        if (neighbors.empty())
        {
            // Remove the chosen frontier cell from the list of frontier cells.
            frontierCells.erase(frontierCells.begin() + frontierCellIndex);
            continue;
        }

        // Pick a random neighbor and connect the frontier cell with the neighbor by setting the cell in-between to state Passage.
        int neighborIndex = rand() % neighbors.size();
        Cell* neighbor = neighbors[neighborIndex];
        int wallX = (frontierCell->x + neighbor->x) / 2;
        int wallY = (frontierCell->y + neighbor->y) / 2;
        (*board)[wallY][wallX].wall = false;

        // Compute the frontier cells of the chosen frontier cell and add them to the frontier list.
        calculateFrontierCells(*frontierCell);

        // make the current frontier cell a passage
        frontierCell->wall = false;

        // Remove the chosen frontier cell from the list of frontier cells.
        frontierCells.erase(frontierCells.begin() + frontierCellIndex);
    }

    update();
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
    if (cell.y + 2 < BOARD_HEIGHT && (*board)[cell.y + 2][cell.x].wall)
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
    if (cell.x + 2 < BOARD_WIDTH && (*board)[cell.y][cell.x + 2].wall)
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
