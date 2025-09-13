#ifndef MOVEGEN_H
#define MOVEGEN_H
#include "board.h"

#define MOVELIST_SIZE 256

/* Some general information:
 * - generate_*_moves generate all pseudolegal moves
 * - get_*_attacks generate the bitboard of attacks
 * - for pawns, this does not include pushes or en passant
 * - sliding pieces take into account occupied squares for magic bitboard use
 */

typedef struct {
    move_t move[MOVELIST_SIZE];  // move list
    int moveCount;                // number of moves stored
    int index;                    // index in the list
} movelist_t;

/// @brief Initializes movegen. Must be run once before using movegen
void initialize_movegen();

/// @brief Generates all possible pseudolegal moves
/// @param board pointer to board to generate moves for
/// @param moves move list to be populated
void generate_moves(board_t *board, movelist_t *moves);

void generate_pawn_moves(board_t *board, movelist_t *moves);

void generate_knight_moves(board_t *board, movelist_t *moves);

void generate_bishop_moves(board_t *board, movelist_t *moves);

void generate_rook_moves(board_t *board, movelist_t *moves);

void generate_queen_moves(board_t *board, movelist_t *moves);

void generate_king_moves(board_t *board, movelist_t *moves);

void generate_castling_moves(board_t *board, movelist_t *moves);

/// @brief Return pawn attack bitboard, EXCULDES EN PASSANT AND PUSHES
/// @param square the pawn is on
/// @param side to move
/// @return bitboard of attacks
uint64_t get_pawn_attacks(Square square, Side side);

/// @brief Returns knight attack bitboard
/// @param square square the knight is on
/// @return bitboard of attacks
uint64_t get_knight_attacks(Square square);

/// @brief Returns king attack bitboard
/// @param square square the king is on
/// @return bitboard of attacks
uint64_t get_king_attacks(Square square);

/// @brief Returns bishop attack bitboard
/// @param square square the bishop is on
/// @param occupied bitboard of occupied squares
uint64_t get_bishop_attacks(Square square, uint64_t occupied);

/// @brief Returns rook attack bitboard
/// @param square square the rook is on
/// @param occupied bitboard of occupied squares
uint64_t get_rook_attacks(Square square, uint64_t occupied);

/// @brief Returns queen attack bitboard
/// @param square square the queen is on
/// @param occupied bitboard of occupied squares
uint64_t get_queen_attacks(Square square, uint64_t occupied);

/// @brief Rates a move for move ordering
/// @param move to rate
void rate_move(board_t *board, move_t *move);

/// @brief Returns the best next move in the move list
/// @param moves list to search
/// @return next best move on success, NULL on error
move_t *movelist_get_next(movelist_t *moves);

/// @brief Adds a move to the move list
/// @param moves movelist to add to
/// @param move move to add
void movelist_add(movelist_t *moves, move_t move);

/// @brief Clears the move list
void movelist_clear(movelist_t *moves);

/// @brief Prints the move list
void movelist_print(movelist_t *moves);

#endif