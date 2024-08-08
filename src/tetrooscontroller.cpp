/*
    tetrooscontroller.cpp

    Class definition for TetroosController.
*/

#include <algorithm>
#include <QPainter>
#include <QBuffer>
#include "tetrooscontroller.h"

/*
    Constructor for TetroosController.
*/
TetroosController::TetroosController()
    : QQuickPaintedItem(), TEXTURES(loadTextures()), gameTimer(QTimer(this))
{
    // seed the rng
    srand(time(NULL));

    // connect gameTimer timeout signal to timerTick slot method
    connect(&gameTimer, &QTimer::timeout, this, &TetroosController::timerTick);

    // populate board with empty values
    board = new FlippedArray<std::array<Block, 10>, 20>;

    for (int y = 0; y < 20; y++)
        for (int x = 0; x < 10; x++)
            (*board)[y][x] = EMPTY_BLOCK;

    // init other data members
    gameOver = false;
    activePiece = {empty, 0, 0, 0, 0};
    holdPiece = empty;
    const PieceType PIECES[] = {I, J, L, O, S, T, Z};
    nextPiece = PIECES[rand() % 7];
    score = 0;
    level = 1;
    clearedRows = 0;
    clearedRowsTotal = 0;
    timerInterval = 1000;

    logicThreadWorker.moveToThread(&logicThread);
    logicThread.start(QThread::HighPriority);
}

/*
    Kicks off the game loop. To be called by QML after entering the game.
*/
void TetroosController::startGame()
{
    // start timer
    gameTimer.start(1000); // this should be whatever the interval is at at level 1 according to the equation
}


/*
    Load the texture images and initialize the textures array with them.
*/
std::array<QImage, TetroosController::TEXTURE_COUNT> TetroosController::loadTextures()
{
    return {
        QImage(":/game/gamefiles/Tetroos/images/1-I-x0y0.png"), QImage(":/game/gamefiles/Tetroos/images/2-I-x0y1.png"), QImage(":/game/gamefiles/Tetroos/images/3-I-x0y2.png"), QImage(":/game/gamefiles/Tetroos/images/4-I-x0y3.png"),
        QImage(":/game/gamefiles/Tetroos/images/5-J-x0y0.png"), QImage(":/game/gamefiles/Tetroos/images/6-J-x1y0.png"), QImage(":/game/gamefiles/Tetroos/images/7-J-x1y1.png"), QImage(":/game/gamefiles/Tetroos/images/8-J-x1y2.png"),
        QImage(":/game/gamefiles/Tetroos/images/9-L-x0y0.png"), QImage(":/game/gamefiles/Tetroos/images/10-L-x1y0.png"), QImage(":/game/gamefiles/Tetroos/images/11-L-x0y1.png"), QImage(":/game/gamefiles/Tetroos/images/12-L-x0y2.png"),
        QImage(":/game/gamefiles/Tetroos/images/13-O-x0y0.png"), QImage(":/game/gamefiles/Tetroos/images/14-O-x1y0.png"), QImage(":/game/gamefiles/Tetroos/images/15-O-x1y1.png"), QImage(":/game/gamefiles/Tetroos/images/16-O-x0y1.png"),
        QImage(":/game/gamefiles/Tetroos/images/17-S-x0y0.png"), QImage(":/game/gamefiles/Tetroos/images/18-S-x1y0.png"), QImage(":/game/gamefiles/Tetroos/images/19-S-x1y1.png"), QImage(":/game/gamefiles/Tetroos/images/20-S-x2y1.png"),
        QImage(":/game/gamefiles/Tetroos/images/21-T-x0y1.png"), QImage(":/game/gamefiles/Tetroos/images/22-T-x1y1.png"), QImage(":/game/gamefiles/Tetroos/images/23-T-x1y0.png"), QImage(":/game/gamefiles/Tetroos/images/24-T-x2y1.png"),
        QImage(":/game/gamefiles/Tetroos/images/25-Z-x0y1.png"), QImage(":/game/gamefiles/Tetroos/images/26-Z-x1y1.png"), QImage(":/game/gamefiles/Tetroos/images/27-Z-x1y0.png"), QImage(":/game/gamefiles/Tetroos/images/28-Z-x2y0.png"),
        QImage(":/game/gamefiles/Tetroos/images/29-blank.png")
    };
}

