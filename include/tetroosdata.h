/*
    tetroosdata.h

    File that contains data structures used in the Tetroos game.
*/

#ifndef TETROOSDATA_H
#define TETROOSDATA_H

#include <QObject>
#include <QQmlEngine>
#include <array>
#include "flippedarray.h"

/*
    Enum that neatly defines all of the piece types (or empty).
    Mapping to chars may or may not be necessary.
*/
enum PieceType : char {I = 'I' , J = 'J', L = 'L', O = 'O', S = 'S', T = 'T', Z = 'Z', empty = 'E'};

/*
    This enum defines all of the actions that can cause a game update. It includes all of the actions a player can make as well as the normal timer tick.
*/
enum GameAction {NewPiece = 0, Left = 1, Right = 2, Down = 3, Rotate = 4, Slam = 5, Hold = 6};

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

        0 if the block doesn't belong to a piece (empty).
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

// Empty block constant.
const Block EMPTY_BLOCK = {empty, 0, 0, false, 0, 0};

/*
    Struct that holds all relevant data about the currently active piece.
*/
struct ActivePiece
{
    /*
        Contains the type of piece the active piece is.
    */
    PieceType pieceType;

    /*
        The rotation of the piece.
        Mod this number by 4 to get rotation. 0 is right side up, 1 is right, 2 is upside down, 3 is left.
    */
    unsigned rotation;

    /*
        The unique identifier of the piece.
    */
    unsigned pieceID;

    /*
        The location of the bottom left corner of the piece on the board.
    */
    unsigned posX, posY;
};

/*
    Struct that makes up the unit for PieceGrids.
*/
struct PieceGridBlock
{
    bool filled;
    unsigned posX, posY;
};

typedef FlippedArray<std::array<PieceGridBlock, 4>, 4> PieceGrid;

// Grid representation of the I piece
const PieceGrid I_PIECE = {{{{{true , 0, 3}, {false, 1, 3}, {false, 2, 3}, {false, 3, 3}}},
                            {{{true , 0, 2}, {false, 1, 2}, {false, 2, 2}, {false, 3, 2}}},
                            {{{true , 0, 1}, {false, 1, 1}, {false, 2, 1}, {false, 3, 1}}},
                            {{{true , 0, 0}, {false, 1, 0}, {false, 2, 0}, {false, 3, 0}}}}};

// Grid representation of the J piece
const PieceGrid J_PIECE = {{{{{false, 0, 3}, {false, 1, 3}, {false, 2, 3}, {false, 3, 3}}},
                            {{{false, 0, 2}, {true , 1, 2}, {false, 2, 2}, {false, 3, 2}}},
                            {{{false, 0, 1}, {true , 1, 1}, {false, 2, 1}, {false, 3, 1}}},
                            {{{true , 0, 0}, {true , 1, 0}, {false, 2, 0}, {false, 3, 0}}}}};

// Grid representation of the L piece
const PieceGrid L_PIECE = {{{{{false, 0, 3}, {false, 1, 3}, {false, 2, 3}, {false, 3, 3}}},
                            {{{true , 0, 2}, {false, 1, 2}, {false, 2, 2}, {false, 3, 2}}},
                            {{{true , 0, 1}, {false, 1, 1}, {false, 2, 1}, {false, 3, 1}}},
                            {{{true , 0, 0}, {true , 1, 0}, {false, 2, 0}, {false, 3, 0}}}}};

// Grid representation of the O piece
const PieceGrid O_PIECE = {{{{{false, 0, 3}, {false, 1, 3}, {false, 2, 3}, {false, 3, 3}}},
                            {{{false, 0, 2}, {false, 1, 2}, {false, 2, 2}, {false, 3, 2}}},
                            {{{true , 0, 1}, {true , 1, 1}, {false, 2, 1}, {false, 3, 1}}},
                            {{{true , 0, 0}, {true , 1, 0}, {false, 2, 0}, {false, 3, 0}}}}};

// Grid representation of the S piece
const PieceGrid S_PIECE = {{{{{false, 0, 3}, {false, 1, 3}, {false, 2, 3}, {false, 3, 3}}},
                            {{{false, 0, 2}, {false, 1, 2}, {false, 2, 2}, {false, 3, 2}}},
                            {{{false, 0, 1}, {true , 1, 1}, {true , 2, 1}, {false, 3, 1}}},
                            {{{true , 0, 0}, {true , 1, 0}, {false, 2, 0}, {false, 3, 0}}}}};

// Grid representation of the T piece
const PieceGrid T_PIECE = {{{{{false, 0, 3}, {false, 1, 3}, {false, 2, 3}, {false, 3, 3}}},
                            {{{false, 0, 2}, {false, 1, 2}, {false, 2, 2}, {false, 3, 2}}},
                            {{{true , 0, 1}, {true , 1, 1}, {true , 2, 1}, {false, 3, 1}}},
                            {{{false, 0, 0}, {true , 1, 0}, {false, 2, 0}, {false, 3, 0}}}}};

// Grid representation of the Z piece
const PieceGrid Z_PIECE = {{{{{false, 0, 3}, {false, 1, 3}, {false, 2, 3}, {false, 3, 3}}},
                            {{{false, 0, 2}, {false, 1, 2}, {false, 2, 2}, {false, 3, 2}}},
                            {{{true , 0, 1}, {true , 1, 1}, {false, 2, 1}, {false, 3, 1}}},
                            {{{false, 0, 0}, {true , 1, 0}, {true , 2, 0}, {false, 3, 0}}}}};

#endif // TETROOSDATA_H
