#include "util.h"

void printbb(bb64 bb) {
    printf("\n");
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (int rank = 7; rank >= 0; rank--) {
        printf("%d |", rank + 1);

        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;

            if (bb & (1ULL << square)) {
                printf(" X |");
            } else {
                printf("   |");
            }
        }

        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }

    printf("    A   B   C   D   E   F   G   H\n");
    printf("\n");
}

int pop_lsb(uint64_t *bb) {
    int lsb = __builtin_ctzll(*bb);
    *bb &= *bb - 1;
    return lsb;
}

int popcount(uint64_t bb) { return __builtin_popcountll(bb); }