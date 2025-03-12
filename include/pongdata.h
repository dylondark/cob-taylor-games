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
    int width;
    int height;
    bool player2;
};

struct Ball {
    int x;
    int y;
    int radius;
    int dx;
    int dy;
};

struct AILevel {
    qreal aiReaction;
    qreal aiError;
};

const std::array<AILevel, 17> AILevels = {{
    {0.2,  40}, // 0:  AI is losing by 8
    {0.3,  50}, // 1:  AI is losing by 7
    {0.4,  60}, // 2:  AI is losing by 6
    {0.5,  70}, // 3:  AI is losing by 5
    {0.6,  80}, // 4:  AI is losing by 4
    {0.7,  90}, // 5:  AI is losing by 3
    {0.8, 100}, // 6:  AI is losing by 2
    {0.9, 110}, // 7:  AI is losing by 1
    {1.0, 120}, // 8:  Tie
    {1.1, 130}, // 9:  AI is winning by 1
    {1.2, 140}, // 10: AI is winning by 2
    {1.3, 150}, // 11: AI is winning by 3
    {1.4, 160}, // 12: AI is winning by 4
    {1.5, 170}, // 13: AI is winning by 5
    {1.6, 180}, // 14: AI is winning by 6
    {1.7, 190}, // 15: AI is winning by 7
    {1.8, 200}  // 16: AI is winning by 8
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
