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
    // check that the piece isn't going to go out of bounds
    if (activePiece.posY == 0)
        return false;

    // get the PieceGrid for the active piece and check for collision in the place that it will be merged into
    PieceGrid newPiece = getPieceGrid(activePiece.pieceType, activePiece.rotation);
    unsigned startPosX = activePiece.posX, startPosY = activePiece.posY - 1;
    unsigned pieceX = 0, pieceY = 0;
    bool collision = false;
    for (unsigned boardY = startPosY; boardY < std::min(startPosY + 5, 20U); boardY++) // use min to ensure we don't go out of bounds
    {
        for (unsigned boardX = startPosX; boardX < std::min(startPosX + 5, 10U); boardX++)
        {
            // get the two blocks we are examining
            Block currentBlockInBoard = board[boardY][boardX];
            bool currentBlockInPiece = newPiece[pieceY][pieceX];

            if (currentBlockInBoard.pieceType != empty && currentBlockInPiece == true)
            {
                collision = true;
                goto endloop; // exit both loops, no need to continue evaluating
            }

            ++pieceX;
        }
        ++pieceY;
    }
endloop:

    // if it doesn't overlap with another non-silhouetted piece...
    if (!collision)
    {
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
        pieceX = 0;
        pieceY = 0;
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

        return true;
    }
    else
        return false;
}
