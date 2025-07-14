/*
    pongdata.h

    File that contains data structures used in the Pong game.
*/

#ifndef PONGDATA_H
#define PONGDATA_H

#include <QDebug>

struct Paddle
{
    qreal x;
    qreal width;
    qreal height;
    bool player2;
};

struct Ball {
    qreal x;
    qreal y;
    qreal width;
    qreal height;
    qreal dx;
    qreal dy;
};

struct AILevel {
    qreal aiReaction;
    qreal aiError;
};

const std::array<AILevel, 13> AILevels = {{
    {1.5,  20}, // 0:  AI is losing by 6; 1.7
    {1.4,  30}, // 1:  AI is losing by 5; 1.6 --
    {1.3,  40}, // 2:  AI is losing by 4; 1.5
    {1.2,  50}, // 3:  AI is losing by 3
    {1.1,  60}, // 4:  AI is losing by 2
    {1.0,  70}, // 5:  AI is losing by 1
    {0.9,  80}, // 6:  Tie
    {0.8,  90}, // 7:  AI is winning by 1; 1.0
    {0.7, 110}, // 8:  AI is winning by 2
    {0.6, 130}, // 9:  AI is winning by 3; .8
    {0.5, 150}, // 10: AI is winning by 4
    {0.4, 170}, // 11: AI is winning by 5
    {0.3, 190}, // 12: AI is winning by 6
}};

struct AI {
    int currentLevel; // Current level based on score difference

    AI() {
        currentLevel = 6; // Start at level 8 (tie)
    }

    void updateLevel(int playerScore, int aiScore) {
        int scoreDifference = aiScore - playerScore;

        // Map the score difference to levels (-6 to +6) -> (0 to 12)
        currentLevel = qBound(0, 6 + scoreDifference, 12);

        // Debug logs
        qDebug() << "Score Difference: " << scoreDifference;
        qDebug() << "Current Level: " << currentLevel;
        qDebug() << "AI Reaction: " << AILevels[currentLevel].aiReaction;
        qDebug() << "AI Error: " << AILevels[currentLevel].aiError;
    }

    qreal getReaction() const {
        return AILevels[currentLevel].aiReaction;
    }

    qreal getError() const {
        return AILevels[currentLevel].aiError;
    }
};

#endif // PONGDATA_H
