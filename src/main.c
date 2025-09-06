#include <stdio.h>
#include "util.h"
#include "constants.h"
#include "board.h"

int main(int argc, char *argv[]) {
    board_t board;
    init_board(&board);
    print_board(&board);
    return 0;
}