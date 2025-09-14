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

    // // move_t move = create_move(E2, E4, W_PAWN, EMPTY, 0,
    // // MOVE_FLAG_DOUBLE_PAWN_PUSH);
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

    // set_fen(&board, "r3k2r/p1ppqpb1/bn2pnp1/3PN3/Pp2P3/2N2Q1p/1PPBBPPP/R3K2R b KQkq a3 0 1");

    set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
    movelist_clear(&movelist);
    generate_castling_moves(&board, &movelist);
    movelist_print(&movelist);

    move_t move = create_move(E1, G1, W_KING, EMPTY, 0xf, 0x2);
    print_board(&board);
    make_move(&board, move);
    print_board(&board);
    unmake_move(&board);
    print_board(&board);

    move = create_move(E1, C1, W_KING, EMPTY, 0xf, 0x3);
    make_move(&board, move);
    print_board(&board);
    unmake_move(&board);
    print_board(&board);


    // // int check = is_in_check(&board, BLACK);
    // // printf("%d\n", check);

    // uint64_t start, stop;
    // start = get_time_microseconds();
    // uint64_t count = perft(&board, 1);
    // stop = get_time_microseconds();
    // printf("Perft: %lu\n", count);
    // printf("Completed in %lu ms\n", (stop - start) / 1000);
    // printf("%lld nps\n", count * 1000000ULL / (stop - start));

    // board_t board;
    // movelist_t moves;
    // uint64_t hash;
    // init_board(&board);
    // movelist_clear(&moves);
    // initialize_movegen();

    // // white can attack en passant
    // set_fen(&board, "rnbqkb1r/ppppp1pp/7n/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
    // hash = board.hash;

    // generate_pawn_moves(&board, &moves);
    // movelist_print(&moves);

    // move_t move = create_move(E5, F6, W_PAWN, B_PAWN, 0xf, 0x5);
    // make_move(&board, move);
    // print_board(&board);
    // unmake_move(&board);
    // print_board(&board);

    // printf("old hash: %lx\n", hash);
    // printf("new hash: %lx\n", board.hash);

    return 0;
}