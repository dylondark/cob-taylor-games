/*
    tetrooscontroller.cpp

    Class definition for TetroosController.
*/

#include <algorithm>
#include <QPainter>
#include <QBuffer>
#include "tetrooscontroller.h"
#include "cliparser.h"

/*
    Constructor for TetroosController.
*/
TetroosController::TetroosController()
    : QQuickPaintedItem(), TEXTURES_ORIGINAL(loadTextures()), gameTimer(QTimer(this)), filepath(CliParser::getPath())
{
    setRenderTarget(QQuickPaintedItem::FramebufferObject);

    // seed the rng
    srand(time(NULL));

    // connect gameTimer timeout signal to timerTick slot method
    connect(&gameTimer, &QTimer::timeout, this, &TetroosController::timerTick);

    // connect width changed signal to size changed slot
    connect(this, &TetroosController::widthChanged, this, &TetroosController::onSizeChanged);

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

TetroosController::~TetroosController()
{
    // Stop the logic thread
    logicThread.quit();
    logicThread.wait();

    // Delete the dynamically allocated board
    delete board;
}


/*
    Load the texture images and initialize the textures array with them.
*/
std::array<QImage, TetroosController::TEXTURE_COUNT> TetroosController::loadTextures()
{
    return {
        QImage(filepath + "/gamefiles/Tetroos/images/1-I-x0y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/2-I-x0y1.png"), QImage(filepath + "/gamefiles/Tetroos/images/3-I-x0y2.png"), QImage(filepath + "/gamefiles/Tetroos/images/4-I-x0y3.png"),
        QImage(filepath + "/gamefiles/Tetroos/images/5-J-x0y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/6-J-x1y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/7-J-x1y1.png"), QImage(filepath + "/gamefiles/Tetroos/images/8-J-x1y2.png"),
        QImage(filepath + "/gamefiles/Tetroos/images/9-L-x0y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/10-L-x1y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/11-L-x0y1.png"), QImage(filepath + "/gamefiles/Tetroos/images/12-L-x0y2.png"),
        QImage(filepath + "/gamefiles/Tetroos/images/13-O-x0y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/14-O-x1y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/15-O-x1y1.png"), QImage(filepath + "/gamefiles/Tetroos/images/16-O-x0y1.png"),
        QImage(filepath + "/gamefiles/Tetroos/images/17-S-x0y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/18-S-x1y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/19-S-x1y1.png"), QImage(filepath + "/gamefiles/Tetroos/images/20-S-x2y1.png"),
        QImage(filepath + "/gamefiles/Tetroos/images/21-T-x0y1.png"), QImage(filepath + "/gamefiles/Tetroos/images/22-T-x1y1.png"), QImage(filepath + "/gamefiles/Tetroos/images/23-T-x1y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/24-T-x2y1.png"),
        QImage(filepath + "/gamefiles/Tetroos/images/25-Z-x0y1.png"), QImage(filepath + "/gamefiles/Tetroos/images/26-Z-x1y1.png"), QImage(filepath + "/gamefiles/Tetroos/images/27-Z-x1y0.png"), QImage(filepath + "/gamefiles/Tetroos/images/28-Z-x2y0.png"),
        QImage(filepath + "/gamefiles/Tetroos/images/29-blank.png")
    };
}

/*
    Runs when size of the widget changes. Smoothly rescales the textures to fit the new size.
*/
void TetroosController::onSizeChanged()
{
    // scale each texture to the new size and store in texturesScaled
    for (unsigned i = 0; i < TEXTURE_COUNT; i++)
        texturesScaled[i] = TEXTURES_ORIGINAL[i].scaled(QSize(this->height() / 20, this->width() / 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
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
*/
QImage TetroosController::getTextureAt(unsigned posX, unsigned posY)
{
    QImage texture(texturesScaled[0].size(), QImage::Format_ARGB32);

    // flip posY
    posY = 19 - posY;

    // get block
    Block thisBlock = (*board)[posY][posX];

    // get texture and colors based on block type
    QColor blockColor;
    switch (thisBlock.pieceType)
    {
    case I:
        if (thisBlock.posY == 0)
            texture = texturesScaled[0];
        else if (thisBlock.posY == 1)
            texture = texturesScaled[1];
        else if (thisBlock.posY == 2)
            texture = texturesScaled[2];
        else if (thisBlock.posY == 3)
            texture = texturesScaled[3];
        blockColor = QColor(0, 242, 255);
        break;
    case J:
        if (thisBlock.posX == 0 && thisBlock.posY == 0)
            texture = texturesScaled[4];
        else if (thisBlock.posX == 1 && thisBlock.posY == 0)
            texture = texturesScaled[5];
        else if (thisBlock.posX == 1 && thisBlock.posY == 1)
            texture = texturesScaled[6];
        else if (thisBlock.posX == 1 && thisBlock.posY == 2)
            texture = texturesScaled[7];
        blockColor = QColor(255, 0, 225);
        break;
    case L:
        if (thisBlock.posX == 0 && thisBlock.posY == 0)
            texture = texturesScaled[8];
        else if (thisBlock.posX == 1 && thisBlock.posY == 0)
            texture = texturesScaled[9];
        else if (thisBlock.posX == 0 && thisBlock.posY == 1)
            texture = texturesScaled[10];
        else if (thisBlock.posX == 0 && thisBlock.posY == 2)
            texture = texturesScaled[11];
        blockColor = QColor(255, 123, 0);
        break;
    case O:
        if (thisBlock.posX == 0 && thisBlock.posY == 0)
            texture = texturesScaled[12];
        else if (thisBlock.posX == 1 && thisBlock.posY == 0)
            texture = texturesScaled[13];
        else if (thisBlock.posX == 1 && thisBlock.posY == 1)
            texture = texturesScaled[14];
        else if (thisBlock.posX == 0 && thisBlock.posY == 1)
            texture = texturesScaled[15];
        blockColor = QColor(255, 204, 0);
        break;
    case S:
        if (thisBlock.posX == 0 && thisBlock.posY == 0)
            texture = texturesScaled[16];
        else if (thisBlock.posX == 1 && thisBlock.posY == 0)
            texture = texturesScaled[17];
        else if (thisBlock.posX == 1 && thisBlock.posY == 1)
            texture = texturesScaled[18];
        else if (thisBlock.posX == 2 && thisBlock.posY == 1)
            texture = texturesScaled[19];
        blockColor = QColor(255, 0, 0);
        break;
    case T:
        if (thisBlock.posX == 0 && thisBlock.posY == 1)
            texture = texturesScaled[20];
        else if (thisBlock.posX == 1 && thisBlock.posY == 1)
            texture = texturesScaled[21];
        else if (thisBlock.posX == 1 && thisBlock.posY == 0)
            texture = texturesScaled[22];
        else if (thisBlock.posX == 2 && thisBlock.posY == 1)
            texture = texturesScaled[23];
        blockColor = QColor(172, 0, 255);
        break;
    case Z:
        if (thisBlock.posX == 0 && thisBlock.posY == 1)
            texture = texturesScaled[24];
        else if (thisBlock.posX == 1 && thisBlock.posY == 1)
            texture = texturesScaled[25];
        else if (thisBlock.posX == 1 && thisBlock.posY == 0)
            texture = texturesScaled[26];
        else if (thisBlock.posX == 2 && thisBlock.posY == 0)
            texture = texturesScaled[27];
        blockColor = QColor(0, 255, 0);
        break;
    case empty:
        texture = texturesScaled[28];
        blockColor = QColor(40, 20, 0);
    }
    blockColor = blockColor.darker(150);

    // rotate block texture
    if (thisBlock.rotation != 0)
    {
        QTransform transform;
        transform.rotate(90 * thisBlock.rotation);
        texture = texture.transformed(transform);
    }

    // calculate and apply borders
    QPainter borderPainter(&texture);
    borderPainter.setOpacity(0.7);
    unsigned w = texture.width();
    unsigned h = texture.height();
    unsigned w8 = w / 8;
    unsigned h8 = h / 8;
    unsigned thisPieceID = thisBlock.pieceID;
    bool thisPieceSilhouette = thisBlock.silhouette;
    if (thisBlock.pieceType == empty)
    {
        // apply borders to all sides
        borderPainter.fillRect(0, 0, texture.width() / 8, texture.height(), blockColor); // left side
        borderPainter.fillRect(0, 0, texture.width(), texture.height() / 8, blockColor); // top side
        borderPainter.fillRect(texture.width() - texture.width() / 8, 0, texture.width() / 8, texture.height(), blockColor); // right side
        borderPainter.fillRect(0, texture.height() - texture.height() / 8, texture.width(), texture.height() / 8, blockColor); // bottom side
    }
    else
    {
        // check if neighboring blocks are part of the same piece
        // left
        if ((posX == 0) || ((posX > 0) && ((*board)[posY][posX - 1].pieceID != thisPieceID || (*board)[posY][posX - 1].silhouette != thisPieceSilhouette)))
        {
            borderPainter.fillRect(0, h8, w8, h - h8 * 2, blockColor); // left side
        }
        // top
        if ((posY == 0) || ((posY > 0) && ((*board)[posY - 1][posX].pieceID != thisPieceID || (*board)[posY - 1][posX].silhouette != thisPieceSilhouette)))
        {
            borderPainter.fillRect(w8, h - h8, w - w8 * 2, h8, blockColor); // top side
        }
        // right
        if ((posX == 9) || ((posX < 9) && ((*board)[posY][posX + 1].pieceID != thisPieceID || (*board)[posY][posX + 1].silhouette != thisPieceSilhouette)))
        {
            borderPainter.fillRect(w - w8, h8, w8, h - h8 * 2, blockColor); // right side
        }
        // bottom
        if ((posY == 19) || ((posY < 19) && ((*board)[posY + 1][posX].pieceID != thisPieceID || (*board)[posY + 1][posX].silhouette != thisPieceSilhouette)))
        {
            borderPainter.fillRect(w8, 0, w - w8 * 2, h8, blockColor); // bottom side
        }
    }
    // calculate and apply corners
    // apply corner unless the block is fully surrounded by other blocks in the same piece
    // top left
    if (((posX - 1 <= 9) && (posY + 1 <= 19)))
    {
        if (!((thisPieceID == (*board)[posY][posX - 1].pieceID && thisPieceSilhouette == (*board)[posY][posX - 1].silhouette)
             && (thisPieceID == (*board)[posY + 1][posX - 1].pieceID && thisPieceSilhouette == (*board)[posY + 1][posX - 1].silhouette)
             && (thisPieceID == (*board)[posY + 1][posX].pieceID && thisPieceSilhouette == (*board)[posY + 1][posX].silhouette)))
            borderPainter.fillRect(0, 0, w8, h8, blockColor);
    }
    else
        borderPainter.fillRect(0, 0, w8, h8, blockColor);
    // top right
    if (((posX + 1 <= 9) && (posY + 1 <= 19)))
    {
        if (!((thisPieceID == (*board)[posY + 1][posX].pieceID && thisPieceSilhouette == (*board)[posY + 1][posX].silhouette)
             && (thisPieceID == (*board)[posY + 1][posX + 1].pieceID && thisPieceSilhouette == (*board)[posY + 1][posX + 1].silhouette)
             && (thisPieceID == (*board)[posY][posX + 1].pieceID && thisPieceSilhouette == (*board)[posY][posX + 1].silhouette)))
            borderPainter.fillRect(w - w8, 0, w8, h8, blockColor);
    }
    else
        borderPainter.fillRect(w - w8, 0, w8, h8, blockColor);
    // bottom right
    if (((posX + 1 <= 9) && (posY - 1 <= 19)))
    {
        if (!((thisPieceID == (*board)[posY][posX + 1].pieceID && thisPieceSilhouette == (*board)[posY][posX + 1].silhouette)
             && (thisPieceID == (*board)[posY - 1][posX + 1].pieceID && thisPieceSilhouette == (*board)[posY - 1][posX + 1].silhouette)
             && (thisPieceID == (*board)[posY - 1][posX].pieceID && thisPieceSilhouette == (*board)[posY - 1][posX].silhouette)))
            borderPainter.fillRect(w - w8, h - h8, w8, h8, blockColor);
    }
    else
        borderPainter.fillRect(w - w8, h - h8, w8, h8, blockColor);
    // bottom left
    if (((posX - 1 <= 9) && (posY - 1 <= 19)))
    {
        if (!((thisPieceID == (*board)[posY - 1][posX].pieceID && thisPieceSilhouette == (*board)[posY - 1][posX].silhouette)
             && (thisPieceID == (*board)[posY - 1][posX - 1].pieceID && thisPieceSilhouette == (*board)[posY - 1][posX - 1].silhouette)
             && (thisPieceID == (*board)[posY][posX - 1].pieceID && thisPieceSilhouette == (*board)[posY][posX - 1].silhouette)))
            borderPainter.fillRect(0, h - h8, w8, h8, blockColor);
    }
    else
        borderPainter.fillRect(0, h - h8, w8, h8, blockColor);

    // overlay blank texture at half opacity if the block is silhouette
    if (thisBlock.silhouette)
    {
        borderPainter.setOpacity(0.5);
        borderPainter.drawImage(0, 0, texturesScaled[28]);
    }

    return texture;
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
    return QString(static_cast<char>(holdPiece));
}

/*
    Returns the currently active piece type.
*/
QString TetroosController::getActivePiece()
{
    return QString(static_cast<char>(activePiece.pieceType));
}

/*
    Returns the type of the next piece.
*/
QString TetroosController::getNextPiece()
{
    return QString(static_cast<char>(nextPiece));
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
    QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection); // begin painting a new frame (call paint()). call on main thread
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
                bool currentBlockInPiece = NEW_PIECE[pieceY][pieceX].filled;

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
            PieceGridBlock currentBlockInPiece = NEW_PIECE[pieceY][pieceX];

            if (currentBlockInPiece.filled == true && currentBlockInBoard->pieceID != activePiece.pieceID)
                *currentBlockInBoard = {activePiece.pieceType, activePiece.rotation, activePiece.pieceID, true, currentBlockInPiece.posX, currentBlockInPiece.posY};

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
    if (holdUsed)
        return false;
    else
    {
        bool holdState = holdPiece != empty;
        // swap active into hold piece
        std::swap(holdPiece, activePiece.pieceType);

        // clear the old piece from the board
        for (unsigned boardY = activePiece.posY; boardY < std::min(activePiece.posY + 4, 20U); boardY++)
            for (unsigned boardX = activePiece.posX; boardX < std::min(activePiece.posX + 4, 10U); boardX++)
            {
                if ((*board)[boardY][boardX].pieceID == activePiece.pieceID)
                    // blank the block
                    (*board)[boardY][boardX] = EMPTY_BLOCK;
            }

        if (holdState)
        {
            // we need to get the current active piece (that was the holding piece) into next so that spawnNextPiece will spawn it
            PieceType currentNext = nextPiece; // save the current next piece to put it back after (so spawnNextPiece doesnt generate a new next piece)
            std::swap(activePiece.pieceType, nextPiece);
            spawnNextPiece();
            nextPiece = currentNext;
        }
        else
            spawnNextPiece();

        holdUsed = true;
        return true;
    }
}

/*
    Randomly chooses a PieceType to be the next piece and spawns it.
    Sets gameOver to true if it can't spawn a piece.
*/
void TetroosController::spawnNextPiece()
{
    holdUsed = false;

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
        for (PieceGridBlock cell : returnGrid[0])
        {
            if (cell.filled)
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
            if (returnGrid[row][0].filled != false)
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
            returnGrid[row][3].filled = false;
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
            if ((*board)[boardY][boardX].pieceType != empty && (*board)[boardY][boardX].pieceID != activePiece.pieceID && NEW_PIECE[pieceY][pieceX].filled)
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
            if (NEW_PIECE[pieceY][pieceX].filled)
                (*board)[boardY][boardX] = {activePiece.pieceType, activePiece.rotation, activePiece.pieceID, false, NEW_PIECE[pieceY][pieceX].posX, NEW_PIECE[pieceY][pieceX].posY};

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
            if (NEW_PIECE[y][x].filled)
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
            if (NEW_PIECE[y][x].filled)
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
