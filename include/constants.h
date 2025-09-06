#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "types.h"

#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

// 0-63 -> a1-h8, in 64-bit bitboard mask
extern const bb64 bitboard_masks[64];

#endif