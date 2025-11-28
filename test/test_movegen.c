#include "constants.h"
#include "movegen.h"
#include "unity.h"

void setUp(void) {
    initialize_movegen();  // initialize pregenerated tables
}

void tearDown(void) {
    // clean stuff up here
}

void test_get_king_attacks(void) {
    uint64_t attacks;

    attacks = get_king_attacks(A1);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000000302, attacks);

    attacks = get_king_attacks(H1);
    TEST_ASSERT_EQUAL_HEX64(0x000000000000C040, attacks);

    attacks = get_king_attacks(A8);
    TEST_ASSERT_EQUAL_HEX64(0x0203000000000000, attacks);

    attacks = get_king_attacks(H8);
    TEST_ASSERT_EQUAL_HEX64(0x40C0000000000000, attacks);

    attacks = get_king_attacks(B2);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000070507, attacks);

    attacks = get_king_attacks(D1);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000001C14, attacks);

    attacks = get_king_attacks(E1);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000003828, attacks);

    attacks = get_king_attacks(D8);
    TEST_ASSERT_EQUAL_HEX64(0x141C000000000000, attacks);

    attacks = get_king_attacks(E8);
    TEST_ASSERT_EQUAL_HEX64(0x2838000000000000, attacks);

    attacks = get_king_attacks(A4);
    TEST_ASSERT_EQUAL_HEX64(0x0000000302030000, attacks);

    attacks = get_king_attacks(A5);
    TEST_ASSERT_EQUAL_HEX64(0x0000030203000000, attacks);

    attacks = get_king_attacks(H4);
    TEST_ASSERT_EQUAL_HEX64(0x000000C040C00000, attacks);

    attacks = get_king_attacks(H5);
    TEST_ASSERT_EQUAL_HEX64(0x0000C040C0000000, attacks);
}

void test_get_pawn_attacks(void) {
    uint64_t attacks;

    attacks = get_pawn_attacks(A1, WHITE);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000000200, attacks);  // b2

    attacks = get_pawn_attacks(H1, WHITE);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000004000, attacks);  // g2

    attacks = get_pawn_attacks(A8, WHITE);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000000000, attacks);  // 8th rank

    attacks = get_pawn_attacks(H8, WHITE);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000000000, attacks);  // 8th rank

    attacks = get_pawn_attacks(A1, BLACK);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000000000, attacks);  // 1st rank

    attacks = get_pawn_attacks(H1, BLACK);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000000000, attacks);  // 1st rank

    attacks = get_pawn_attacks(A8, BLACK);
    TEST_ASSERT_EQUAL_HEX64(0x0002000000000000, attacks);  // b7

    attacks = get_pawn_attacks(H8, BLACK);
    TEST_ASSERT_EQUAL_HEX64(0x0040000000000000, attacks);  // g7

    attacks = get_pawn_attacks(D4, WHITE);
    TEST_ASSERT_EQUAL_HEX64(0x0000001400000000, attacks);  // c5, e5

    attacks = get_pawn_attacks(D4, BLACK);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000140000, attacks);  // c3, e3

    attacks = get_pawn_attacks(A4, WHITE);
    TEST_ASSERT_EQUAL_HEX64(0x0000000200000000, attacks);  // b5

    attacks = get_pawn_attacks(H4, BLACK);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000400000, attacks);  // g3
}

void test_get_knight_attacks(void) {
    uint64_t attacks;

    attacks = get_knight_attacks(A1);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000020400, attacks);  // b3, c2

    attacks = get_knight_attacks(H1);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000402000, attacks);  // f2, g3

    attacks = get_knight_attacks(A8);
    TEST_ASSERT_EQUAL_HEX64(0x0004020000000000, attacks);  // b6, c7

    attacks = get_knight_attacks(H8);
    TEST_ASSERT_EQUAL_HEX64(0x0020400000000000, attacks);  // f7, g6

    attacks = get_knight_attacks(A4);
    TEST_ASSERT_EQUAL_HEX64(0x0000020400040200, attacks);  // b2, b6, c3, c5

    attacks = get_knight_attacks(H4);
    TEST_ASSERT_EQUAL_HEX64(0x0000402000204000, attacks);  // f3, f5, g2, g6

    attacks = get_knight_attacks(D1);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000142200, attacks);  // b2, c3, e3, f2

    attacks = get_knight_attacks(D8);
    TEST_ASSERT_EQUAL_HEX64(0x0022140000000000, attacks);  // b7, c6, e6, f7

    attacks = get_knight_attacks(D4);
    TEST_ASSERT_EQUAL_HEX64(0x0000142200221400,
                            attacks);  // b3, b5, c2, c6, e2, e6, f3, f5

    attacks = get_knight_attacks(E4);
    TEST_ASSERT_EQUAL_HEX64(0x0000284400442800,
                            attacks);  // c3, c5, d2, d6, f2, f6, g3, g5
}

