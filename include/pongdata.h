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
    AILevel levels[17]; // 17 levels for different score differences
    int currentLevel; // Current level based on score difference

    /*
      Constructor to initialize AI levels
    */
    AI () {
        // Initialize AI levels based on the score difference
        levels[0] = {0.2f, 40}; // AI is losing by 8
        levels[1] = {0.3f, 50};
        levels[2] = {0.4f, 60};
        levels[3] = {0.5f, 70};
        levels[4] = {0.6f, 80};
        levels[5] = {0.7f, 90};
        levels[6] = {0.8f, 100};
        levels[7] = {0.9f, 110};
        levels[8] = {1.0f, 120}; // Tie
        levels[9] = {1.1f, 130};
        levels[10] = {1.2f, 140};
        levels[11] = {1.3f, 150};
        levels[12] = {1.4f, 160};
        levels[13] = {1.5f, 170};
        levels[14] = {1.6f, 180};
        levels[15] = {1.7f, 190};
        levels[16] = {1.8f, 200}; // AI is winning by 8

        currentLevel = 8; // Start at level 8 (tie)
    }

    /*
        Function to update the AI level based on the score difference
    */
    void updateLevel(int playerScore, int aiScore) {
        int scoreDifference = aiScore - playerScore;
        if (scoreDifference < -8) scoreDifference = -8;
        if (scoreDifference > 8) scoreDifference = 8;
        currentLevel = scoreDifference + 8; // Map score difference to level index
    }
};

#endif // PONGDATA_H
