/* Chess board representation and functions. Includes everything about board
 * state. */

#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>

#include "move.h"
#include "types.h"

#define CASTLE_WHITE_KING (1 << 0)
#define CASTLE_WHITE_QUEEN (1 << 1)
#define CASTLE_BLACK_KING (1 << 2)
#define CASTLE_BLACK_QUEEN (1 << 3)

#define MAX_GAME_LENGTH 256

typedef struct {
    uint64_t hash;
    uint8_t castlingRights;
    Square enPassantSquare;
    int halfMoves;
    int lastTriggerPly;
    int repetitions;
    move_t *lastMove;
    int wasInCheck;  // check status before the move
} game_state_t;

typedef struct {
    uint64_t hash;           // board hash
    uint8_t castlingRights;  // 4 bits
    Side sideToMove;         // side to move

    int inCheck;         // is a player in check?
    int lastTriggerPly;  // ply with pawn move or capture
    int repetitions;     // number of times the same position was visited
    int halfMoves;       // number of half moves since the last capture or pawn
                         // advance
    int fullMoves;       // starts at 1 and is incremented after Black's move

    move_t *lastMove;
    Square enPassantSquare;  // en passant target square

    // 64-bit bitboards
    // see PieceType for indexing
    // size 13 because of 12 pieces + empty square
    bb64 pcbb[13];
    bb64 occupied[2];       // occupied squares by each color
    PieceType squares[64];  // which piece is on which square

    // history
    game_state_t history[MAX_GAME_LENGTH];  // does NOT store current
    int historyIndex;
} board_t;

/// @brief Initializes a new board to the starting position
/// @param board
void init_board(board_t *board);

/// @brief Clears the board state
/// @param board
/// @return 0 on success
int clear_board(board_t *board);

/// @brief Sets the board state from a FEN string
/// @param board
/// @param fen
/// @return 0 on success
int set_fen(board_t *board, char *fen);

/// @brief Prints the board to stdout
/// @param board
void print_board(board_t *board);

/// @brief Checks if two boards are equal by comparing their bitboards. Only
/// checks piece placement, nothing else.
/// @param b1
/// @param b2
/// @return 1 if equal, 0 otherwise
int board_equal_bb(board_t *b1, board_t *b2);

/// @brief Checks if two boards are equal by comparing their hashes. Does not
/// check for collisions.
/// @param b1
/// @param b2
/// @return 1 if equal, 0 otherwise
int board_equal_hash(board_t *b1, board_t *b2);

/// @brief Checks if two boards are exactly equal - bitboards, castling rights,
/// side to move, etc
/// @param b1
/// @param b2
/// @return 1 if equal, 0 otherwise
int board_equal_exact(board_t *b1, board_t *b2);

/// @brief Clones one board to another
/// @param dest
/// @param src
/// @return 0 on success, -ERR otherwise
int board_clone(board_t *dest, board_t *src);

/// @brief Makes a move on the board. Does NOT check for legality of the move!
/// @param board
/// @param move
/// @return 0 on success
int make_move(board_t *board, move_t move);

/// @brief Un-makes a move on the board
/// @param board
/// @param move
/// @return 0 on success
int unmake_move(board_t *board);
#endif