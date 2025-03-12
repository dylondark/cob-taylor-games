#include "pongcontroller.h"
#include "cliparser.h"
#include <QPainter>
#include <QKeyEvent>
#include <QRandomGenerator>

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
    playerScore = 0;
    aiScore = 0;

    // Initialize AI
    ai = AI();

    // Connect timer
    connect(&gameTimer, &QTimer::timeout, this, &PongController::timerTick);

    // Initialize ball properties
    ballX = 0;
    ballY = 0;
    ballWidth = 20;
    ballHeight = 20;
    ballVelocityX = 2;
    ballVelocityY = 2;

    // Initialize both paddles
    playerPaddle1 = {10, 100, 20, false};
    playerPaddle2 = {10, 100, 20, true};

    // Ensure PongController can receive key events
    setFlag(QQuickItem::ItemHasContents, true);
    setFlag(QQuickItem::ItemIsFocusScope, true);
    setFocus(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
    setFlag(QQuickItem::ItemAcceptsInputMethod, true);  // Ensure input is accepted

    // Manually set active focus (force focus on startup)
    QMetaObject::invokeMethod(this, "forceActiveFocus", Qt::QueuedConnection);
    // Debugging focus
    qDebug() << "PongController focus status (constructor): " << hasActiveFocus();


    QTimer::singleShot(100, this, [this]() {
        qDebug() << "PongController focus status (constructor after invoke): " << hasActiveFocus();
    });

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

    // /// Initialize ball position on first paint with valid dimensions
    if ((ballX == 0 && ballY == 0) && (width() > 0 && height() > 0)) {
        ballX = width() / 2 - ballWidth / 2;
         ballY = height() / 2 - ballHeight / 2;
    }

    updateGame();

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

    // Draw the ball
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(ballX, ballY, ballWidth, ballHeight));
}

/*
    Kicks off the game loop. To be called by QML after entering the game.
*/
void PongController::startGame()
{
    // start timer


    gameTimer.start(16);

    update();

}

#include <QKeyEvent>

void PongController::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "Key Pressed: " << event->key();  // Debugging
    if (!hasActiveFocus()) {
        qDebug() << "PongController does NOT have focus! Ignoring key press.";
        return;
    }

    switch (event->key()) {
    case Qt::Key_A:
        qDebug() << "Moving Player Paddle Left";
        moveLeftPaddle1();
        break;
    case Qt::Key_S:
        qDebug() << "Moving Player Paddle Right";
        moveRightPaddle1();
        break;
    case Qt::Key_Left:
        qDebug() << "Moving AI Paddle Left";
        moveLeftPaddle2();
        break;
    case Qt::Key_Right:
        qDebug() << "Moving AI Paddle Right";
        moveRightPaddle2();
        break;
    default:
        QQuickPaintedItem::keyPressEvent(event);
    }
}


void PongController::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_S:
    case Qt::Key_Left:
    case Qt::Key_Right:
        // No continuous movement required, so do nothing.
        break;
    default:
        QQuickPaintedItem::keyReleaseEvent(event);
    }
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
        playerPaddle2.x -= 10;

    }
    update();


}




unsigned PongController::getScore()
{
    return 0;
}

// /*
//     Slot function that is called when gameTimer ticks. Calls updateGame with the TimerTick action.
// */
// void PongController::timerTick()
// {
//     if (gameOver)
//     {
//         gameTimer.stop();
//         return;
//     }

//     QMetaObject::invokeMethod(&logicThreadWorker, [&]() {
//         updateGame();
//     });

//     gameTimer.setInterval(timerInterval);
// }

void PongController::move()
{

}


