#ifndef PONGCONTROLLER_H
#define PONGCONTROLLER_H

#include <QObject>

class PongController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int playerPaddlePosition READ playerPaddlePosition WRITE setPlayerPaddlePosition NOTIFY playerPaddlePositionChanged)

public:
    explicit PongController(QObject *parent = nullptr);

    // Getter for player's paddle position
    int playerPaddlePosition() const;

    // Setter for player's paddle position
    void setPlayerPaddlePosition(int position);

signals:
    // Signal to notify when player's paddle position changes
    void playerPaddlePositionChanged();

public slots:
    // Slots for moving paddle
    void movePaddleLeft();
    void movePaddleRight();

private:
    int m_playerPaddlePosition;  // Current position of the player paddle
    const int m_paddleStep = 20;  // Distance moved with each press
    const int m_minPosition = 0;  // Minimum position (left bound)
    const int m_maxPosition = 700;  // Maximum position (right bound, adjust based on screen width)
};

#endif // PONGCONTROLLER_H
