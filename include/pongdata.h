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

struct AI {

};

#endif // PONGDATA_H
