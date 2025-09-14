#include <stdio.h>
#include <time.h>

#include "board.h"
#include "constants.h"
#include "movegen.h"
#include "types.h"
#include "util.h"

uint64_t get_time_microseconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000ULL + (uint64_t)ts.tv_nsec / 1000ULL;
}

int main(int argc, char *argv[]) {
    board_t board;
    init_board(&board);
    initialize_movegen();

    // move_t move = create_move(E2, E4, W_PAWN, EMPTY, 0,
    // MOVE_FLAG_DOUBLE_PAWN_PUSH);
    movelist_t movelist = {0};

    // make_move(&board, move);
    // // unmake_move(&board);

    // print_board(&board);
    // unmake_move(&board);
    // print_board(&board);

    // // generate_moves(&board, &movelist);
    // // printf("generated moves: %d\n", movelist.moveCount);
    // // unmake_move(&board);
    // // movelist_clear(&movelist);
    // generate_moves(&board, &movelist);
    // printf("generated moves: %d\n", movelist.moveCount);
    // // make_move(&board, move);

    set_fen(&board, "r4rk1/1pp1qBpp/p1np1n2/2b1p1B1/4P1b1/P1NP1N2/1PP1QPPP/R4RK1 b - - 0 10");

    // int check = is_in_check(&board, BLACK);
    // printf("%d\n", check);

    uint64_t start, stop;
    start = get_time_microseconds();
    uint64_t count = perft(&board, 5);
    stop = get_time_microseconds();
    printf("Perft: %lu\n", count);
    printf("Completed in %lu ms\n", (stop - start) / 1000);
    printf("%lld nps\n", count * 1000000ULL / (stop - start));

    return 0;
}