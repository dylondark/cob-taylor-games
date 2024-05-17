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
    Q_INVOKABLE bool isGameOver();
    Q_INVOKABLE QImage getTextureAt(int posX, int posY);
    Q_INVOKABLE int getScore();
    Q_INVOKABLE PieceType getHoldPiece();
    Q_INVOKABLE PieceType getCurrentPiece();
    Q_INVOKABLE PieceType getNextPiece();
    Q_INVOKABLE void left();
    Q_INVOKABLE void right();
    Q_INVOKABLE void down();
    Q_INVOKABLE void rotateCW();
    Q_INVOKABLE void rotateCCW();
    Q_INVOKABLE void slam();
    Q_INVOKABLE void hold();

signals:
    void updateView();

private:
    bool gameOver;
    Block board[20][10];
    PieceType holdPiece;
    PieceType currentPiece;
    PieceType nextPiece;
    int score;
    int activePieceID;
    QTimer gameTimer;
    QImage textures[21];

    void updateGame(GameAction trigger);
    bool mergePieceLeft();
    bool mergePieceRight();
    bool mergePieceDown();
    void calculateNextPiece();
};

#endif // TETROOSCONTROLLER_H
