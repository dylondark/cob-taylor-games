/*
    pongdata.h

    File that contains data structures used in the Pong game.
*/

#ifndef PONGDATA_H
#define PONGDATA_H

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

struct AILevel {
    float aiReaction; // Reaction time for the AI
    float aiError; // Error margin for the AI's prediction
};

struct AI {
    AILevel levels[13]; // 13 levels for different score differences
    int currentLevel; // Current level based on score difference
};

#endif // PONGDATA_H
