/*
    tetrooscontroller.h

    Class declaration for TetroosController.
*/

#ifndef TETROOSCONTROLLER_H
#define TETROOSCONTROLLER_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>
#include <QImage>
#include <array>
#include <QThread>
#include <QQuickPaintedItem>
#include "threadworker.h"
#include "tetroosdata.h"

/*
    TetroosController

    This class is the controller class for the Tetroos game. It is instantiated as an object in the QML file for the game and used in the QML.
    This class contains all of the logic for the Tetroos game. The QML file calls this class's input methods when buttons are pressed in the
    game, and this class sends signals to the QML file to update its view of the game state.
*/
class TetroosController : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
public:

    /*
        Constructor for TetroosController.
    */
    explicit TetroosController();

    /*
        Paint a new frame onto the canvas.
    */
    void paint(QPainter* painter) override;

    /*
        Kicks off the game loop. To be called by QML after entering the game.
    */
    Q_INVOKABLE void startGame();

    /*
        Returns whether game is over or not.
    */
    Q_INVOKABLE bool isGameOver();

    /*
        Returns the current score.
    */
    Q_INVOKABLE unsigned getScore();

    /*
        Returns the current holding piece type (or empty if not holding).
    */
    Q_INVOKABLE PieceType getHoldPiece();

    /*
        Returns the currently active piece type.
    */
    Q_INVOKABLE PieceType getActivePiece();

    /*
        Returns the type of the next piece.
    */
    Q_INVOKABLE PieceType getNextPiece();

    /*
        Returns the current level.
    */
    Q_INVOKABLE unsigned getLevel();

    /*
        Returns the total amount of lines cleared.
    */
    Q_INVOKABLE unsigned getLinesCleared();

    /*
        Move piece left action.
    */
    Q_INVOKABLE void leftAction();

    /*
        Move piece right action.
    */
    Q_INVOKABLE void rightAction();

    /*
        Move piece down action.
    */
    Q_INVOKABLE void downAction();

    /*
        Rotate piece clockwise action.
    */
    Q_INVOKABLE void rotateAction();

    /*
        Slam piece to the bottom action.
    */
    Q_INVOKABLE void slamAction();

    /*
        Hold active piece action.
    */
    Q_INVOKABLE void holdAction();

signals:
    /*
        Signal to tell QML when it's time to update the game view.
    */
    void updateView();

private slots:
    /*
        Slot function that is called when gameTimer ticks. Calls updateGame with the TimerTick action.
    */
    void timerTick();

private:
    // The amount of textures to hold in the textures array.
    const static unsigned TEXTURE_COUNT = 29;

    // How many row clears until a new level.
    const unsigned LEVEL_ROW_CLEARS = 5;

    // Contains the base textures for all the blocks. @TODO: document which values contain which textures.
    const std::array<QImage, TEXTURE_COUNT> TEXTURES;

    // The main thread used to execute game logic calculations.
    QThread logicThread;

    // Worker for the main thread.
    ThreadWorker logicThreadWorker;

    // Holds the game over state for the game. No game logic will continue after this is set to true.
    bool gameOver;

    // Contains the internal representation of the board grid.
    std::array<std::array<Block, 10>, 20>* board;

    // Current active piece. Holds all relevant data about the piece on the board.
    ActivePiece activePiece;

    // Current holding piece
    PieceType holdPiece;

    // Current next up piece.
    PieceType nextPiece;

    // Player's current score.
    unsigned score;

    // The current level the game is on.
    unsigned level;

    // How many lines have been cleared since the last level increase.
    unsigned clearedRows;

    // How many lines have been cleared since the start of the game.
    unsigned clearedRowsTotal;

    // The current interval of the timer in ms (how many ms it takes for the piece to fall 1 row naturally).
    unsigned timerInterval;

    // Timer that causes the block to fall. Gets increasingly faster according to an exponential function.
    QTimer gameTimer;

    /*
        Main game loop. Called every time a new action has happened.
        Calculates the new game state in response to the action and sends the signal to QML to display it.

        GameAction trigger: what action is triggering the game update.
    */
    void updateGame(GameAction trigger);

    /*
        Calculates and returns the block texture at a given block.
        Calculation is based on the values of the block struct at the given block.

        Currently the plan is to apply rotation and silhouette dynamically on the preexisting images if needed before passing to QML
        to simplify the amount of textures we need to create and store.
        However if higher CPU efficiency is needed we could premake the rotated and silhouetted textures and store them in the textures array.
        This would be at the cost of making a ton more images and a (probably not very notable) increase in RAM usage.
    */
    QImage getTextureAt(unsigned posX, unsigned posY);

    /*
        Internal action to move the active piece left and merge it into the board.

        Returns whether or not the move was successful.
    */
    bool mergePieceLeft();

    /*
        Internal action to move the active piece right and merge it into the board.

        Returns whether or not the move was successful.
    */
    bool mergePieceRight();

    /*
        Internal action to move the active piece down one and merge it into the board.

        Returns whether or not the move was successful.
    */
    bool mergePieceDown();

    /*
        Internal action to rotate the active piece clockwise and merge it into the board.

        Returns whether or not the rotate was successful.
    */
    bool mergePieceRotate();

    /*
        Swaps out the active piece with the currently holding piece.
        Checks the piece to be swapped for collision.

        Returns whether or not the swap was successful.
    */
    bool swapHold();

    /*
        Calculates the position of and applies the silhouette to the board.
    */
    void applySilhouette();

    /*
        Randomly chooses a PieceType to be the next piece and spawns it.
        Sets gameOver to true if it can't spawn a piece.
    */
    void spawnNextPiece();

    /*
        Checks the board for filled rows and clears them. Adds to the player's score.

        Returns whether there were any filled rows.
    */
    bool clearFilledRows();

    /*
        Erases the current active piece and then rewrites it again at the specified coordinates.

        int xOffset: number to offset the X value of the piece by (it gets added to the piece's current X).
        int yOffset: number to offset the Y value of the piece by (it gets added to the piece's current Y).
        bool rotate: whether to rotate the piece 90 degrees clockwise.
        Returns whether the rewrite was a success.
    */
    bool rewriteActivePiece(int xOffset, int yOffset, bool rotate);

    /*
        Returns a PieceGrid for a specified piece with specified rotation.

        PieceType piece: The type of piece to return the grid for.
        unsigned rotation: The rotation to apply to the grid before returning. Uses same logic as the rotation values in the Block struct.
    */
    PieceGrid getPieceGrid(PieceType piece, unsigned rotation);

    /*
        Gets the max width and height that a piece occupies at a given rotation.

        PieceType piece: the type of piece.
        unsigned rotation: the rotation value of the piece.
        Returns a pair of unsigned in the order (width, height).
    */
    std::pair<unsigned, unsigned> getPieceDim(PieceType piece, unsigned rotation);

    /*
        Load the texture images and initialize the textures array with them.
    */
    std::array<QImage, TEXTURE_COUNT> loadTextures();
};

#endif // TETROOSCONTROLLER_H
