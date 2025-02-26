/*
    pongdata.h

    File that contains data structures used in the Pong game.
*/

#ifndef PONGDATA_H
#define PONGDATA_H

#include <QDebug>

struct Paddle
{
    int x;
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

struct AI {
    int currentLevel;   // Current level based on score difference

    float baseReaction = 1.0f; // Default reaction time
    float baseError = 120.0f;  // Default error margin

    float aiReaction; // Current reaction time
    float aiError;    // Current error margin

    AI() {
        currentLevel = 8; // Start at level 8 (tie)
        aiReaction = baseReaction; // Initialize with base values
        aiError = baseError;       // Initialize with base values
    }

    void updateLevel(int playerScore, int aiScore) {
        int scoreDifference = aiScore - playerScore;

        // Adjust the AI's difficulty based on the score difference
        float difficultyFactor = 1.0f + (scoreDifference * 0.1f); // Adjust the multiplier as needed

        // Clamp the difficulty factor to a reasonable range
        if (difficultyFactor < 0.5f) difficultyFactor = 0.5f; // Minimum difficulty
        if (difficultyFactor > 2.0f) difficultyFactor = 2.0f; // Maximum difficulty

        // Update the AI's reaction time and error margin based on the difficulty factor
        aiReaction = baseReaction * difficultyFactor;
        aiError = baseError / difficultyFactor;

        // Debug logs
        qDebug() << "Score Difference: " << scoreDifference;
        qDebug() << "Difficulty Factor: " << difficultyFactor;
        qDebug() << "AI Reaction: " << aiReaction;
        qDebug() << "AI Error: " << aiError;
    }
};

#endif // PONGDATA_H
