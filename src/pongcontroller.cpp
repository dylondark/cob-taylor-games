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

    soccerField.load(filepath + "/gamefiles/Zoccer/images/soccerField.png");
    soccerBall.load(filepath + "/gamefiles/Zoccer/images/soccerball.png");
    if (soccerField.isNull()) {
        qDebug() << "Failed to load soccer field image.";
    }
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
    // Scale factors
    qreal scaleX = width() / internalWidth;
    qreal scaleY = height() / internalHeight;

    // Background; draw soccer field image
    if (!soccerField.isNull()){
        QRectF fieldRect(0, 0, width(), height());
        painter->drawImage(fieldRect, soccerField, QRectF(0, 0, soccerField.width(), soccerField.height()));
    } else {
        // Fallback to green background
        painter->setBrush(QBrush(Qt::darkGreen));
        painter->drawRect(0, 0, width(), height());
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


// void PongController::checkCollisions()
// {
//     QRectF ballRect(ball.x, ball.y, ball.width, ball.height);

//     // Bounce off top and bottom
//     if (ball.y <= 0 || ball.y + ball.height >= internalHeight) {
//         ball.dy = -ball.dy;
//     }

//     // Bounce off left and right
//     if (ball.x <= 0 || ball.x + ball.width >= internalWidth) {
//         ball.dx = -ball.dx;
//     }

//     // Player 1 paddle (bottom)
//     QRectF paddle1Rect(
//         playerPaddle1.x,
//         internalHeight - playerPaddle1.height - 10,
//         playerPaddle1.width,
//         playerPaddle1.height
//         );

//     if (ballRect.intersects(paddle1Rect)) {
//         ball.dy = -qAbs(ball.dy);
//         ball.y = paddle1Rect.top() - ball.height;

//         // 🔥 Increase speed by 25%
//         ball.dx *= 1.25;
//         ball.dy *= 1.25;
//         qDebug() << " bottom paddle";
//     }

//     // Player 2 paddle (top)
//     QRectF paddle2Rect(
//         playerPaddle2.x,
//         10,
//         playerPaddle2.width,
//         playerPaddle2.height
//         );

//     if (ballRect.intersects(paddle2Rect)) {
//         ball.dy = qAbs(ball.dy);
//         ball.y = paddle2Rect.bottom();

//          // 🔥 Increase speed by 25%
//         ball.dx *= 1.25;
//         ball.dy *= 1.25;
//         qDebug() << "top paddle";
//     }

//     // Scoring logic
//     if (ball.y + ball.height >= internalHeight) {
//         aiScore++;
//         emit scoreUpdated();

//         if (aiScore >= 7) {
//             // AI (Zippy) wins
//             gameOver = true;
//             gameTimer.stop();
//             emit gameOverSignal();      // notify QML
//             return;
//         }

//         resetBall(); // Reset ball after score
//         return;
//     }

//     if (ball.y <= 0) {
//         playerScore++;
//         emit scoreUpdated();
//         if (playerScore >= 7) {
//             // Player wins
//             gameOver = true;
//             gameTimer.stop();
//             emit gameOverSignal();      // notify QML
//             return;
//         }
//         resetBall(); // Reset ball after score
//         return;
//     }

// }

void PongController::checkCollisions()
{
    QRectF ballRect(ball.x, ball.y, ball.width, ball.height);

    // 🔹 Step 1: Check scoring before anything else
    if (ball.y + ball.height >= internalHeight) {
        aiScore++;
        emit scoreUpdated();

        if (aiScore >= 7) {
            gameOver = true;
            gameTimer.stop();
            emit gameOverSignal();
            return;
        }

        resetBall();
        return;
    }

    if (ball.y <= 0) {
        playerScore++;
        emit scoreUpdated();

        if (playerScore >= 7) {
            gameOver = true;
            gameTimer.stop();
            emit gameOverSignal();
            return;
        }

        resetBall();
        return;
    }

    // 🔹 Step 2: Bounce off walls (left/right)
    if (ball.x <= 0 || ball.x + ball.width >= internalWidth) {
        ball.dx = -ball.dx;
    }

    // 🔹 Step 3: Paddle collisions

    // Player 1 (bottom paddle)
    // QRectF paddle1Rect(
    //     playerPaddle1.x,
    //     internalHeight - playerPaddle1.height - 10,
    //     playerPaddle1.width,
    //     playerPaddle1.height
    //     );

    // if (ballRect.intersects(paddle1Rect)) {
    //     qreal paddleCenter = playerPaddle1.x + playerPaddle1.width / 2.0;
    //     qreal ballCenter = ball.x + ball.width / 2.0;
    //     qreal offset = (ballCenter - paddleCenter) / (playerPaddle1.width / 2.0);

    //     ball.dy = -qAbs(ball.dy);
    //     ball.dx = offset * 16.0;

    //     if (movingLeft || movingRight) {
    //         ball.dy *= 1.2;
    //     }

    //     ball.y = paddle1Rect.top() - ball.height;
    //     qDebug() << "Hit bottom paddle | offset:" << offset << " dx:" << ball.dx << " dy:" << ball.dy;
    // }

    // Player 2 (top paddle)
    // QRectF paddle2Rect(
    //     playerPaddle2.x,
    //     10,
    //     playerPaddle2.width,
    //     playerPaddle2.height
    //     );

    // if (ballRect.intersects(paddle2Rect)) {
    //     qreal paddleCenter = playerPaddle2.x + playerPaddle2.width / 2.0;
    //     qreal ballCenter = ball.x + ball.width / 2.0;
    //     qreal offset = (ballCenter - paddleCenter) / (playerPaddle2.width / 2.0);

    //     ball.dy = qAbs(ball.dy);
    //     ball.dx = offset * 16.0;

    //     ball.dy *= 1.2;
    //     ball.y = paddle2Rect.bottom();
    //     qDebug() << "Hit top paddle | offset:" << offset << " dx:" << ball.dx << " dy:" << ball.dy;
    // }

    //New Paddle code

    // Player 1 (bottom paddle)
    QRectF paddle1Rect(
        playerPaddle1.x,
        internalHeight - playerPaddle1.height - 10,
        playerPaddle1.width,
        playerPaddle1.height
        );

    if (ballRect.intersects(paddle1Rect)) {
        qreal paddleCenter = playerPaddle1.x + playerPaddle1.width / 2.0;
        qreal ballCenter = ball.x + ball.width / 2.0;
        qreal offset = (ballCenter - paddleCenter) / (playerPaddle1.width / 2.0);

        ball.dy = -qAbs(ball.dy);
        ball.dx = offset * 16.0;

        if (movingLeft || movingRight) {
            ball.dy *= 1.2;
        }

        // Cap max ball speed
        qreal maxBallSpeed = 28.0;
        qreal currentSpeed = std::sqrt(ball.dx * ball.dx + ball.dy * ball.dy);
        if (currentSpeed > maxBallSpeed) {
            qreal scale = maxBallSpeed / currentSpeed;
            ball.dx *= scale;
            ball.dy *= scale;
        }

        ball.y = paddle1Rect.top() - ball.height;
        qDebug() << "Hit bottom paddle | offset:" << offset << " dx:" << ball.dx << " dy:" << ball.dy;
        qDebug() << "⚡ Ball speed after hit:" << std::sqrt(ball.dx * ball.dx + ball.dy * ball.dy);

    }


    // Player 2 (top paddle)
    QRectF paddle2Rect(
        playerPaddle2.x,
        10,
        playerPaddle2.width,
        playerPaddle2.height
        );

    if (ballRect.intersects(paddle2Rect)) {
        qreal paddleCenter = playerPaddle2.x + playerPaddle2.width / 2.0;
        qreal ballCenter = ball.x + ball.width / 2.0;
        qreal offset = (ballCenter - paddleCenter) / (playerPaddle2.width / 2.0);

        ball.dy = qAbs(ball.dy);
        ball.dx = offset * 16.0;

        ball.dy *= 1.2;

        // Cap max ball speed
        qreal maxBallSpeed = 28.0;
        qreal currentSpeed = std::sqrt(ball.dx * ball.dx + ball.dy * ball.dy);
        if (currentSpeed > maxBallSpeed) {
            qreal scale = maxBallSpeed / currentSpeed;
            ball.dx *= scale;
            ball.dy *= scale;
        }

        ball.y = paddle2Rect.bottom();
        qDebug() << "Hit top paddle | offset:" << offset << " dx:" << ball.dx << " dy:" << ball.dy;
        qDebug() << "⚡ Ball speed after hit:" << std::sqrt(ball.dx * ball.dx + ball.dy * ball.dy);

    }


}

qreal calculateBounceAdjustedX(qreal startX, qreal dx, qreal time, qreal fieldWidth) {
    while (time > 0) {
        // Time until next wall hit
        qreal timeToWall = (dx > 0) ? (fieldWidth - startX) / dx : (-startX) / dx;
        timeToWall = qMax(timeToWall, 0.0); // Clamp to positive

        if (timeToWall >= time) {
            // No more bounces within remaining time
            return startX + dx * time;
        } else {
            // Advance to wall and bounce
            startX += dx * timeToWall;
            dx = -dx; // Reverse direction
            time -= timeToWall;
        }
    }
    return startX;
}

// void PongController::aiOperation()
// {
//     if (ball.dy >= 0) return; // Ball moving toward player

//     static qreal aiEdgeBias = 0.0;
//     static qreal lastMovement = 0.0;

//     // 1. Update edge bias when needed
//     if (ball.y > internalHeight * 0.75) {
//         aiEdgeBias = QRandomGenerator::global()->generateDouble() * 0.6 - 0.3;
//         qDebug() << "AI edge bias updated:" << aiEdgeBias;
//     }

//     // 2. Calculate pure ball prediction (no errors/biases yet)
//     qreal timeToIntercept = (10 - ball.y) / abs(ball.dy);
//     qreal idealInterceptX = calculateBounceAdjustedX(ball.x, ball.dx, timeToIntercept, internalWidth);

//     // 3. Calculate adjustments separately
//     qreal errorOffset = ai.getError(); //* 0.7 * (QRandomGenerator::global()->generateDouble() - 0.5);
//     qreal edgeOffset = aiEdgeBias * playerPaddle2.width * 0.4;

//     // 4. Combine components for final target
//     qreal targetX = idealInterceptX + errorOffset + edgeOffset;
//     targetX = qBound(0.0, targetX, internalWidth - playerPaddle2.width);

//     // 5. Calculate movement toward target
//     qreal paddleCenter = playerPaddle2.x + (playerPaddle2.width / 2);
//     qreal desiredMovement = (targetX - paddleCenter) * ai.getReaction();

//     // 6. Apply movement smoothing
//     qreal movement = 0.7 * desiredMovement + 0.3 * lastMovement;
//     lastMovement = movement;

//     // 7. Enforce speed limits
//     qreal maxSpeed = 10.0 * (0.3 - ai.getReaction()/1.5);
//     movement = qBound(-fabs(maxSpeed), movement, fabs(maxSpeed));

//     // 8. Update paddle position
//     playerPaddle2.x += movement;
//     playerPaddle2.x = qBound(0.0, playerPaddle2.x, internalWidth - playerPaddle2.width);

//     // Debug with clear separation
//     qDebug() << "AI decision:"
//              << "Ideal:" << idealInterceptX
//              << "Error:" << errorOffset
//              << "Bias:" << edgeOffset
//              << "FinalTarget:" << targetX
//              << "Movement:" << movement;
// }
qreal capSpeed(qreal dx, qreal dy, qreal maxSpeed) {
    qreal speed = std::sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed) {
        qreal scale = maxSpeed / speed;
        dx *= scale;
        dy *= scale;
    }
    return speed; // Optional return, or just update dx/dy directly
}

