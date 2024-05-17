/*
    tetrooscontroller.h

    Class declaration for TetroosController.
*/

#ifndef TETROOSCONTROLLER_H
#define TETROOSCONTROLLER_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>
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
    explicit TetroosController();

signals:
    //updateBoardState();

private:
    Block board[20][10];
    PieceType holdPiece;
    PieceType currentPiece;
    PieceType nextPiece;
    int score;
    QTimer gameTimer;


};

#endif // TETROOSCONTROLLER_H
