#include "board.h"
#include "hash.h"
#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_hash(void) {
    board_t board;
    uint64_t hash = 0;

    // starting position
    init_board(&board);
    hash = hash_board(&board);
    TEST_ASSERT_EQUAL_UINT64(0x463b96181691fc9cULL, hash);

    // position after e2e4
    set_fen(&board,
            "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    hash = hash_board(&board);
    TEST_ASSERT_EQUAL_UINT64(0x823c9b50fd114196ULL, hash);

    // position after e2e4 d75
    set_fen(&board,
            "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2");
    hash = hash_board(&board);
    TEST_ASSERT_EQUAL_UINT64(0x0756b94461c50fb0ULL, hash);

    // position after e2e4 d7d5 e4e5
    set_fen(&board,
            "rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2");
    hash = hash_board(&board);
    TEST_ASSERT_EQUAL_UINT64(0x662fafb965db29d4ULL, hash);

    // position after e2e4 d7d5 e4e5 f7f5
    set_fen(&board,
            "rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
    hash = hash_board(&board);
    TEST_ASSERT_EQUAL_UINT64(0x22a48b5a8e47ff78ULL, hash);

    // position after e2e4 d7d5 e4e5 f7f5 e1e2
    set_fen(&board,
            "rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPPKPPP/RNBQ1BNR b kq - 0 3");
    hash = hash_board(&board);
    TEST_ASSERT_EQUAL_UINT64(0x652a607ca3f242c1ULL, hash);

    // position after e2e4 d7d5 e4e5 f7f5 e1e2 e8f7
    set_fen(&board,
            "rnbq1bnr/ppp1pkpp/8/3pPp2/8/8/PPPPKPPP/RNBQ1BNR w - - 0 4");
    hash = hash_board(&board);
    TEST_ASSERT_EQUAL_UINT64(0x00fdd303c946bdd9ULL, hash);

    // position after a2a4 b7b5 h2h4 b5b4 c2c4
    set_fen(&board,
            "rnbqkbnr/p1pppppp/8/8/PpP4P/8/1P1PPPP1/RNBQKBNR b KQkq c3 0 3");
    hash = hash_board(&board);
    TEST_ASSERT_EQUAL_UINT64(0x3c8123ea7b067637ULL, hash);

    // position after a2a4 b7b5 h2h4 b5b4 c2c4 b4c3 a1a3
    set_fen(&board,
            "rnbqkbnr/p1pppppp/8/8/P6P/R1p5/1P1PPPP1/1NBQKBNR b Kkq - 0 4");
    hash = hash_board(&board);
    TEST_ASSERT_EQUAL_UINT64(0x5c3f9b829b279560ULL, hash);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_hash);
    return UNITY_END();
}