/*
    mazecontroller.h

    Class declaration for MazeController.
*/

#ifndef MAZECONTROLLER_H
#define MAZECONTROLLER_H

#include <QObject>
#include <QQuickPaintedItem>
#include "flippedarray.h"

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
    This enum defines all of the actions that can cause a game update. It includes all of the actions a player can make.
*/
enum MazeAction {Left, Right, Up, Down, Generate};

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

private:
    // Width of the board in cells
    static const int BOARD_WIDTH = 29;

    // Height of the board in cells
    static const int BOARD_HEIGHT = 59;

    // Contains the internal representation of the maze grid.
    FlippedArray<std::array<Cell, BOARD_WIDTH>, BOARD_HEIGHT>* board;

    // Contains the list of frontier cells
    std::vector<Cell*> frontierCells;

    // Holds the game over state for the game. No game logic will continue after this is set to true.
    bool gameOver;

    /*
        Main game loop. Called every time a new action has happened.
        Calculates the new game state in response to the action and sends the signal to QML to display it.

        MazeAction trigger: what action is triggering the game update.
    */
    void updateGame(MazeAction trigger);

    /*
        Calculates all frontier cells at a given cell and adds them to frontierCells.
    */
    void calculateFrontierCells(const Cell& cell);
};

#endif // MAZECONTROLLER_H
