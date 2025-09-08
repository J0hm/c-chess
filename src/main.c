#include <stdio.h>
#include "util.h"
#include "constants.h"
#include "board.h"

int main(int argc, char *argv[]) {
    board_t board;
    init_board(&board);
    print_board(&board);
    printf("board_t size: %lu\n", sizeof(board_t));
    return 0;
}