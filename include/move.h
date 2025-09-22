#ifndef MOVE_H
#define MOVE_H
#include <stdint.h>

#include "types.h"

/* 28 bits to represent a move :
 * Castling rights BEFORE move : 4 bits
 * Captured piece type         : 4 bits
 * Moved piece type            : 4 bits
 * Flags                       : 4 bits
 * Origin                      : 6 bits
 * Destination                 : 6 bits
 *
 * Piece types: see types.h
 *
 * Flags: Leftmost bit is promotion bit, the bit after is capture bit.
 * 0    0    0    0	  quiet moves
 * 0    0    0    1	  double pawn push
 * 0    0	 1	  0	  king castle
 * 0	0	 1	  1	  queen castle
 * 0	1	 0	  0	  captures
 * 0	1	 0	  1	  en-passant-capture
 * 1	0	 0	  0	  knight-promotion
 * 1	0	 0	  1	  bishop-promotion
 * 1	0	 1	  0   rook-promotion
 * 1	0	 1	  1	  queen-promotion
 * 1	1	 0	  0	  knight-promo capture
 * 1	1	 0	  1	  bishop-promo capture
 * 1	1	 1	  0	  rook-promo capture
 * 1	1	 1	  1	  queen-promo capture
 */

typedef struct {
    int rating;  // score of this move for move ordering
    uint32_t move32;
} move_t;

#define CASTLE_WHITE_KING (1 << 0)
#define CASTLE_WHITE_QUEEN (1 << 1)
#define CASTLE_BLACK_KING (1 << 2)
#define CASTLE_BLACK_QUEEN (1 << 3)

#define MOVE_FLAG_QUITE 0b0000
#define MOVE_FLAG_DOUBLE_PAWN_PUSH 0b0001
#define MOVE_FLAG_KING_CASTLE 0b0010
#define MOVE_FLAG_QUEEN_CASTLE 0b0011
#define MOVE_FLAG_CAPTURE 0b0100
#define MOVE_FLAG_EN_PASSANT 0b0101
#define MOVE_FLAG_KNIGHT_PROMO 0b1000
#define MOVE_FLAG_BISHOP_PROMO 0b1001
#define MOVE_FLAG_ROOK_PROMO 0b1010
#define MOVE_FLAG_QUEEN_PROMO 0b1011
#define MOVE_FLAG_KNIGHT_PROMO_CAPTURE 0b1100
#define MOVE_FLAG_BISHOP_PROMO_CAPTURE 0b1101
#define MOVE_FLAG_ROOK_PROMO_CAPTURE 0b1110
#define MOVE_FLAG_QUEEN_PROMO_CAPTURE 0b1111

// getters
#define MOVE32_DST(m) (m & 0x3f)
#define MOVE32_SRC(m) ((m >> 6) & 0x3f)
#define MOVE32_FLAGS(m) ((m >> 12) & 0xf)
#define MOVE32_PIECE_TYPE(m) ((m >> 16) & 0xf)
#define MOVE32_CAPTURED_PIECE(m) ((m >> 20) & 0xf)
#define MOVE32_CASTLING_RIGHTS(m) ((m >> 24) & 0xf)

// setters
#define MOVE32_SET_DST(m, dst) ((m) = ((m) & ~0x3f) | ((dst) & 0x3f))
#define MOVE32_SET_SRC(m, src) \
    ((m) = ((m) & ~(0x3f << 6)) | (((src) & 0x3f) << 6))
#define MOVE32_SET_FLAGS(m, flags) \
    ((m) = ((m) & ~(0xf << 12)) | (((flags) & 0xf) << 12))
#define MOVE32_SET_MOVED_PIECE_TYPE(m, piece_type) \
    ((m) = ((m) & ~(0xf << 16)) | (((piece_type) & 0xf) << 16))
#define MOVE32_SET_CAPTURED_PIECE_TYPE(m, piece_type) \
    ((m) = ((m) & ~(0xf << 20)) | (((piece_type) & 0xf) << 20))
#define MOVE32_SET_CASTLING_RIGHTS(m, rights) \
    ((m) = ((m) & ~(0xf << 24)) | (((rights) & 0xf) << 24))

move_t create_move(Square from, Square to, PieceType moved, PieceType captured,
                   uint8_t castling, uint8_t flags);

void print_move(move_t move);

void to_lan(move_t move, char *buf);

#endif