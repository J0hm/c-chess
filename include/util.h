#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>

#include "types.h"

int pop_lsb(uint64_t *bb);

int popcount(uint64_t bb);

/// @brief Prints a 64-bit bitboard. Always prints from White's perspective
/// @param bb
void printbb(bb64 bb);

char* square_to_string(Square sq);

char* piece_type_to_string(PieceType pt);

#endif