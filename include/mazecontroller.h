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

private:
    // Contains the internal representation of the maze grid.
    FlippedArray<std::array<Cell, 20>, 40>* board;

    /*
        Main game loop. Called every time a new action has happened.
        Calculates the new game state in response to the action and sends the signal to QML to display it.

        MazeAction trigger: what action is triggering the game update.
    */
    void updateGame(MazeAction trigger);
};

#endif // MAZECONTROLLER_H
