#include "PongController.h"

PongController::PongController(QObject *parent)
    : QObject(parent),
    m_playerPaddlePosition(400)  // Initial position (adjust based on the screen size)
{
}

// Getter for player's paddle position
int PongController::playerPaddlePosition() const
{
    return m_playerPaddlePosition;
}

// Setter for player's paddle position
void PongController::setPlayerPaddlePosition(int position)
{
    if (m_playerPaddlePosition != position) {
        m_playerPaddlePosition = position;
        emit playerPaddlePositionChanged();  // Notify QML when position changes
    }
}

// Slot to move the paddle left
void PongController::movePaddleLeft()
{
    int newPosition = m_playerPaddlePosition - m_paddleStep;
    if (newPosition >= m_minPosition) {  // Ensure the paddle doesn't move beyond the left bound
        setPlayerPaddlePosition(newPosition);
    }
}

// Slot to move the paddle right
void PongController::movePaddleRight()
{
    int newPosition = m_playerPaddlePosition + m_paddleStep;
    if (newPosition <= m_maxPosition) {  // Ensure the paddle doesn't move beyond the right bound
        setPlayerPaddlePosition(newPosition);
    }
}
