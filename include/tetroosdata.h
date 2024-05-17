/*
    tetroosdata.h

    File that contains data structures used in the Tetroos game.
*/

#ifndef TETROOSDATA_H
#define TETROOSDATA_H

#include <QObject>
#include <QQmlEngine>

/*
    Enum that neatly defines all of the piece types (or empty).
    Mapping to chars may or may not be necessary.
*/
enum PieceType : char {I = 'I' , J = 'J', L = 'L', O = 'O', S = 'S', T = 'T', Z = 'Z', empty = 'E'};

/*
    This enum defines all of the actions that can cause a game update. It includes all of the actions a player can make as well as the normal timer tick.
*/
enum GameAction {TimerTick, Left, Right, Down, RotateClockwise, RotateCounterclockwise, Slam, Hold};

/*
    This is the data structure that represents every individual block on the play grid.
    It contains the block type as well as a bunch of metadata used to determine how to apply images to the block.
*/
struct Block
{
    /*
        Contains the type of piece this block belongs to.
    */
    PieceType pieceType;

    /*
        Contains the rotation of the piece (if part of one).

        0 for right side up, -1 for rotated left, 1 for rotated right, 2 for upside down.
    */
    int rotation;

    /*
        Unique identifier of the piece that this block belongs to.

        -1 if the block doesn't belong to a piece (empty).
    */
    int pieceID;

    /*
    `   Whether this block is part of the piece silhouette that shows where the piece will end up.
    */
    bool silhouette;

    /*
        The location of this block in relation to the entire piece (if applicable).

        Pieces are represented as a 4x4 grid of blocks with the bottom left corner being the origin.
        @TODO: document the piece grids.
    */
    int posX, posY;
};

#endif // TETROOSDATA_H
