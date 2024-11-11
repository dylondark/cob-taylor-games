#ifndef PONGCONTROLLER_H
#define PONGCONTROLLER_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickPaintedItem>
#include <QTimer>

class PongController : public QQuickPaintedItem
{
    Q_OBJECT

public:

    /*
        Constructor for PongController
    */
    explicit PongController();

    /*
        Destructor for PongController
    */
    ~PongController();

    /*
        Paint a new frame onto the canvas
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

signals:


public slots:


private:

};

#endif // PONGCONTROLLER_H
