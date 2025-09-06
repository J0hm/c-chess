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