/*
    Paint a new frame onto the canvas.
*/
void TetroosController::paint(QPainter* painter)
{
    unsigned width = this->width() / 10;
    unsigned height = this->height() / 20;

    for (unsigned row = 0; row < 20; ++row)
        for (unsigned col = 0; col < 10; ++col)
            painter->drawImage(width * col, height * row, getTextureAt(col, row), 0, 0, width, height);
}

/*
    Calculates and returns the block texture at a given block.
    Calculation is based on the values of the block struct at the given block.

    Currently the plan is to apply rotation and silhouette dynamically on the preexisting images if needed before passing to QML
    to simplify the amount of textures we need to create and store.
    However if higher CPU efficiency is needed we could premake the rotated and silhouetted textures and store them in the textures array.
    This would be at the cost of making a ton more images and a (probably not very notable) increase in RAM usage.
*/
QImage TetroosController::getTextureAt(unsigned posX, unsigned posY)
{
    // THIS IS A PROTOTYPE IMPLEMENTATION FOR USE WITH THE PROTOTYPE TEXTURES
    // block-specific textures and rotation are not implemented yet

    QImage texture;

    // flip posY
    posY = 19 - posY;

    switch ((*board)[posY][posX].pieceType)
    {
    case I:
        texture = TEXTURES[0];
        break;
    case J:
        texture = TEXTURES[4];
        break;
    case L:
        texture = TEXTURES[8];
        break;
    case O:
        texture = TEXTURES[12];
        break;
    case S:
        texture = TEXTURES[16];
        break;
    case T:
        texture = TEXTURES[20];
        break;
    case Z:
        texture = TEXTURES[24];
        break;
    case empty:
        texture = TEXTURES[28];
    }

    if ((*board)[posY][posX].silhouette)
    {
        // overlay blank texture with half transparency
        QImage blank = TEXTURES[28];
        QPainter painter(&texture);
        painter.setOpacity(0.7);
        painter.drawImage(0, 0, blank);
        painter.end();
    }

    return texture.scaled(QSize(this->height() / 20, this->width() / 10));
}

/*
    Returns the current holding piece type (or empty if not holding).
*/
unsigned TetroosController::getScore()
{
    return score;
}

/*
    Returns the current holding piece type (or empty if not holding).
*/
QString TetroosController::getHoldPiece()
{
    return QString(holdPiece);
}

/*
    Returns the currently active piece type.
*/
QString TetroosController::getActivePiece()
{
    return QString(activePiece.pieceType);
}

/*
    Returns the type of the next piece.
*/
QString TetroosController::getNextPiece()
{
    return QString(nextPiece);
}

/*
    Returns the current level.
*/
Q_INVOKABLE unsigned TetroosController::getLevel()
{
    return level;
}

/*
    Returns the total amount of lines cleared.
*/
Q_INVOKABLE unsigned TetroosController::getLinesCleared()
{
    return clearedRowsTotal;
}

/*
    Move piece down action.
*/
void TetroosController::downAction()
{
    // Move piece down
    if (!gameOver)
    {
        // Update game state
        QMetaObject::invokeMethod(&logicThreadWorker, [&]() {
            updateGame(GameAction::Down);
        });
    }
}
/*
    Move piece left action.
*/
void TetroosController::leftAction()
{
    // Move piece down
    if (!gameOver)
    {
        // Update game state
        QMetaObject::invokeMethod(&logicThreadWorker, [&]() {
            updateGame(GameAction::Left);
        });
    }
}
/*
    Move piece right action.
*/
void TetroosController::rightAction()
{
    // Move piece down
    if (!gameOver)
    {
        // Update game state
        QMetaObject::invokeMethod(&logicThreadWorker, [&]() {
            updateGame(GameAction::Right);
        });
    }
}

/*
    Rotate piece clockwise action.
*/
void TetroosController::rotateAction()
{
    // Rotate piece clockwise
    if (!gameOver)
    {
        // Update game state
        QMetaObject::invokeMethod(&logicThreadWorker, [&]() {
            updateGame(GameAction::Rotate);
        });
    }
}

