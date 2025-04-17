#ifndef PONGCONTROLLER_H
#define PONGCONTROLLER_H

#include "pongdata.h"
#include "threadworker.h"
#include <QObject>
#include <QQmlEngine>
#include <QQuickPaintedItem>
#include <QImage>
#include <QTimer>
#include <QThread>

class PongController : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

    // Expose playerScore and aiScore as QML properties
    Q_PROPERTY(int playerScore READ getPlayerScore NOTIFY scoreUpdated)
    Q_PROPERTY(int aiScore READ getAIScore NOTIFY scoreUpdated)
public:

    /*
        Constructor for PongController
    */
    explicit PongController();

    /*
        Destructor for PongController
    */
    ~PongController();

    // Getter functions for QML
    int getPlayerScore() const { return playerScore; }
    int getAIScore() const { return aiScore; }

    /*
        Paint a new frame onto the canvas
    */
    void paint(QPainter* painter) override;

    /*
        Kicks off the game loop. To be called by QML after entering the game.
    */
    Q_INVOKABLE void startGame();
    Q_INVOKABLE void moveLeftPaddle1();
    Q_INVOKABLE void moveRightPaddle1();
    Q_INVOKABLE void moveLeftPaddle2();
    Q_INVOKABLE void moveRightPaddle2();

signals:
    /*
        Signal to tell QML when it's time to update the game field
    */
    void updateQML();
    void gameOverSignal(); // <-- Signal for game over
    void scoreUpdated();   // <-- Signal to update score

private:

    QImage soccerBall;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    /*
        Kicks off the game loop. To be called by QML after entering the game.
    */
    void updateGame();

    /*
        The base of the paths. Should be the location of the folder containing the gamefiles folder.
        By default it is "." which (should) mean "wherever the game executable was launched from" but this doesn't always work (ahem, mac).
        Will be set to whatever path is specified with the -p CLI parameter if it is used.
    */
    const QString filepath = ".";

    // the width of the internal game area (this is SEPARATE from the width of the QML canvas)
    const int internalWidth = 1000;

    // the height of the internal game area (this is SEPARATE from the height of the QML canvas)
    const int internalHeight = 2000;

    // The main thread used to execute game logic calculations.
    QThread logicThread;

    // Worker for the main thread.
    ThreadWorker logicThreadWorker;

    /*
        Holds the game over state for the game. No game logic will continue after this is set to true
    */
    bool gameOver;

    /*
        Moves the game objects (ball and paddles) based on their velocities and input
    */
    void move();

    /*
        Checks for collisions between the ball and walls, paddles, and adjusts direction accordingly
    */
    void checkCollisions();

    /*
        Manages AI behavior for the AI paddle ( e.g., tracking ball movement)
    */
    void aiOperation();

    /*
        Player's current score
    */
    unsigned score;

    /*
         The current interval of the timer in ms (how many ms it takes for the piece to fall 1 row naturally).
    */
    unsigned timerInterval;

    int playerScore; // <-- Player's Score
    int aiScore;     // <-- AI's Score

    void timerTick();
    void resetBall();

    Paddle playerPaddle1;
    Paddle playerPaddle2;
    Ball ball;
    AI ai;

    // Timer for the game
    QTimer gameTimer;


    /*
        Main game loop. Called every time a new action has happened.
        Calculates the new game state in response to the action and sends the signal to QML to display it.
    */


    /*
        checks to track player's input for paddle movement
    */
    // True if player is moving paddle right
    bool movingRight;

    // True if player is moving paddle left
    bool movingLeft;


};

#endif // PONGCONTROLLER_H
