#include <stdio.h>
#include "constants.h"
#include "board.h"
#include "movegen.h"
#include "types.h"
#include "util.h"

int main(int argc, char *argv[]) {
    board_t board;
    movelist_t moves;
    init_board(&board);
    initialize_movegen();

    set_fen(&board, "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ");
    print_board(&board);
    
    generate_moves(&board, &moves);
    
    movelist_print(&moves);

    printf("generated %d moves\n", moves.moveCount);
    return 0;
}