/*
    Slam piece to the bottom action.
*/
void TetroosController::slamAction()
{
    // Move piece down
    if (!gameOver)
    {
        // Update game state
        QMetaObject::invokeMethod(&logicThreadWorker, [&]() {
            updateGame(GameAction::Slam);
        });
    }
}

/*
    Hold active piece action.
*/
void TetroosController::holdAction()
{
    // Move piece down
    if (!gameOver)
    {
        // Update game state
        QMetaObject::invokeMethod(&logicThreadWorker, [&]() {
            updateGame(GameAction::Hold);
        });
    }
}

/*
    Returns whether game is over or not.
*/
bool TetroosController::isGameOver()
{
    return gameOver;
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
    case GameAction::NewPiece:
        spawnNextPiece();
        applySilhouette();
        break;
    case GameAction::Left:
        if (mergePieceLeft())
            applySilhouette();
        else
            return;
        break;
    case GameAction::Right:
        if (mergePieceRight())
            applySilhouette();
        else
            return;
        break;
    case GameAction::Down:
        if (mergePieceDown())
            applySilhouette();
        else
        {
            clearFilledRows();
            updateGame(GameAction::NewPiece);
            return;
        }
        break;
    case GameAction::Rotate:
        if (mergePieceRotate())     
            applySilhouette();
        else
            return;
        break;
    case GameAction::Slam:
        while (mergePieceDown()); // repeatedly move the piece down until it can't anymore
        clearFilledRows();
        updateGame(GameAction::NewPiece);
        return;
    case GameAction::Hold:
        if (swapHold())
            applySilhouette();
        else
            return;
        break;
    }

    emit updateView(); // tell QML it is time to update the game information
    update(); // begin painting a new frame (call paint())
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
    return rewriteActivePiece(0, 0, true);
}

/*
    Calculates the position of and applies the silhouette to the board.
*/
void TetroosController::applySilhouette()
{
    // erase the current silhouette
    for (unsigned y = 0; y < 20; y++)
        for (unsigned x = 0; x < 10; x++)
            if ((*board)[y][x].silhouette == true)
                (*board)[y][x] = EMPTY_BLOCK;

    // get the grid for the active piece type
    const PieceGrid NEW_PIECE = getPieceGrid(activePiece.pieceType, activePiece.rotation);

    // go from the active piece to the bottom and save the last y value where the silhouette can be written
    unsigned silhouetteY = 0;
    bool collision = false;
    for (unsigned y = activePiece.posY; y < 20; y--) // go from activepiece to bottom
    {
        // check for collision with other pieces
        unsigned pieceX = 0, pieceY = 0;
        collision = false;
        for (unsigned boardY = y; boardY < std::min(y + 4, 20U); boardY++) // use min to ensure we don't go out of bounds
        {
            for (unsigned boardX = activePiece.posX; boardX < std::min(activePiece.posX + 4, 10U); boardX++)
            {
                // get the two blocks we are examining
                Block currentBlockInBoard = (*board)[boardY][boardX];
                bool currentBlockInPiece = NEW_PIECE[pieceY][pieceX];

                if (currentBlockInBoard.pieceType != empty && currentBlockInBoard.pieceID != activePiece.pieceID && currentBlockInPiece == true)
                    collision = true;

                ++pieceX;
            }
            pieceX = 0;
            ++pieceY;
        }

        // if we collided at this Y
        if (collision)
        {
            silhouetteY = y + 1; // save the y value so we can start writing the silhouette at it
            break;
        }
    }

    // rewrite the silhouette piece into its new position
    unsigned pieceX = 0, pieceY = 0;
    for (unsigned boardY = silhouetteY; boardY < std::min(silhouetteY + 4, 20U); boardY++)
    {
        for (unsigned boardX = activePiece.posX; boardX < std::min(activePiece.posX + 4, 10U); boardX++)
        {
            // get reference to block since we are modifying it
            Block* currentBlockInBoard = &(*board)[boardY][boardX];
            bool currentBlockInPiece = NEW_PIECE[pieceY][pieceX];

            if (currentBlockInPiece == true && currentBlockInBoard->pieceID != activePiece.pieceID)
                *currentBlockInBoard = {activePiece.pieceType, activePiece.rotation, activePiece.pieceID, true, pieceX, pieceY};

            ++pieceX;
        }
        pieceX = 0;
        ++pieceY;
    }
}

