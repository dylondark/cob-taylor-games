/*
    mazecontroller.cpp

    Class definition for MazeController.
*/

#include "mazecontroller.h"
#include "qpainter.h"

/*
    Constructor for MazeController.
*/
MazeController::MazeController()
{
    // populate board with empty values
    board = new FlippedArray<std::array<Cell, 20>, 40>;
}

/*
    Destructor for MazeController.
*/
MazeController::~MazeController()
{

}

/*
    Paint a new frame onto the canvas.
*/
void MazeController::paint(QPainter* painter)
{
    painter->setBrush(QBrush(Qt::black));
    painter->drawRect(0, 0, width(), height());
}
