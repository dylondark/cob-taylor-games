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

    soccerBall.load(filepath + "/gamefiles/Zoccer/images/soccerball.png");
    if (soccerBall.isNull()) {
        qDebug() << "Failed to load soccer ball image.";
    }

    playerPaddle1 = {
        static_cast<qreal>(internalWidth) / 2 - 200,
        400,
        60,
        false
    };

    playerPaddle2 = {
        static_cast<qreal>(internalWidth) / 2 - 200,
        400,
        60,
        true
    };


    ball = {
        static_cast<qreal>(internalWidth) / 2 - 35,
        static_cast<qreal>(internalHeight) / 2 - 35,
        80, 80, 8, 8
    };


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

    //startGame();
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
    // Background
    painter->setBrush(QBrush(Qt::darkGreen));
    painter->drawRect(0, 0, width(), height());

    // Scale factors
    qreal scaleX = width() / internalWidth;
    qreal scaleY = height() / internalHeight;

    // Draw center dotted line
    painter->setPen(QPen(Qt::white, 2, Qt::DashLine));
    int centerY = height() / 2;
    int dotWidth = 5;
    int dotSpacing = 15;
    for (int x = 0; x < width(); x += dotWidth + dotSpacing) {
        painter->drawRect(x, centerY - 1, dotWidth, 2);
    }

    // Reset the pen to remove white border effect
    painter->setPen(Qt::NoPen);


    // Draw Player 1 paddle (bottom)
    painter->setBrush(Qt::blue);
    painter->drawRect(
        playerPaddle1.x * scaleX,
        (internalHeight - playerPaddle1.height - 10) * scaleY,
        playerPaddle1.width * scaleX,
        playerPaddle1.height * scaleY
        );

    // Draw Player 2 paddle (top)
    painter->setBrush(Qt::red);
    painter->drawRect(
        playerPaddle2.x * scaleX,
        10 * scaleY,
        playerPaddle2.width * scaleX,
        playerPaddle2.height * scaleY
        );

    // Draw ball (image if available, else fallback)
    QRectF scaledBallRect(
        ball.x * scaleX,
        ball.y * scaleY,
        ball.width * scaleX,
        ball.height * scaleY
        );

    if (!soccerBall.isNull()) {
        painter->drawImage(scaledBallRect, soccerBall, QRectF(0, 0, soccerBall.width(), soccerBall.height()));
    } else {
        painter->setBrush(Qt::black);
        painter->drawEllipse(scaledBallRect);
    }
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
    default:
        QQuickPaintedItem::keyPressEvent(event);
    }
}


void PongController::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_S:
        // No continuous movement required, so do nothing.
        break;
    default:
        QQuickPaintedItem::keyReleaseEvent(event);
    }
}

//moves paddle 1 and 2 left and right

void PongController::moveLeftPaddle1() {
    if (playerPaddle1.x > 0) {
        playerPaddle1.x -= 30; // Move in internal units
        if (playerPaddle1.x < 0)
            playerPaddle1.x = 0;
    }
    update();
}

void PongController::moveRightPaddle1() {
    if (playerPaddle1.x + playerPaddle1.width < internalWidth) {
        playerPaddle1.x += 30;
        if (playerPaddle1.x + playerPaddle1.width > internalWidth)
            playerPaddle1.x = internalWidth - playerPaddle1.width;
    }
    update();
}

void PongController::moveLeftPaddle2() {
    if (playerPaddle2.x > 0) {
        playerPaddle2.x -= 30;
        if (playerPaddle2.x < 0)
            playerPaddle2.x = 0;
    }
    update();
}

void PongController::moveRightPaddle2() {
    if (playerPaddle2.x + playerPaddle2.width < internalWidth) {
        playerPaddle2.x += 30;
        if (playerPaddle2.x + playerPaddle2.width > internalWidth)
            playerPaddle2.x = internalWidth - playerPaddle2.width;
    }
    update();
}


