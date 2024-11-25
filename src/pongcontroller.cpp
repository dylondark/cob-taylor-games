#include "pongcontroller.h"
#include "cliparser.h"
#include <QPainter>

/*
    Constructor for PongController
*/
PongController::PongController()
    : QQuickPaintedItem(), gameTimer(QTimer(this)), filepath(CliParser::getPath())
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

}

/*
    Paint a new frame onto the canvas
*/

void PongController::paint(QPainter* painter)
{
    painter->setBrush(QBrush(Qt::darkGreen)); // Set brush color
    painter->drawRect(0, 0, width(), height());

    // Draw the dotted horizontal line
    painter->setPen(QPen(Qt::white, 2)); // Set pen color and thickness
    int dotWidth = 5;                   // Width of each dot
    int dotHeight = 1;                   // Height of each dot
    int dotSpacing = 15;                 // Space between dots

    int centerY = height() / 2;          // Vertical center of the board
    for (int x = 0; x < width(); x += dotWidth + dotSpacing) {
        painter->drawRect(x, centerY - dotHeight / 2, dotWidth, dotHeight);
    }
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