/*
    Swaps out the active piece with the currently holding piece.
    Checks the piece to be swapped for collision.

    Returns whether or not the swap was successful.
*/
bool TetroosController::swapHold()
{
    if (holdPiece != empty)
    {
        std::swap(holdPiece, activePiece.pieceType);

        // attempt to rewrite the piece with the hold and active swapped out
        if (!rewriteActivePiece(0, 0, false))
        {
            // swap back if the rewrite didnt succeed
            std::swap(holdPiece, activePiece.pieceType);
            return false;
        }
        return true;
    }
    else
    {
        // swap active into hold piece
        std::swap(holdPiece, activePiece.pieceType);
        // active will now be empty

        // swap next piece into active
        std::swap(activePiece.pieceType, nextPiece);
        // next piece will now be empty

        // attempt to write it into the board
        if (rewriteActivePiece(0, 0, false))
        {
            // generate new nextPiece
            const PieceType PIECES[] = {I, J, L, O, S, T, Z};
            nextPiece = PIECES[rand() % 7];
            return true;
        }
        else
        {
            // undo swaps if it failed
            std::swap(activePiece.pieceType, nextPiece);
            std::swap(holdPiece, activePiece.pieceType);
            return false;
        }
    }
}

/*
    Randomly chooses a PieceType to be the next piece and spawns it.
    Sets gameOver to true if it can't spawn a piece.
*/
void TetroosController::spawnNextPiece()
{
    // swap next piece into active
    std::swap(activePiece.pieceType, nextPiece);

    // update active piece metadata
    activePiece.rotation = 0;
    std::pair<unsigned, unsigned> pieceWH = getPieceDim(activePiece.pieceType, 0);
    activePiece.posX = 5 - pieceWH.first / 2; // spawn in middle (ish)
    activePiece.posY = 20 - pieceWH.second; // spawn as close to top as possible
    ++activePiece.pieceID;

    // generate new nextPiece
    const PieceType PIECES[] = {I, J, L, O, S, T, Z};
    nextPiece = PIECES[rand() % 7];

    // attempt to write it into the board
    // if it cant fit, go offscreen until the piece can fit
    // if it goes fully offscreen then end the game
    for (int spawnY = activePiece.posY; spawnY < 20; spawnY++)
    {
        activePiece.posY = spawnY;
        if (rewriteActivePiece(0, 0, false))
            return;
    }
    gameOver = true;
}

/*
    Checks the board for filled rows and clears them. Adds to the player's score.

    Returns whether there were any filled rows.
*/
bool TetroosController::clearFilledRows()
{
    // loop through all rows and check for filled rows
    bool isFilled = true;
    unsigned filledRows = 0;
    for (unsigned y = 0; y < 20; y++)
    {
        isFilled = true;
        // check the row
        for (unsigned x = 0; x < 10; x++)
        {
            if ((*board)[y][x].pieceType == empty)
            {
                isFilled = false;
                break;
            }
        }

        if (isFilled)
        {
            ++filledRows;
            ++clearedRows;
            ++clearedRowsTotal;

            // clear the row
            for (unsigned x = 0; x < 10; x++)
                (*board)[y][x] = EMPTY_BLOCK;
        }
    }

    // increment level if needed
    if (clearedRows >= LEVEL_ROW_CLEARS)
    {
        ++level;
        clearedRows -= LEVEL_ROW_CLEARS;

        // decrease timer interval
        timerInterval = 1 / (0.0004 * (level + 2)); // equation for calculating the timing
    }

    // apply points
    switch (filledRows)
    {
    case 0:
        return false;
    case 1:
        score += 100 * level;
        break;
    case 2:
        score += 300 * level;
        break;
    case 3:
        score += 500 * level;
        break;
    case 4:
        score += 800 * level;
        break;
    }

    // shift all blocks down
    bool isRowEmpty = true;
    for (unsigned y = 0; y < 20; y++) // go from bottom to top
    {
        // get whether this row is empty or not
        for (unsigned x = 0; x < 10; x++)
        {
            if ((*board)[y][x].pieceType != empty)
            {
                isRowEmpty = false;
                break;
            }
        }

        // stop this logic when we have already moved all of the previously filled rows
        if (filledRows > 0)
        {
            // bring all other rows down if row is empty
            if (isRowEmpty)
            {
                for (unsigned y2 = y--; y2 < 19; y2++) // starting at the empty row y value going all the way to the top
                    // swap the empty row all the way up to the top (i feel like a genius for thinking of this)
                    std::swap((*board)[y2], (*board)[y2 + 1]);
                --filledRows;
            }
        }
        else
            break;
        isRowEmpty = true;
    }

    return true;
}

