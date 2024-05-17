/*
    tetroosdata.h

    File that contains data structures used in the Tetroos game.
*/

#ifndef TETROOSDATA_H
#define TETROOSDATA_H

#include <QObject>
#include <QQmlEngine>

enum PieceType {I = 'I' , J = 'J', L = 'L', O = 'O', S = 'S', T = 'T', Z = 'Z', empty = 'E'};

/*
    This is the data structure that represents every individual block on the play grid.
    It contains the block type as well as a bunch of metadata used to determine how to apply images to the block.
*/
struct block
{
    Q_GADGET
public:
    /*
        Contains the type of piece this block belongs to.

        Can be 'I', 'J', 'L', 'O', 'S', 'T', 'Z' for their respective pieces.
        'E' for empty (not part of a piece).
    */
    PieceType m_pieceType;

    /*
        Contains the rotation of the piece (if part of one).

        0 for right side up, -1 for rotated left, 1 for rotated right, 2 for upside down.
    */
    int m_rotation;

    /*
        Unique identifier of the piece that this block belongs to.

        -1 if the block doesn't belong to a piece (empty).
    */
    int m_pieceID;

    /*
    `   Whether this block is part of the piece silhouette that shows where the piece will end up.
    */
    bool m_silhouette;

    /*
        The location of this block in relation to the entire piece (if applicable).

        Pieces are represented as a 4x4 grid of blocks with the bottom left corner being the origin.
        @TODO: document the piece grids.
    */
    int m_posX, m_posY;

    // Properties to make these data members accessible in QML.
    Q_PROPERTY(char pieceType MEMBER m_pieceType)
    Q_PROPERTY(int rotation MEMBER m_rotation)
    Q_PROPERTY(int pieceID MEMBER m_pieceID)
    Q_PROPERTY(bool silhouette MEMBER m_silhouette)
    Q_PROPERTY(int posX MEMBER m_posX)
    Q_PROPERTY(int posY MEMBER m_posY)
};

#endif // TETROOSDATA_H
