/*
    mazecontroller.h

    Class declaration for MazeController.
*/

#ifndef MAZECONTROLLER_H
#define MAZECONTROLLER_H

#include <QObject>
#include <QQuickPaintedItem>
#include "flippedarray.h"
#include "threadworker.h"
#include <QThread>
#include <QTimer>

/*
    This is the data structure that represents every individual cell in the maze board.
    It contains whether the cell is a wall or if the player is currently occupying it.
*/
struct Cell
{
    bool wall;
    bool player;
    int x;
    int y;
};

/*
    This enum defines all of the actions that the game can be doing. It includes all of the actions a player can make.
*/
enum MazeAction {Left, Right, Up, Down, Generate, Wait};

class MazeController : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
public:

    /*
        Constructor for MazeController.
    */
    explicit MazeController();

    /*
        Destructor for MazeController.
    */
    ~MazeController();

    /*
        Paint a new frame onto the canvas.
    */
    void paint(QPainter* painter) override;

    /*
        Starts the maze generation. To be called by QML after entering the game.
    */
    Q_INVOKABLE void startGame();

    /*
        Move character left action.
    */
    Q_INVOKABLE void leftAction();

    /*
        Move character right action.
    */
    Q_INVOKABLE void rightAction();

    /*
        Move character down action.
    */
    Q_INVOKABLE void downAction();

    /*
        Move character up action.
    */
    Q_INVOKABLE void upAction();

    /*
        Returns whether the game is over or not.
    */
    Q_INVOKABLE bool isGameOver();

signals:
    /*
        Signal to tell QML when the maze is generated.
    */
    void mazeGenerated();

private slots:
    /*
        Main game loop. Called every time a new action has happened.
        Calculates the new game state in response to the action and sends the signal to QML to display it.
    */
    void updateGame();

private:
    // Width of the board in cells
    static const int BOARD_WIDTH = 29;

    // Height of the board in cells
    static const int BOARD_HEIGHT = 59;

    // The current action being performed in the game.
    MazeAction currentAction;

    // Contains the internal representation of the maze grid.
    FlippedArray<std::array<Cell, BOARD_WIDTH>, BOARD_HEIGHT>* board;

    // Contains the position of the player on the board
    std::pair<int, int> playerPos = {1, 0};

    // Contains the list of frontier cells
    std::vector<Cell*> frontierCells;

    // Timer for the game loop
    QTimer frameTimer;

    // Holds how many frames are left before an action is complete.
    int actionFramesLeft;

    // Holds the game over state for the game. No game logic will continue after this is set to true.
    bool gameOver;

    // The main thread used to execute game logic calculations.
    QThread logicThread;

    // Worker for the main thread.
    ThreadWorker logicThreadWorker;

    /*
        Calculates all frontier cells at a given cell and adds them to frontierCells.
    */
    void calculateFrontierCells(const Cell& cell);
};

#endif // MAZECONTROLLER_H
