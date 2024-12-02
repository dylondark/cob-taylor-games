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
    timerInterval = 16; // ~60fps

    // Connect timer
    connect(&gameTimer, &QTimer::timeout, this, &PongController::timerTick);


    // Initialize both paddles
    playerPaddle1 = {10, 100, 20, false}; // x-position, width, height, isPlayer2
    playerPaddle2 = {10, 100, 20, true};     // x-position, width, height, isPlayer2

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

    // Draw paddles
    painter->setBrush(QBrush(Qt::blue)); // Set paddle color for player
    painter->drawRect(playerPaddle1.x, height() - playerPaddle1.height - 10,
                      playerPaddle1.width, playerPaddle1.height);

    painter->setBrush(QBrush(Qt::red)); // Set paddle color for AI
    painter->drawRect(width() - playerPaddle2.x - playerPaddle2.width, 10,
                      playerPaddle2.width, playerPaddle2.height);
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

//moves paddle 1 and 2 left and right

void PongController::moveLeftPaddle1() {
    if (playerPaddle1.x > 0) {
        playerPaddle1.x -= 10; // Move left by 10 units
    }
    update();
}

void PongController::moveRightPaddle1() {
    if (playerPaddle1.x < width() - playerPaddle1.width) {
        playerPaddle1.x += 10; // Move right by 10 units
    }
    update();
}

void PongController::moveLeftPaddle2() {
    if (playerPaddle2.x < width() - playerPaddle2.width) {
        playerPaddle2.x += 10; // Move right by 10 units
    }
    update();

}

void PongController::moveRightPaddle2() {
    if (playerPaddle2.x > 0) {
        playerPaddle2.x -= 10; // Move left by 10 units
    }
    update();

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
        updateGame();
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

void PongController::updateGame()
{

}
