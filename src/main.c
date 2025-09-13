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

    // set_fen(&board, "8/8/8/8/8/8/4P3/8 w - - 0 1");
    print_board(&board);
    
    generate_moves(&board, &moves);
    
    movelist_print(&moves);
    return 0;
}