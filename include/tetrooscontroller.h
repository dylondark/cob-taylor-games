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
#include "tetroosdata.h"

/*
    TetroosController

    This class is the controller class for the Tetroos game. It is instantiated as an object in the QML file for the game and used in the QML.
    This class contains all of the logic for the Tetroos game. The QML file calls this class's input methods when buttons are pressed in the
    game, and this class sends signals to the QML file to update its view of the game state.
*/
class TetroosController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:

    /*
        Constructor for TetroosController.
    */
    explicit TetroosController();

    /*
        Returns whether game is over or not.
    */
    Q_INVOKABLE bool isGameOver();

    /*
        Calculates and returns the block texture at a given block.
        Calculation is based on the values of the block struct at the given block.

        Currently the plan is to apply rotation and silhouette dynamically on the preexisting images if needed before passing to QML
        to simplify the amount of textures we need to create and store.
        However if higher CPU efficiency is needed we could premake the rotated and silhouetted textures and store them in the textures array.
        This would be at the cost of making a ton more images and a (probably not very notable) increase in RAM usage.
    */
    Q_INVOKABLE QImage getTextureAt(unsigned posX, unsigned posY);

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
        Move piece left action.
    */
    Q_INVOKABLE void left();

    /*
        Move piece right action.
    */
    Q_INVOKABLE void right();

    /*
        Move piece down action.
    */
    Q_INVOKABLE void down();

    /*
        Rotate piece clockwise action.
    */
    Q_INVOKABLE void rotate();

    /*
        Slam piece to the bottom action.
    */
    Q_INVOKABLE void slam();

    /*
        Hold active piece action.
    */
    Q_INVOKABLE void hold();

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
    const std::array<QImage, TEXTURE_COUNT> textures;

    // Holds the game over state for the game. No game logic will continue after this is set to true.
    bool gameOver;

    /*
        This value is set to true when the active piece has just been laid down and the game is about to spawn a new active piece.
        When this is true, the game will not respond to any user actions and will wait for the next gameTimer tick,
        at which it will spawn a new piece and set this value back to false.
    */
    bool waitingForNewPiece;

    // Contains the internal representation of the board grid.
    FlippedArray<std::array<Block, 10>, 20> board;

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
        Does the operations for going to the next level. Ups the level counter and decreases the timer
    */
    void levelUp();

    /*
        Load the texture images and initialize the textures array with them.
    */
    std::array<QImage, TEXTURE_COUNT> loadTextures();
};

#endif // TETROOSCONTROLLER_H
