#ifndef PONGCONTROLLER_H
#define PONGCONTROLLER_H

#include "threadworker.h"
#include <QObject>
#include <QQmlEngine>
#include <QQuickPaintedItem>
#include <QTimer>
#include <QThread>

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
    /*
        Signal to tell QML when it's time to update the game field
    */
    void updateField();

private slots:

    /*
        Slot function that is called when gameTimer ticks.
    */
    void timerTick();

private:

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

    std::vector<std::vector<int>>* board = new std::vector<std::vector<int>>();

    //Paddle playerPaddle;
    //Paddle aiPaddle;
    //Ball ball;
    //AI ai;

    // Timer for the game
    QTimer gameTimer;

    /*
        Main game loop. Called every time a new action has happened.
        Calculates the new game state in response to the action and sends the signal to QML to display it.
    */
    void updateGame();

    /*
        checks to track player's input for paddle movement
    */
    // True if player is moving paddle right
    bool movingRight;

    // True if player is moving paddle left
    bool movingLeft;



};

#endif // PONGCONTROLLER_H