void PongController::checkCollisions()
{
    QRectF ballRect(ball.x, ball.y, ball.width, ball.height);

    // Bounce off top and bottom
    if (ball.y <= 0 || ball.y + ball.height >= internalHeight) {
        ball.dy = -ball.dy;
    }

    // Bounce off left and right
    if (ball.x <= 0 || ball.x + ball.width >= internalWidth) {
        ball.dx = -ball.dx;
    }

    // Player 1 paddle (bottom)
    QRectF paddle1Rect(
        playerPaddle1.x,
        internalHeight - playerPaddle1.height - 10,
        playerPaddle1.width,
        playerPaddle1.height
        );

    if (ballRect.intersects(paddle1Rect)) {
        ball.dy = -qAbs(ball.dy);
        ball.y = paddle1Rect.top() - ball.height;

        // 🔥 Increase speed by 5%
        ball.dx *= 1.25;
        ball.dy *= 1.25;
        qDebug() << " bottom paddle";
    }

    // Player 2 paddle (top)
    QRectF paddle2Rect(
        playerPaddle2.x,
        10,
        playerPaddle2.width,
        playerPaddle2.height
        );

    if (ballRect.intersects(paddle2Rect)) {
        ball.dy = qAbs(ball.dy);
        ball.y = paddle2Rect.bottom();

        ball.dx *= 1.25;
        ball.dy *= 1.25;
        qDebug() << "top paddle";
    }

    // Scoring logic
    if (ball.y + ball.height >= internalHeight) {
        aiScore++;
        emit scoreUpdated();

        if (aiScore >= 7) {
            // AI (Zippy) wins
            gameOver = true;
            gameTimer.stop();
            emit gameOverSignal();      // notify QML
            return;
        }

        resetBall(); // Reset ball after score
        return;
    }

    if (ball.y <= 0) {
        playerScore++;
        emit scoreUpdated();
        if (playerScore >= 7) {
            // Player wins
            gameOver = true;
            gameTimer.stop();
            emit gameOverSignal();      // notify QML
            return;
        }
        resetBall(); // Reset ball after score
        return;
    }

}


void PongController::aiOperation()
{
    if (ball.dy >= 0) return; // Ball moving away

    qreal paddleY = 10;
    qreal deltaY = paddleY - ball.y;
    qreal timeToIntersect = deltaY / ball.dy;
    qreal predictedX = ball.x + (ball.dx * timeToIntersect);

    // Add AI error
    qreal error = ai.getError() * 0.5;
    predictedX += error;

    // Clamp prediction to internal width
    if (predictedX < 0) predictedX = 0;
    if (predictedX > internalWidth) predictedX = internalWidth;

    qreal paddleCenterX = playerPaddle2.x + (playerPaddle2.width / 2);
    qreal deltaX = predictedX - paddleCenterX;

    qreal movement = deltaX * ai.getReaction();
    qreal maxSpeed = 5.0;
    movement = qBound(-maxSpeed, movement, maxSpeed);

    playerPaddle2.x += movement;

    // Enforce boundaries using internal width
    if (playerPaddle2.x < 0) playerPaddle2.x = 0;
    if (playerPaddle2.x > internalWidth - playerPaddle2.width)
        playerPaddle2.x = internalWidth - playerPaddle2.width;
}

void PongController::updateGame()
{
    if (gameOver)
        return;

    ball.x += ball.dx;
    ball.y += ball.dy;

    aiOperation();
    checkCollisions();

    QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
}


void PongController::resetBall()
{
    ball.x = width() / 2 - ball.width / 2;
    ball.y = height() / 2 - ball.height / 2;
    if (playerScore == 7 || aiScore==7)
    {
        gameOver = true;
        emit gameOverSignal();      // notify QML
        return;
    }
    // Set speed to original value (2 units)
    ball.dx = 8;
    ball.dy = 8;

    ai.updateLevel(playerScore, aiScore); // Update AI difficulty
}
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
