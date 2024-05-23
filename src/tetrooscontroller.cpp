/*
    tetrooscontroller.cpp

    Class definition for TetroosController.
*/

#include <algorithm>
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

    // init other data members
    gameOver = false;
    waitingForNewPiece = true;
    activePiece = {empty, 0, 0, 0, 0};
    holdPiece = empty;
    nextPiece = empty;
    score = 0;

    // start game timer with 1 second interval
    gameTimer.start(1000);

/*
    Returns the current holding piece type (or empty if not holding).
*/
}
unsigned TetroosController::getScore()
{
    return score;
}

/*
    Returns the current holding piece type (or empty if not holding).
*/
PieceType TetroosController::getHoldPiece()
{
    return holdPiece;
}

/*
    Returns the currently active piece type.
*/
PieceType TetroosController::getActivePiece()
{
    return activePiece.pieceType;
}

/*
    Returns the type of the next piece.
*/
PieceType TetroosController::getNextPiece()
{
    return nextPiece;
}

/*
    Move piece down action.
*/
void TetroosController::down()
{
    // Move piece down
    if (!gameOver && !waitingForNewPiece) {
        // Update game state
        updateGame(Down);
    }
}
/*
    Move piece left action.
*/
void TetroosController::left()
{
    // Move piece down
    if (!gameOver && !waitingForNewPiece) {
        // Update game state
        updateGame(Left);
    }
}
/*
    Move piece right action.
*/
void TetroosController::right()
{
    // Move piece down
    if (!gameOver && !waitingForNewPiece) {
        // Update game state
        updateGame(Right);
    }
}

/*
    Rotate piece clockwise action.
*/
void TetroosController::rotate()
{
    // Rotate piece clockwise
    if (!gameOver && !waitingForNewPiece) {
        // Update game state
        updateGame(Rotate);
    }
}

/*
    Slam piece to the bottom action.
*/
void TetroosController::slam()
{
    // Move piece down
    if (!gameOver && !waitingForNewPiece) {
        // Update game state
        updateGame(Slam);
    }
}

/*
    Hold active piece action.
*/
void TetroosController::hold()
{
    // Move piece down
    if (!gameOver && !waitingForNewPiece) {
        // Update game state
        updateGame(Hold);
    }
}


/*
    Main game loop. Called every time a new action has happened.
    Calculates the new game state in response to the action and sends the signal to QML to display it.

    GameAction trigger: what action is triggering the game update.
*/
void TetroosController::updateGame(GameAction trigger)
{
    // do nothing if game over
    if (gameOver)
        return;

    switch (trigger)
    {
    case TimerTick:
        // check if waiting on new piece
        if (waitingForNewPiece)
        {
            spawnNextPiece();
            applySilhouette();
            waitingForNewPiece = false;
        }
        else
        {
            if (mergePieceDown())
                applySilhouette();
            else
            {
                waitingForNewPiece = true;
                return; // no need to trigger a view update since nothing actually happened on the board
            }
        }
        break;
    case Left:
        if (mergePieceLeft())
            applySilhouette();
        else
            return;
        break;
    case Right:
        if (mergePieceRight())
            applySilhouette();
        else
            return;
        break;
    case Down:
        if (mergePieceDown())
            applySilhouette();
        else
        {
            waitingForNewPiece = true;
            return;
        }
        break;
    case Rotate:
        if (mergePieceRotate())
            applySilhouette();
        else
            return;
        break;
    case Slam:
        while (mergePieceDown()); // repeatedly move the piece down until it can't anymore
        waitingForNewPiece = true;
        break;
    case Hold:
        if (swapHold())
            applySilhouette();
        else
            return;
        break;
    }

    // tell QML to update
    emit updateView();
}

/*
    Internal action to move the active piece down one and merge it into the board.

    Returns whether or not the move was successful.
*/
bool TetroosController::mergePieceDown()
{
    // check that the piece isn't going to go out of bounds
    if (activePiece.posY == 0)
        return false;

    // get the PieceGrid for the active piece and check for collision in the place that it will be merged into
    if (!checkActivePieceCollision(activePiece.posX, activePiece.posY - 1))
    {
        rewriteActivePiece(activePiece.posX, --activePiece.posY);
        return true;
    }
    else
        return false;
}