void test_get_bishop_attacks(void) {
    uint64_t attacks;

    // Bishop on A1 with blocker on D4
    attacks = get_bishop_attacks(A1, bitboard_masks[D4]);
    TEST_ASSERT_EQUAL_HEX64(0x0000000008040200, attacks);

    // Bishop on A1 - no blockers (empty board)
    attacks = get_bishop_attacks(A1, 0ULL);
    TEST_ASSERT_EQUAL_HEX64(0x8040201008040200, attacks);

    // Bishop on H1 - no blockers
    attacks = get_bishop_attacks(H1, 0ULL);
    TEST_ASSERT_EQUAL_HEX64(0x0102040810204000, attacks);

    // Bishop on A8 - no blockers
    attacks = get_bishop_attacks(A8, 0ULL);
    TEST_ASSERT_EQUAL_HEX64(0x0002040810204080, attacks);

    // Bishop on H8 - no blockers
    attacks = get_bishop_attacks(H8, 0ULL);
    TEST_ASSERT_EQUAL_HEX64(0x0040201008040201, attacks);

    // Bishop on D4 with blocker on B2
    attacks = get_bishop_attacks(D4, bitboard_masks[B2]);
    TEST_ASSERT_EQUAL_HEX64(0x8041221400142240, attacks);

    // Bishop on D4 with blocker on F6
    attacks = get_bishop_attacks(D4, bitboard_masks[F6]);
    TEST_ASSERT_EQUAL_HEX64(0x0001221400142241, attacks);

    // Bishop on D4 with multiple blockers
    attacks = get_bishop_attacks(D4, bitboard_masks[B2] | bitboard_masks[F6]);
    TEST_ASSERT_EQUAL_HEX64(0x0001221400142240, attacks);

    // Bishop on E4 - center square, no blockers
    attacks = get_bishop_attacks(E4, 0ULL);
    TEST_ASSERT_EQUAL_HEX64(0x0182442800284482, attacks);

    // Bishop on E4 with blockers on C2 and G6
    attacks = get_bishop_attacks(E4, bitboard_masks[C2] | bitboard_masks[G6]);
    TEST_ASSERT_EQUAL_HEX64(0x0102442800284480, attacks);

    // Corner bishop with nearby blocker
    attacks = get_bishop_attacks(A1, bitboard_masks[B2]);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000000200, attacks);

    // Edge bishop tests
    attacks = get_bishop_attacks(A4, bitboard_masks[C6]);
    TEST_ASSERT_EQUAL_HEX64(0x0000040200020408, attacks);

    attacks = get_bishop_attacks(H5, bitboard_masks[F3]);
    TEST_ASSERT_EQUAL_HEX64(0x1020400040200000, attacks);
}

