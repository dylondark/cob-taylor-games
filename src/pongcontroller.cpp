#include "pongcontroller.h"
#include <QPainter>

/*
    Constructor for PongController
*/
PongController::PongController()
    : QQuickPaintedItem(), gameTimer(QTimer(this))
{
    gameOver = false;
    movingRight = false;
    movingLeft = false;
    score = 0;
    timerInterval = 1000;

    logicThreadWorker.moveToThread(&logicThread);
    logicThread.start(QThread::HighPriority);
}

PongController::~PongController()
{
    // Stop the logic thread
    logicThread.quit();
    logicThread.wait();

    // Delete the dynamically allocated board
    delete board;
}

/*
    Paint a new frame onto the canvas
*/

void PongController::paint(QPainter* painter)
{
    unsigned width = this->width() / 10;
    unsigned height = this->height() / 20;

    for (unsigned row = 0; row < 20; ++row)
        for (unsigned col =0; col < 10; ++col)
            painter->drawRect(width * col, height * row, width, height);
}

/*
    Kicks off the game loop. To be called by QML after entering the game.
*/
void PongController::startGame()
{
    // start timer
    gameTimer.start(1000);
}

/*
    Returns whether game is over or not.
*/
bool PongController::isGameOver()
{
    return gameOver;
}

unsigned PongController::getScore()
{
    return 0;
}

/*
    Slot function that is called when gameTimer ticks. Calls updateGame with the TimerTick action.
*/
void PongController::timerTick()
{
    if (gameOver)
    {
        gameTimer.stop();
        return;
    }

    QMetaObject::invokeMethod(&logicThreadWorker, [&]() {
        updateGame(GameAction::Down);
    });

    gameTimer.setInterval(timerInterval);
}

void PongController::move()
{

}

void PongController::checkCollisions()
{

}

void PongController::aiOperation()
{

}

void PongController::updateGame(GameAction trigger)
{

}