void PongController::checkCollisions()
{
    // Define ball rectangle for collision detection
    QRectF ballRect(ballX, ballY, ballWidth, ballHeight);

    // **Check if the ball missed a paddle (scoring condition)**
    if (ballY + ballHeight >= height()) { // Player missed, AI scores
        aiScore++;
        emit scoreUpdated();
        qDebug() << "AI Scores! Player: " << playerScore << " - AI: " << aiScore;
        resetBall();
        ai.updateLevel(playerScore, aiScore); // Update AI difficulty
        return; // Exit function to avoid further updates
    }

    if (ballY <= 0) { // AI missed, Player scores
        playerScore++;
        emit scoreUpdated();
        qDebug() << "Player Scores! Player: " << playerScore << " - AI: " << aiScore;
        resetBall();
        ai.updateLevel(playerScore, aiScore); // Update AI difficulty
        return; // Exit function to avoid further updates
    }

    // **End game if any player reaches 5 points**
    if (playerScore >= 9 || aiScore >= 9) {
        gameOver = true;
        gameTimer.stop();
        emit gameOverSignal();
        qDebug() << "Game Over! Final Score -> Player: " << playerScore << " - AI: " << aiScore;
        return;
    }

    // **Bounce off the left and right walls**
    if (ballX <= 0 || ballX + ballWidth >= width()) {
        ballVelocityX = -ballVelocityX; // Reverse X direction
    }

    // **Check collision with Player's Paddle (bottom paddle)**
    QRectF paddle1Rect(playerPaddle1.x,
                       height() - playerPaddle1.height - 10,
                       playerPaddle1.width,
                       playerPaddle1.height);

    if (ballRect.intersects(paddle1Rect)) {
        qDebug() << "Collision with Player 1 Paddle!";
        ballVelocityY = -ballVelocityY; // Reverse Y direction
        ballY = paddle1Rect.top() - ballHeight - 1; // Prevent sticking
    }

    // **Check collision with AI's Paddle (top paddle)**
    QRectF paddle2Rect(width() - playerPaddle2.x - playerPaddle2.width,
                       10,
                       playerPaddle2.width,
                       playerPaddle2.height);

    if (ballRect.intersects(paddle2Rect)) {
        qDebug() << "Collision with Player 2 Paddle!";
        ballVelocityY = -ballVelocityY; // Reverse Y direction
        ballY = paddle2Rect.bottom() + 1; // Prevent sticking

    }
}




void PongController::aiOperation()
{
    // Only predict if the ball is moving towards the AI paddle
    if (ballVelocityY >= 0) {
        return; // Ball is moving away from the AI paddle
    }

    // Predict where the ball will intersect with the AI paddle's Y position
    qreal paddleY = 10; // Y position of the AI paddle (top paddle)
    qreal deltaY = paddleY - ballY; // Vertical distance between ball and paddle
    qreal timeToIntersect = deltaY / ballVelocityY; // Time until ball reaches paddle

    // Predict the ball's X position at the intersection point
    qreal predictedX = ballX + (ballVelocityX * timeToIntersect);

    // add some randomness to the prediction based onAI error
    qreal error = ai.getError() * 0.5 * (QRandomGenerator::global()->generateDouble() - 0.5);
    predictedX += error;

    // Ensure the predicted position is within the game bounds
    if (predictedX < 0) predictedX = 0;
    if (predictedX > width()) predictedX = width();

    // Calculate the center of the AI paddle
    qreal paddleCenterX = playerPaddle2.x + (playerPaddle2.width / 2);

    // Move the AI paddle towards the predicted position
    qreal interpolationFactor = ai.getReaction(); // use AI reaction time for smooth movement
    qreal deltaX = predictedX - paddleCenterX;
    qreal movement = deltaX * interpolationFactor;

    // Limit the paddle's speed to avoid glitchy movement
    qreal maxSpeed = 5.0; // Adjust this value as needed
    if (movement > maxSpeed) movement = maxSpeed;
    if (movement < -maxSpeed) movement = -maxSpeed;

    // Update the paddle's position using floating-point precision
    playerPaddle2.x += movement;

    // Prevent the AI paddle from moving out of bounds
    if (playerPaddle2.x < 0) playerPaddle2.x = 0;
    if (playerPaddle2.x > width() - playerPaddle2.width) playerPaddle2.x = width() - playerPaddle2.width;

    update();
}

void PongController::updateGame()
{
    if (gameOver)
        return; // Stop updating if the game is over

    // Update AI difficulty
    ai.updateLevel(playerScore, aiScore);

    // Move the ball
    ballX += ballVelocityX;
    ballY += ballVelocityY;

    // Update AI paddle position
    aiOperation();

    // Check for collisions
    checkCollisions();

    // Trigger a repaint
    update();
}

void PongController::resetBall()
{
    ballX = width() / 2 - ballWidth / 2;
    ballY = height() / 2 - ballHeight / 2;

    // Set speed to original value (2 units)
    ballVelocityX = (rand() % 2 == 0) ? 2 : -2;
    ballVelocityY = (rand() % 2 == 0) ? 2 : -2;

    update();
}

void PongController::timerTick()
{
    if (gameOver)
    {
        gameTimer.stop();
        return;
    }

    // Update AI paddle position
    aiOperation();

    QMetaObject::invokeMethod(&logicThreadWorker, [&]() {
        updateGame();
    });

    gameTimer.setInterval(timerInterval);
}

unsigned PongController::getPlayerScore()
{
    return playerScore;
}

unsigned PongController::getAIScore()
{
    return aiScore;
}



