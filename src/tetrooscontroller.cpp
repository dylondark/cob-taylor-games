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
    return rewriteActivePiece(0, -1, false);
}

/*
    Internal action to move the active piece left and merge it into the board.

    Returns whether or not the move was successful.
*/
bool TetroosController::mergePieceLeft()
{
    return rewriteActivePiece(-1, 0, false);
}

/*
    Internal action to move the active piece right and merge it into the board.

    Returns whether or not the move was successful.
*/
bool TetroosController::mergePieceRight()
{
    return rewriteActivePiece(1, 0, false);
}

/*
    Internal action to rotate the active piece clockwise and merge it into the board.

    Returns whether or not the rotate was successful.
*/
bool TetroosController::mergePieceRotate()
{

}

/*
    Checks that a given piece would not collide with any filled blocks were it to be applied to the board at the provided location.

    unsigned startPosX: X value of the bottom left corner of the grid area on the board.
    unsigned startPosY: Y value of the bottom left corner of the grid area on the board.
    bool rotate: whether to rotate the piece 90 degrees clockwise before checking.
    Returns whether there was a collision.
*/
bool TetroosController::checkActivePieceCollision(unsigned startPosX, unsigned startPosY, bool rotate)
{
    // start by checking if startpos values are out of the desired range
    if (startPosY >= 20 || startPosX >= 10) // must be 0-19 for Y and 0-9 for X, if it goes below 0 it will wrap over to 4bil because unsigned
        return false;

    // get the grid for the active piece type
    PieceGrid checkPiece = getPieceGrid(activePiece.pieceType, activePiece.rotation + rotate);

    // get the max width of the check piece and ensure it doesnt go out of bounds
    unsigned maxWidth = 4;
    bool isBlockInColumn = false;
    for (unsigned x = 0; x < 4; x++)
    {
        for (unsigned y = 0; y < 4; y++)
        {
            if (checkPiece[y][x] == true)
            {
                isBlockInColumn = true;
                break;
            }
        }
        if (!isBlockInColumn)
        {
            maxWidth = x;
            break;
        }
    }
    if (maxWidth > 20U - startPosX)
        return false;

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

    int xOffset: number to offset the X value of the piece by (it gets added to the piece's current X).
    int yOffset: number to offset the Y value of the piece by (it gets added to the piece's current Y).
    bool rotate: whether to rotate the piece 90 degrees clockwise.
    Returns whether the rewrite was a success.
*/
bool TetroosController::rewriteActivePiece(int xOffset, int yOffset, bool rotate)
{
    unsigned startPosX = (int)activePiece.posX + xOffset;
    unsigned startPosY = (int)activePiece.posY + yOffset;

    // check if we can do the rewrite
    if (!checkActivePieceCollision(startPosX, startPosY, rotate))
        return false;

    // get the grid for the active piece type
    PieceGrid newPiece = getPieceGrid(activePiece.pieceType, activePiece.rotation + rotate);

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

    // update the position values of the active piece
    activePiece.posX = startPosX;
    activePiece.posY = startPosY;

    return true;
}
