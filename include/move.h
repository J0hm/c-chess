#ifndef MOVE_H
#define MOVE_H
#include <stdint.h>

/* 26 bits to represent a move :
 * Castling rights BEFORE move : 4 bits
 * Captured piece              : 3 bits
 * Moved piece type            : 3 bits
 * Flags                       : 4 bits
 * Origin                      : 6 bits
 * Destination                 : 6 bits
 *
 * Castling:
 * Same as FEN, QKqk = 1111, Qk = 1001, etc.
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
    int rating; // score of this move for move ordering
    uint32_t move;
} move_t;

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

#define MOVE_DST(m) (m & 0x3f)
#define MOVE_SRC(m) ((m >> 6) & 0x3f)
#define MOVE_FLAGS(m) ((m >> 12) & 0xf)
#define MOVE_PIECE_TYPE(m) ((m >> 16) & 0x7)
#define MOVE_CAPTURED_PIECE(m) ((m >> 19) & 0x7)
#define MOVE_PROMOTION_PIECE_TYPE(m) ((MOVE_FLAGS() & 0b11) + 2)
#define MOVE_CASTLING_RIGHTS(m) ((m >> 22) & 0xf)
#define MOVE_EQ(m1, m2) (m1.move == m2.move)

#endif