#include "pongcontroller.h"
#include <QPainter>

PongController::PongController()
    : gameOver(false), movingRight(false), movingLeft(false)
{

}

PongController::~PongController()
{

}

void PongController::paint(QPainter* painter)
{

}

void PongController::startGame()
{

}

bool PongController::isGameOver()
{
    return gameOver;
}

unsigned PongController::getScore()
{
    return 0;
}

void PongController::timerTick()
{

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