/*
    Slot function that is called when gameTimer ticks. Calls updateGame with the TimerTick action.
*/
void TetroosController::timerTick()
{
    if (gameOver)
    {
        gameTimer.stop();
        return;
    }

    QMetaObject::invokeMethod(&logicThreadWorker, [&]() {
        updateGame(GameAction::Down);
    });

    gameTimer.setInterval(timerInterval);
}

/*
    Returns a PieceGrid for a specified piece with specified rotation.

    PieceType piece: The type of piece to return the grid for.
    unsigned rotation: The rotation to apply to the grid before returning. Uses same logic as the rotation values in the Block struct.
*/
PieceGrid TetroosController::getPieceGrid(PieceType piece, unsigned rotation)
{
    PieceGrid newGrid;
    switch (piece)
    {
    case I: newGrid = I_PIECE;
        break;
    case J: newGrid = J_PIECE;
        break;
    case L: newGrid = L_PIECE;
        break;
    case O: newGrid = O_PIECE;
        break;
    case S: newGrid = S_PIECE;
        break;
    case T: newGrid = T_PIECE;
        break;
    case Z: newGrid = Z_PIECE;
        break;
    }
    PieceGrid returnGrid = newGrid;

    rotation = rotation % 4;
    // This will run for how many times it needs to be rotated at 90 degrees clockwise
    for (unsigned iteration = 1; iteration <= rotation; iteration++)
    {
        for (unsigned y = 0; y <= 3; y++)
        {
            for (unsigned x = 0; x <= 3; x++)
                returnGrid[x][y] = newGrid[y][3 - x];
        }
        newGrid = returnGrid;
    }

    // Checking rows and swapping if needed
    for (unsigned z = 0; z <= 3; z++)
    {
        // Checks if row is empty, if empty will swap up the row
        bool check = false;
        for (bool cell : returnGrid[0])
        {
            if (cell)
            {
                check = true;
                break;
            }
        }

        // If row is empty, then it will stop swapping
        if (check)
            break;

        // Swapping the bottom row to the top
        for(unsigned swapper = 0; swapper <= 2; swapper++)
            std::swap(returnGrid[swapper], returnGrid[swapper + 1]);

    }

    // Checking columns and shifting if needed
    for (unsigned shiftCount = 0; shiftCount < 4; shiftCount++)
    {
        // Checks if the leftmost column is empty
        bool isLeftColumnEmpty = true;
        for (unsigned row = 0; row < 4; row++)
        {
            if (returnGrid[row][0] != 0) // Assuming non-zero values mean non-empty cells
            {
                isLeftColumnEmpty = false;
                break;
            }
        }

        // If the leftmost column is not empty, stop shifting
        if (!isLeftColumnEmpty)
            break;

        // Shifting columns to the left
        for (unsigned col = 0; col < 3; col++)
        {
            for (unsigned row = 0; row < 4; row++)
            {
                returnGrid[row][col] = returnGrid[row][col + 1];
            }
        }

        // Clear the rightmost column after shifting
        for (unsigned row = 0; row < 4; row++)
        {
            returnGrid[row][3] = 0;
        }
    }
    return returnGrid;
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

    // start by checking if startpos values are out of the desired range
    if (startPosY >= 20 || startPosX >= 10) // must be 0-19 for Y and 0-9 for X, if it goes below 0 it will wrap over to 4bil because unsigned
        return false;

    // get the max width of the new piece and ensure it doesnt go out of bounds
    if (startPosX > 5) // only do this part if we are moving right and we are within 4 blocks away from the right edge
    {
        unsigned edgeSpace = 10 - startPosX;

        if (rotate)
        {
            // adjust the piece x so that we can write it at the rightmost possible position
            unsigned widthAfterRotate = getPieceDim(activePiece.pieceType, activePiece.rotation + rotate).first;
            if (widthAfterRotate > edgeSpace)
                startPosX = 10 - widthAfterRotate;
        }
        else // if we are not rotating and just bumping into the edge, dont write anything
            if (getPieceDim(activePiece.pieceType, activePiece.rotation).first > edgeSpace)
                return false;
    }

    // get the grid for the active piece type
    const PieceGrid NEW_PIECE = getPieceGrid(activePiece.pieceType, activePiece.rotation + rotate);

    // check for collision with other pieces
    unsigned pieceX = 0, pieceY = 0;
    for (unsigned boardY = startPosY; boardY < std::min(startPosY + 4, 20U); boardY++) // use min to ensure we don't go out of bounds
    {
        for (unsigned boardX = startPosX; boardX < std::min(startPosX + 4, 10U); boardX++)
        {
            if ((*board)[boardY][boardX].pieceType != empty && (*board)[boardY][boardX].pieceID != activePiece.pieceID && NEW_PIECE[pieceY][pieceX])
                return false;

            ++pieceX;
        }
        pieceX = 0;
        ++pieceY;
    }

    // ---at this point we are assuming there are no conflicts and it is good to start making changes to the board---

    activePiece.rotation = activePiece.rotation + rotate;

    // erase the active piece from its current position
    for (unsigned boardY = activePiece.posY; boardY < std::min(activePiece.posY + 4, 20U); boardY++)
        for (unsigned boardX = activePiece.posX; boardX < std::min(activePiece.posX + 4, 10U); boardX++)
        {
            if ((*board)[boardY][boardX].pieceID == activePiece.pieceID)
                // blank the block
                (*board)[boardY][boardX] = EMPTY_BLOCK;
        }

    // rewrite the active piece into its new position
    pieceX = pieceY = 0;
    for (unsigned boardY = startPosY; boardY < std::min(startPosY + 4, 20U); boardY++)
    {
        for (unsigned boardX = startPosX; boardX < std::min(startPosX + 4, 10U); boardX++)
        {
            if (NEW_PIECE[pieceY][pieceX])
                (*board)[boardY][boardX] = {activePiece.pieceType, activePiece.rotation, activePiece.pieceID, false, pieceX, pieceY};

            ++pieceX;
        }
        pieceX = 0;
        ++pieceY;
    }

    // update the position values of the active piece
    activePiece.posX = startPosX;
    activePiece.posY = startPosY;

    return true;
}

/*
    Gets the max width and height that a piece occupies at a given rotation.

    PieceType piece: the type of piece.
    unsigned rotation: the rotation value of the piece.
    Returns a pair of unsigned in the order (width, height).
*/
std::pair<unsigned, unsigned> TetroosController::getPieceDim(PieceType piece, unsigned rotation)
{
    const PieceGrid NEW_PIECE = getPieceGrid(piece, rotation);
    std::pair<unsigned, unsigned> wh(4, 4);

    // test for width
    bool isBlockInColumn = false;
    for (unsigned x = 0; x < 4; x++)
    {
        for (unsigned y = 0; y < 4; y++)
        {
            if (NEW_PIECE[y][x])
            {
                isBlockInColumn = true;
                break;
            }
        }
        if (isBlockInColumn)
            wh.first = x + 1;
        isBlockInColumn = false;
    }

    // test for height
    bool isBlockInRow = false;
    for (unsigned y = 0; y < 4; y++)
    {
        for (unsigned x = 0; x < 4; x++)
        {
            if (NEW_PIECE[y][x])
            {
                isBlockInRow = true;
                break;
            }
        }
        if (isBlockInRow)
            wh.second = y + 1;
        isBlockInRow = false;
    }

    return wh;
}
