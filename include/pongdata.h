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

const std::array<AILevel, 17> AILevels = {{
    {1.7,  20}, // 0:  AI is losing by 8; 1.7
    {1.6,  30}, // 1:  AI is losing by 7; 1.6
    {1.5,  40}, // 2:  AI is losing by 6; 1.5
    {1.4,  50}, // 3:  AI is losing by 5
    {1.3,  60}, // 4:  AI is losing by 4
    {1.2,  70}, // 5:  AI is losing by 3
    {1.1,  80}, // 6:  AI is losing by 2
    {1.0,  90}, // 7:  AI is losing by 1; 1.0
    {0.9, 100}, // 8:  Tie
    {0.8, 110}, // 9:  AI is winning by 1; .8
    {0.7, 120}, // 10: AI is winning by 2
    {0.6, 130}, // 11: AI is winning by 3
    {0.5, 140}, // 12: AI is winning by 4
    {0.4, 150}, // 13: AI is winning by 5
    {0.3, 160}, // 14: AI is winning by 6; .3
    {0.2, 170}, // 15: AI is winning by 7; .2
    {0.1, 180}  // 16: AI is winning by 8; .1
}};

struct AI {
    int currentLevel; // Current level based on score difference

    AI() {
        currentLevel = 8; // Start at level 8 (tie)
    }

    void updateLevel(int playerScore, int aiScore) {
        int scoreDifference = aiScore - playerScore;

        // Map the score difference to a level (0 to 16)
        currentLevel = 8 + scoreDifference; // 8 is the tie level
        if (currentLevel < 0) currentLevel = 0;
        if (currentLevel > 16) currentLevel = 16;

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
