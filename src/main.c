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

    set_fen(&board, "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
    print_board(&board);
    
    generate_moves(&board, &moves);
    
    movelist_print(&moves);

    printf("generated %d moves\n", moves.moveCount);
    return 0;
}