#include "board.h"
#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_init(void) {
    board_t board;
    init_board(&board);

    // test initial values
    TEST_ASSERT_EQUAL_UINT64(0, board.hash);
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_INT(0, board.inCheck);
    TEST_ASSERT_EQUAL_INT(0, board.lastTriggerPly);
    TEST_ASSERT_EQUAL_INT(0, board.repetitions);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(1, board.fullMoves);
    TEST_ASSERT_NULL(board.lastMove);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);

    // test bitboard equality for starting position
    TEST_ASSERT_EQUAL_UINT64(0x000000000000FF00ULL, board.pcbb[W_PAWN]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000042ULL, board.pcbb[W_KNIGHT]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000024ULL, board.pcbb[W_BISHOP]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000081ULL, board.pcbb[W_ROOK]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000008ULL, board.pcbb[W_QUEEN]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000010ULL, board.pcbb[W_KING]);

    TEST_ASSERT_EQUAL_UINT64(0x00FF000000000000ULL, board.pcbb[B_PAWN]);
    TEST_ASSERT_EQUAL_UINT64(0x4200000000000000ULL, board.pcbb[B_KNIGHT]);
    TEST_ASSERT_EQUAL_UINT64(0x2400000000000000ULL, board.pcbb[B_BISHOP]);
    TEST_ASSERT_EQUAL_UINT64(0x8100000000000000ULL, board.pcbb[B_ROOK]);
    TEST_ASSERT_EQUAL_UINT64(0x0800000000000000ULL, board.pcbb[B_QUEEN]);
    TEST_ASSERT_EQUAL_UINT64(0x1000000000000000ULL, board.pcbb[B_KING]);

    // test occupied bitboards
    TEST_ASSERT_EQUAL_UINT64(0x000000000000FFFFULL,
                             board.occupied[0]);  // White occupied (ranks 1-2)
    TEST_ASSERT_EQUAL_UINT64(0xFFFF000000000000ULL,
                             board.occupied[1]);  // Black occupied (ranks 7-8)

    // test squares array for starting position
    // Rank 1 (White back rank)
    TEST_ASSERT_EQUAL_UINT8(W_ROOK, board.squares[A1]);
    TEST_ASSERT_EQUAL_UINT8(W_KNIGHT, board.squares[B1]);
    TEST_ASSERT_EQUAL_UINT8(W_BISHOP, board.squares[C1]);
    TEST_ASSERT_EQUAL_UINT8(W_QUEEN, board.squares[D1]);
    TEST_ASSERT_EQUAL_UINT8(W_KING, board.squares[E1]);
    TEST_ASSERT_EQUAL_UINT8(W_BISHOP, board.squares[F1]);
    TEST_ASSERT_EQUAL_UINT8(W_KNIGHT, board.squares[G1]);
    TEST_ASSERT_EQUAL_UINT8(W_ROOK, board.squares[H1]);

    // Rank 2 (White pawns)
    for (int i = 8; i < 16; i++) {
        TEST_ASSERT_EQUAL_UINT8(W_PAWN, board.squares[i]);  // A2-H2
    }

    // Ranks 3-6 (Empty squares)
    for (int i = 16; i < 48; i++) {
        TEST_ASSERT_EQUAL_UINT8(EMPTY, board.squares[i]);  // Empty squares
    }

    // Rank 7 (Black pawns)
    for (int i = 48; i < 56; i++) {
        TEST_ASSERT_EQUAL_UINT8(B_PAWN, board.squares[i]);  // A7-H7
    }

    // Rank 8 (Black back rank)
    TEST_ASSERT_EQUAL_UINT8(B_ROOK, board.squares[A8]);
    TEST_ASSERT_EQUAL_UINT8(B_KNIGHT, board.squares[B8]);
    TEST_ASSERT_EQUAL_UINT8(B_BISHOP, board.squares[C8]);
    TEST_ASSERT_EQUAL_UINT8(B_QUEEN, board.squares[D8]);
    TEST_ASSERT_EQUAL_UINT8(B_KING, board.squares[E8]);
    TEST_ASSERT_EQUAL_UINT8(B_BISHOP, board.squares[F8]);
    TEST_ASSERT_EQUAL_UINT8(B_KNIGHT, board.squares[G8]);
    TEST_ASSERT_EQUAL_UINT8(B_ROOK, board.squares[H8]);
}

void test_set_fen(void) {
    board_t board;
    init_board(&board);

    // TODO test some other starting positions, including some with en passant
    // and a variety of castling
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_init);
    return UNITY_END();
}