void test_get_rook_attacks(void) {
    uint64_t attacks;

    // Rook on A1 with blocker on E1
    attacks = get_rook_attacks(A1, bitboard_masks[E1]);
    TEST_ASSERT_EQUAL_HEX64(0x010101010101011E, attacks);

    // Rook on A1 - no blockers (empty board)
    attacks = get_rook_attacks(A1, 0ULL);
    TEST_ASSERT_EQUAL_HEX64(0x01010101010101FE, attacks);

    // Rook on H1 - no blockers
    attacks = get_rook_attacks(H1, 0ULL);
    TEST_ASSERT_EQUAL_HEX64(0x808080808080807F, attacks);

    // Rook on A8 - no blockers
    attacks = get_rook_attacks(A8, 0ULL);
    TEST_ASSERT_EQUAL_HEX64(0xFE01010101010101, attacks);

    // Rook on H8 - no blockers
    attacks = get_rook_attacks(H8, 0ULL);
    TEST_ASSERT_EQUAL_HEX64(0x7F80808080808080, attacks);

    // Rook on D4 with blocker on D6
    attacks = get_rook_attacks(D4, bitboard_masks[D6]);
    TEST_ASSERT_EQUAL_HEX64(0x00000808F7080808, attacks);

    // Rook on D4 with blocker on F4
    attacks = get_rook_attacks(D4, bitboard_masks[F4]);
    TEST_ASSERT_EQUAL_HEX64(0x0808080837080808, attacks);

    // Rook on D4 with multiple blockers
    attacks = get_rook_attacks(D4, bitboard_masks[D2] | bitboard_masks[G4]);
    TEST_ASSERT_EQUAL_HEX64(0x0808080877080800, attacks);

    // Rook on E4 - center square, no blockers
    attacks = get_rook_attacks(E4, 0ULL);
    TEST_ASSERT_EQUAL_HEX64(0x10101010EF101010, attacks);

    // Rook on E4 with blockers on E2 and B4
    attacks = get_rook_attacks(E4, bitboard_masks[E2] | bitboard_masks[B4]);
    TEST_ASSERT_EQUAL_HEX64(0x10101010EE101000, attacks);

    // Corner rook with nearby blockers
    attacks = get_rook_attacks(A1, bitboard_masks[A3] | bitboard_masks[C1]);
    TEST_ASSERT_EQUAL_HEX64(0x0000000000010106, attacks);

    // Edge rook tests
    attacks = get_rook_attacks(A4, bitboard_masks[A6] | bitboard_masks[D4]);
    TEST_ASSERT_EQUAL_HEX64(0x000001010E010101, attacks);

    attacks = get_rook_attacks(H5, bitboard_masks[H2] | bitboard_masks[E5]);
    TEST_ASSERT_EQUAL_HEX64(0x8080807080808000, attacks);

    // Test blocking at board edges
    attacks = get_rook_attacks(D1, bitboard_masks[A1] | bitboard_masks[H1]);
    TEST_ASSERT_EQUAL_HEX64(0x08080808080808F7, attacks);

    attacks = get_rook_attacks(D8, bitboard_masks[A8] | bitboard_masks[H8]);
    TEST_ASSERT_EQUAL_HEX64(0xF708080808080808, attacks);
}