/*
    Internal action to move the active piece left and merge it into the board.

    Returns whether or not the move was successful.
*/
bool TetroosController::mergePieceLeft()
{
    // check that the piece isn't going to go out of bounds
    if (activePiece.posX == 0)
        return false;

    // get the PieceGrid for the active piece and check for collision in the place that it will be merged into
    if (!checkActivePieceCollision(activePiece.posX - 1, activePiece.posY))
    {
        rewriteActivePiece(--activePiece.posX, activePiece.posY);
        return true;
    }
    else
        return false;
}

/*
    Internal action to move the active piece right and merge it into the board.

    Returns whether or not the move was successful.
*/
bool TetroosController::mergePieceRight()
{
    // get the width of the current piece
    unsigned pieceWidth = 0;
    switch (activePiece.pieceType)
    {
    case I:
        pieceWidth = 1;
        break;
    case J:
    case L:
    case O:
        pieceWidth = 2;
        break;
    case S:
    case T:
    case Z:
        pieceWidth = 3;
        break;
    case empty: // active piece should never be empty so this is here just to suppress a warning
        break;
    }

    // check that the piece isn't going to go out of bounds
    if (activePiece.posX + pieceWidth >= 19)
        return false;

    // get the PieceGrid for the active piece and check for collision in the place that it will be merged into
    if (!checkActivePieceCollision(activePiece.posX - 1, activePiece.posY))
    {
        rewriteActivePiece(++activePiece.posX, activePiece.posY);
        return true;
    }
    else
        return false;
}

/*
    Checks that a given piece would not collide with any filled blocks were it to be applied to the board at the provided location.

    unsigned startPosX: X value of the bottom left corner of the grid area on the board.
    unsigned startPosY: Y value of the bottom left corner of the grid area on the board.
    Returns whether there was a collision.
*/
bool TetroosController::checkActivePieceCollision(unsigned startPosX, unsigned startPosY)
{
    // get the grid for the active piece type
    PieceGrid checkPiece = getPieceGrid(activePiece.pieceType, activePiece.rotation);

    unsigned pieceX = 0, pieceY = 0;
    for (unsigned boardY = startPosY; boardY < std::min(startPosY + 5, 20U); boardY++) // use min to ensure we don't go out of bounds
    {
        for (unsigned boardX = startPosX; boardX < std::min(startPosX + 5, 10U); boardX++)
        {
            // get the two blocks we are examining
            Block currentBlockInBoard = board[boardY][boardX];
            bool currentBlockInPiece = checkPiece[pieceY][pieceX];

            if (currentBlockInBoard.pieceType != empty && currentBlockInPiece == true)
                return true;

            ++pieceX;
        }
        ++pieceY;
    }
    return false;
}

/*
    Erases the current active piece and then rewrites it again at the specified coordinates.

    unsigned startPosX: X value of the bottom left corner of the grid area on the board.
    unsigned startPosY: Y value of the bottom left corner of the grid area on the board.
*/
void TetroosController::rewriteActivePiece(unsigned startPosX, unsigned startPosY)
{
    // get the grid for the active piece type
    PieceGrid newPiece = getPieceGrid(activePiece.pieceType, activePiece.rotation);

    unsigned pieceX = 0, pieceY = 0;
    // erase the active piece from its current position
    for (unsigned boardY = startPosY + 1; boardY < std::min(startPosY + 6, 20U); boardY++)
        for (unsigned boardX = startPosX; boardX < std::min(startPosX + 5, 10U); boardX++)
        {
            // get reference to block since we are modifying it
            Block* currentBlockInBoard = &board[boardY][boardX];

            if (currentBlockInBoard->pieceID == activePiece.pieceID)
                // blank the block
                *currentBlockInBoard = {empty, 0, 0, false, 0, 0};
        }

    // rewrite the active piece into its new position
    pieceX = pieceY = 0;
    for (unsigned boardY = startPosY; boardY < std::min(startPosY + 5, 20U); boardY++)
    {
        for (unsigned boardX = startPosX; boardX < std::min(startPosX + 5, 10U); boardX++)
        {
            // get reference to block since we are modifying it
            Block* currentBlockInBoard = &board[boardY][boardX];
            bool currentBlockInPiece = newPiece[pieceY][pieceX];

            if (currentBlockInPiece == true)
                *currentBlockInBoard = {activePiece.pieceType, activePiece.rotation, activePiece.pieceID, false, pieceX, pieceY};

            ++pieceX;
        }
        ++pieceY;
    }
}