void PongController::aiOperation()
{
    if (ball.dy >= 0 || qAbs(ball.dy) < 0.1)
        return;

    static qreal aiEdgeBias = 0.0;
    static qreal lastMovement = 0.0;

    if (ball.y > internalHeight * 0.75) {
        aiEdgeBias = QRandomGenerator::global()->generateDouble() * 0.6 - 0.3;
        qDebug() << "AI edge bias updated:" << aiEdgeBias;
    }

    qreal timeToIntercept = (10 - ball.y) / std::abs(ball.dy);
    qreal idealInterceptX = calculateBounceAdjustedX(ball.x, ball.dx, timeToIntercept, internalWidth);

    qreal errorOffset = ai.getError();
    qreal edgeOffset = aiEdgeBias * playerPaddle2.width * 0.4;

    qreal targetX = idealInterceptX + errorOffset + edgeOffset;
    targetX = qBound(0.0, targetX, internalWidth - playerPaddle2.width);

    qreal paddleCenter = playerPaddle2.x + playerPaddle2.width / 2;
    qreal desiredMovement = (targetX - paddleCenter) * ai.getReaction();

    // Smooth movement
    qreal movement = 0.7 * desiredMovement + 0.3 * lastMovement;
    lastMovement = movement;

    // Dynamic speed boost based on player score lead
    int scoreDiff = playerScore - aiScore;
    scoreDiff = qBound(-5, scoreDiff, 5);
    qreal maxSpeed = qBound(8.0, 8.0 + (scoreDiff * 0.6), 12.0);

    movement = qBound(-maxSpeed, movement, maxSpeed);
    playerPaddle2.x += movement;

    playerPaddle2.x = qBound(0.0, playerPaddle2.x, internalWidth - playerPaddle2.width);

    qDebug() << "AI decision:"
             << "TargetX:" << targetX
             << "Move:" << movement
             << "ScoreDiff:" << scoreDiff;
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
    /*
    if (playerScore == 7 || aiScore==7)
    {
        gameOver = true;
        emit gameOverSignal();      // notify QML
        return;
    }
    */
    // Set speed to original value (8 units)
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
