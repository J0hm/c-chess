/* Chess board representation and functions. Includes everything about board
 * state. */

#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>

#include "move.h"
#include "types.h"

typedef struct {
    uint64_t hash;           // board hash
    uint8_t castlingRights;  // 4 bits: KQkq = 1111, Kk = 1010, Kq = 1001, etc
    enum Side side_to_move;  // side to move

    int lastTriggerPly;  // ply with pawn move or capture
    int inCheck;         // is a player in check?
    int repetitions;     // number of times the same position was visited

    Move lastMove;
    enum Square enPassantSquare;  // square which can be moved to in order to
                                  // capture via en passant

    // 64-bit bitboards
    // see PieceType for indexing
    // 13 for "empty" pieces
    uint64_t pcbb[13];
    uint64_t occupied[2];        // occupied squares by each color
    enum PieceType squares[64];  // which piece is on which square
} board_t;

#endif