void test_get_castling_attacks(void) {
    board_t board;
    movelist_t moves;
    init_board(&board);

    // black king is in check
    set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
    movelist_clear(&moves);
    generate_castling_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(2, moves.moveCount);

    set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
    movelist_clear(&moves);
    generate_king_moves(&board, &moves);
    generate_castling_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(7, moves.moveCount);

    set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1");
    movelist_clear(&moves);
    generate_king_moves(&board, &moves);
    generate_castling_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(7, moves.moveCount);

    set_fen(&board, "8/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
    movelist_clear(&moves);
    generate_king_moves(&board, &moves);
    generate_castling_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(7, moves.moveCount);

    set_fen(&board, "r3k2r/8/8/8/8/8/8/8 b KQkq - 0 1");
    movelist_clear(&moves);
    generate_king_moves(&board, &moves);
    generate_castling_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(7, moves.moveCount);
}

void test_gen_en_passant(void) {
    board_t board, board_copy;
    movelist_t moves;
    move_t move;
    init_board(&board);
    movelist_clear(&moves);

    // white can attack en passant
    set_fen(&board,
            "rnbqkb1r/ppppp1pp/7n/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
    set_fen(&board_copy,
            "rnbqkb1r/ppppp1pp/7n/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");

    generate_pawn_moves(&board, &moves);

    move = create_move(E5, F6, W_PAWN, B_PAWN, 0xf, 0x5);
    make_move(&board, move);
    unmake_move(&board);

    TEST_ASSERT_EQUAL_UINT64(board_copy.hash, board.hash);
    TEST_ASSERT_TRUE(board_equal_bb(&board, &board_copy));
}

void test_generate_promotions(void) {
    board_t board;
    movelist_t moves;
    init_board(&board);

    set_fen(&board, "8/8/8/8/8/8/3p4/2R1R3 b - - 0 1");
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(12, moves.moveCount);
}

void test_generate_pawn_moves(void) {
    board_t board;
    movelist_t moves;
    init_board(&board);

    // initial position
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(16, moves.moveCount);

    set_fen(&board,
            "rnbqkbnr/pppp2pp/4p3/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(15, moves.moveCount);

    set_fen(&board, "2q1r3/3P4/8/8/8/8/8/8 w - - 0 1");
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(12, moves.moveCount);

    set_fen(&board, "4r3/3P4/8/8/8/8/8/8 w - - 0 1");
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(8, moves.moveCount);

    set_fen(&board, "8/8/8/8/8/8/3p4/2R1R3 b - - 0 1");
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(12, moves.moveCount);

    set_fen(&board, "8/8/8/8/8/8/3p4/4R3 b - - 0 1");
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(8, moves.moveCount);

    set_fen(&board,
            "rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq - 0 1");
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(16, moves.moveCount);

    set_fen(&board,
            "rnbqkbnr/pppppp1p/8/6p1/7P/8/PPPPPPP1/RNBQKBNR w KQkq - 0 1");
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(16, moves.moveCount);

    set_fen(&board,
            "rnbqk1nr/pppp1ppp/8/4p3/1b5P/1P6/P1PPPPP1/RNBQKBNR w KQkq - 0 1");
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(13, moves.moveCount);
}

void test_gen_en_passant_edgecase(void) {
    board_t board;
    movelist_t moves;
    move_t move;
    init_board(&board);

    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(16, moves.moveCount);

    move = create_move(H2, H4, W_PAWN, EMPTY, 0xf, MOVE_FLAG_DOUBLE_PAWN_PUSH);
    make_move(&board, move);
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(16, moves.moveCount);

    move = create_move(A7, A5, B_PAWN, EMPTY, 0xf, MOVE_FLAG_DOUBLE_PAWN_PUSH);
    make_move(&board, move);
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(15, moves.moveCount);

    move = create_move(A7, A5, B_PAWN, EMPTY, 0xf, MOVE_FLAG_DOUBLE_PAWN_PUSH);
    make_move(&board, move);
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(15, moves.moveCount);

    init_board(&board);
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(16, moves.moveCount);

    move = create_move(E2, E3, W_PAWN, EMPTY, 0xf, 0);
    make_move(&board, move);
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(16, moves.moveCount);

    move = create_move(A7, A5, B_PAWN, EMPTY, 0xf, MOVE_FLAG_DOUBLE_PAWN_PUSH);
    make_move(&board, move);
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(15, moves.moveCount);

    move = create_move(H2, H4, W_PAWN, EMPTY, 0xf, MOVE_FLAG_DOUBLE_PAWN_PUSH);
    make_move(&board, move);
    movelist_clear(&moves);
    generate_pawn_moves(&board, &moves);
    TEST_ASSERT_EQUAL_INT(15, moves.moveCount);
}

void test_perft(void) {
    board_t board;
    init_board(&board);
    uint64_t nodes = 0;

    // test the starting positoon
    nodes = perft(&board, 1);
    TEST_ASSERT_EQUAL_UINT64(20, nodes);
    nodes = perft(&board, 2);
    TEST_ASSERT_EQUAL_UINT64(400, nodes);
    nodes = perft(&board, 3);
    TEST_ASSERT_EQUAL_UINT64(8902, nodes);
    nodes = perft(&board, 4);
    TEST_ASSERT_EQUAL_UINT64(197281, nodes);
    nodes = perft(&board, 5);
    TEST_ASSERT_EQUAL_UINT64(4865609, nodes);

    // kiwipete
    set_fen(
        &board,
        "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    nodes = perft(&board, 1);
    TEST_ASSERT_EQUAL_UINT64(48, nodes);
    nodes = perft(&board, 2);
    TEST_ASSERT_EQUAL_UINT64(2039, nodes);
    nodes = perft(&board, 3);
    TEST_ASSERT_EQUAL_UINT64(97862, nodes);
    nodes = perft(&board, 4);
    TEST_ASSERT_EQUAL_UINT64(4085603, nodes);

    // https://analog-hors.github.io/webperft/ pos 3
    set_fen(&board, "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    nodes = perft(&board, 1);
    TEST_ASSERT_EQUAL_UINT64(14, nodes);
    nodes = perft(&board, 2);
    TEST_ASSERT_EQUAL_UINT64(191, nodes);
    nodes = perft(&board, 3);
    TEST_ASSERT_EQUAL_UINT64(2812, nodes);
    nodes = perft(&board, 4);
    TEST_ASSERT_EQUAL_UINT64(43238, nodes);
    nodes = perft(&board, 5);
    TEST_ASSERT_EQUAL_UINT64(674624, nodes);
    nodes = perft(&board, 6);
    TEST_ASSERT_EQUAL_UINT64(11030083, nodes);

    // https://analog-hors.github.io/webperft/ pos 4
    set_fen(&board,
            "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    nodes = perft(&board, 1);
    TEST_ASSERT_EQUAL_UINT64(6, nodes);
    nodes = perft(&board, 2);
    TEST_ASSERT_EQUAL_UINT64(264, nodes);
    nodes = perft(&board, 3);
    TEST_ASSERT_EQUAL_UINT64(9467, nodes);
    nodes = perft(&board, 4);
    TEST_ASSERT_EQUAL_UINT64(422333, nodes);
    nodes = perft(&board, 5);
    TEST_ASSERT_EQUAL_UINT64(15833292, nodes);

    // https://analog-hors.github.io/webperft/ pos 5
    set_fen(&board,
            "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    nodes = perft(&board, 1);
    TEST_ASSERT_EQUAL_UINT64(44, nodes);
    nodes = perft(&board, 2);
    TEST_ASSERT_EQUAL_UINT64(1486, nodes);
    nodes = perft(&board, 3);
    TEST_ASSERT_EQUAL_UINT64(62379, nodes);
    nodes = perft(&board, 4);
    TEST_ASSERT_EQUAL_UINT64(2103487, nodes);

    set_fen(&board,
            "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
    nodes = perft(&board, 1);
    TEST_ASSERT_EQUAL_UINT64(48, nodes);
    nodes = perft(&board, 2);
    TEST_ASSERT_EQUAL_UINT64(2039, nodes);
    nodes = perft(&board, 3);
    TEST_ASSERT_EQUAL_UINT64(97862, nodes);
    nodes = perft(&board, 4);
    TEST_ASSERT_EQUAL_UINT64(4085603, nodes);

    set_fen(&board, "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
    nodes = perft(&board, 1);
    TEST_ASSERT_EQUAL_UINT64(14, nodes);
    nodes = perft(&board, 2);
    TEST_ASSERT_EQUAL_UINT64(191, nodes);
    nodes = perft(&board, 3);
    TEST_ASSERT_EQUAL_UINT64(2812, nodes);
    nodes = perft(&board, 4);
    TEST_ASSERT_EQUAL_UINT64(43238, nodes);
    nodes = perft(&board, 5);
    TEST_ASSERT_EQUAL_UINT64(674624, nodes);

    set_fen(&board,
            "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    nodes = perft(&board, 1);
    TEST_ASSERT_EQUAL_UINT64(6, nodes);
    nodes = perft(&board, 2);
    TEST_ASSERT_EQUAL_UINT64(264, nodes);
    nodes = perft(&board, 3);
    TEST_ASSERT_EQUAL_UINT64(9467, nodes);
    nodes = perft(&board, 4);
    TEST_ASSERT_EQUAL_UINT64(422333, nodes);

    set_fen(&board,
            "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    nodes = perft(&board, 1);
    TEST_ASSERT_EQUAL_UINT64(44, nodes);
    nodes = perft(&board, 2);
    TEST_ASSERT_EQUAL_UINT64(1486, nodes);
    nodes = perft(&board, 3);
    TEST_ASSERT_EQUAL_UINT64(62379, nodes);

    set_fen(&board,
            "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - "
            "- 0 10");
    nodes = perft(&board, 1);
    TEST_ASSERT_EQUAL_UINT64(46, nodes);
    nodes = perft(&board, 2);
    TEST_ASSERT_EQUAL_UINT64(2079, nodes);
    nodes = perft(&board, 3);
    TEST_ASSERT_EQUAL_UINT64(89890, nodes);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_king_attacks);
    RUN_TEST(test_get_pawn_attacks);
    RUN_TEST(test_get_knight_attacks);
    RUN_TEST(test_get_bishop_attacks);
    RUN_TEST(test_get_rook_attacks);
    RUN_TEST(test_get_castling_attacks);
    RUN_TEST(test_gen_en_passant);
    RUN_TEST(test_gen_en_passant_edgecase);
    RUN_TEST(test_generate_pawn_moves);
    RUN_TEST(test_generate_promotions);
    // RUN_TEST(test_perft);
    return UNITY_END();
}