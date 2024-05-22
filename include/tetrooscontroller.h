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
    Q_INVOKABLE QImage getTextureAt(int posX, int posY);

    /*
        Returns the current score.
    */
    Q_INVOKABLE int getScore();

    /*
        Returns the current holding piece type (or empty if not holding).
    */
    Q_INVOKABLE PieceType getHoldPiece();

    /*
        Returns the currently active piece type.
    */
    Q_INVOKABLE PieceType getCurrentPiece();

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
    Q_INVOKABLE void rotateCW();

    /*
        Rotate piece counterclockwise action.
    */
    Q_INVOKABLE void rotateCCW();

    /*
        Slam piece to the bottom action.
    */
    Q_INVOKABLE void slam();

    /*
        Hold current piece action.
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
    const static int TEXTURE_COUNT = 29;

    // Contains the base textures for all the blocks. @TODO: document which values contain which textures.
    const std::array<QImage, TEXTURE_COUNT> textures;

    // Holds the game over state for the game. No game logic will continue after this is set to true.
    bool gameOver;

    // Contains the internal representation of the board grid.
    Block board[20][10];

    // Current holding piece
    PieceType holdPiece;

    // Current active piece.
    PieceType currentPiece;

    // Current next up piece.
    PieceType nextPiece;

    // Player's current score.
    int score;

    // ID of the currently active piece. Used for determining which set of blocks on the grid makes up the current piece.
    int activePieceID;

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
    bool mergePieceRotateCW();

    /*
        Internal action to rotate the active piece counterclockwise and merge it into the board.

        Returns whether or not the rotate was successful.
    */
    bool mergePieceRotateCCW();

    /*
        Randomly chooses a PieceType to be the next piece and sets it to currentPiece.
    */
    void calculateNextPiece();

    /*
        Load the texture images and initialize the textures array with them.
    */
    std::array<QImage, TEXTURE_COUNT> loadTextures();
};

#endif // TETROOSCONTROLLER_H
