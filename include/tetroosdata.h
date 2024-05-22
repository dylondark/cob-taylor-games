/*
    tetroosdata.h

    File that contains data structures used in the Tetroos game.
*/

#ifndef TETROOSDATA_H
#define TETROOSDATA_H

#include <QObject>
#include <QQmlEngine>
#include <array>

typedef std::array<std::array<bool, 4>, 4> PieceGrid;

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

        Mod this number by 4 to get rotation. 0 is right side up, 1 is right, 2 is upside down, 3 is left.
    */
    unsigned rotation;

    /*
        Unique identifier of the piece that this block belongs to.

        -1 if the block doesn't belong to a piece (empty).
    */
    unsigned pieceID;

    /*
    `   Whether this block is part of the piece silhouette that shows where the piece will end up.
    */
    bool silhouette;

    /*
        The location of this block in relation to the entire piece (if applicable).

        Pieces are represented as a 4x4 grid of blocks with the bottom left corner being the origin.
        @TODO: document the piece grids.
    */
    unsigned posX, posY;
};

// Grid representation of the I piece
const PieceGrid I_PIECE = {{{1,0,0,0},
                            {1,0,0,0},
                            {1,0,0,0},
                            {1,0,0,0}}};

// Grid representation of the J piece
const PieceGrid J_PIECE = {{{0,0,0,0},
                            {0,1,0,0},
                            {0,1,0,0},
                            {1,1,0,0}}};

// Grid representation of the L piece
const PieceGrid L_PIECE = {{{0,0,0,0},
                            {1,0,0,0},
                            {1,0,0,0},
                            {1,1,0,0}}};

// Grid representation of the O piece
const PieceGrid O_PIECE = {{{0,0,0,0},
                            {0,0,0,0},
                            {1,1,0,0},
                            {1,1,0,0}}};

// Grid representation of the S piece
const PieceGrid S_PIECE = {{{0,0,0,0},
                            {0,0,0,0},
                            {0,1,1,0},
                            {1,1,0,0}}};

// Grid representation of the T piece
const PieceGrid T_PIECE = {{{0,0,0,0},
                            {0,0,0,0},
                            {0,1,0,0},
                            {1,1,1,0}}};

// Grid representation of the Z piece
const PieceGrid Z_PIECE = {{{0,0,0,0},
                            {0,0,0,0},
                            {1,1,0,0},
                            {0,1,1,0}}};

#endif // TETROOSDATA_H
