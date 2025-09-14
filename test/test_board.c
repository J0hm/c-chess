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
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_INT(0, board.inCheck);
    TEST_ASSERT_EQUAL_INT(0, board.lastTriggerPly);
    TEST_ASSERT_EQUAL_INT(0, board.repetitions);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(1, board.fullMoves);
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
    int ret = 0;

    // en passant available (e3 square)
    ret = set_fen(
        &board, "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(BLACK, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(E3, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(1, board.fullMoves);

    // en passant available (d6 square)
    ret = set_fen(
        &board, "rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(D6, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(3, board.fullMoves);

    // no castling rights
    ret = set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R w - - 0 1");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x0, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(1, board.fullMoves);

    // white kingside castling
    ret = set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R b K - 5 10");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(1, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x1, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(5, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(10, board.fullMoves);

    // black queenside castling
    ret = set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R w q - 25 50");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x8, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(25, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(50, board.fullMoves);

    // mixed castling rights
    ret = set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R b Kq - 0 1");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(1, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x9, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(1, board.fullMoves);

    // high move numbers
    ret = set_fen(&board, "8/8/8/8/8/8/8/4K3 w - - 99 150");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x0, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(99, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(150, board.fullMoves);

    // en passant on a-file
    ret = set_fen(
        &board, "rnbqkbnr/1ppppppp/8/pP6/8/8/P1PPPPPP/RNBQKBNR w KQkq a6 0 3");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(A6, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(3, board.fullMoves);

    // en passant on h-file
    ret = set_fen(
        &board, "rnbqkbnr/pppppp1p/8/6Pp/8/8/PPPPPP1P/RNBQKBNR w KQkq h6 0 3");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(H6, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(3, board.fullMoves);

    // complex middle game position
    ret = set_fen(
        &board,
        "r1bqk2r/pp2nppp/2n1p3/3p4/2PP4/2N1PN2/PP3PPP/R1BQKB1R b KQkq - 2 8");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(1, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(2, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(8, board.fullMoves);

    // pPromoted queen
    ret = set_fen(&board, "r1bQk2r/pp2nppp/2n1p3/8/8/8/8/4K3 w - - 0 1");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x0, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(1, board.fullMoves);

    // all castling rights
    ret = set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(1, board.fullMoves);

    // white queenside only
    ret = set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R b Q - 0 1");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(1, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x2, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(1, board.fullMoves);

    // black kingside only
    ret = set_fen(&board, "r3k2r/8/8/8/8/8/8/R3K2R w k - 10 25");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x4, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(10, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(25, board.fullMoves);

    // 50-Move rule edge case
    ret = set_fen(&board, "8/8/8/8/8/8/8/4K3 b - - 50 100");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(1, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x0, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(50, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(100, board.fullMoves);

    // en passant on e6 (black pawn moved)
    ret = set_fen(
        &board, "rnbqkbnr/pppp1ppp/8/4pP2/8/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(E6, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(2, board.fullMoves);

    // en passant on c3 (white pawn can capture)
    ret = set_fen(
        &board, "rnbqkbnr/pp1ppppp/8/8/2Pp4/8/PP1PPPPP/RNBQKBNR b KQkq c3 0 2");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(1, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(C3, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(2, board.fullMoves);

    // maximum fullmove number
    ret = set_fen(&board, "8/8/8/8/8/8/8/4K3 w - - 0 999");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x0, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(999, board.fullMoves);

    // multiple promoted pieces
    ret = set_fen(&board, "2Q1Q3/8/8/8/8/8/8/4K3 w - - 0 1");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x0, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(1, board.fullMoves);

    ret = set_fen(&board,
                  "rnbq1bnr/ppp1pkpp/8/3pPp2/8/8/PPPPKPPP/RNBQ1BNR w - - 0 4");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(0, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0x0, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(ER, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(4, board.fullMoves);

    TEST_ASSERT_EQUAL_UINT64(0x000000100000EF00ULL, board.pcbb[W_PAWN]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000042ULL, board.pcbb[W_KNIGHT]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000024ULL, board.pcbb[W_BISHOP]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000081ULL, board.pcbb[W_ROOK]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000008ULL, board.pcbb[W_QUEEN]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000001000ULL, board.pcbb[W_KING]);

    TEST_ASSERT_EQUAL_UINT64(0x00D7002800000000ULL, board.pcbb[B_PAWN]);
    TEST_ASSERT_EQUAL_UINT64(0x4200000000000000ULL, board.pcbb[B_KNIGHT]);
    TEST_ASSERT_EQUAL_UINT64(0x2400000000000000ULL, board.pcbb[B_BISHOP]);
    TEST_ASSERT_EQUAL_UINT64(0x8100000000000000ULL, board.pcbb[B_ROOK]);
    TEST_ASSERT_EQUAL_UINT64(0x0800000000000000ULL, board.pcbb[B_QUEEN]);
    TEST_ASSERT_EQUAL_UINT64(0x0020000000000000ULL, board.pcbb[B_KING]);

    ret = set_fen(
        &board,
        "rnbqkbnr/p1pppppp/8/8/PpP4P/8/1P1PPPP1/RNBQKBNR b KQkq c3 0 3");
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_UINT8(1, board.sideToMove);
    TEST_ASSERT_EQUAL_UINT8(0xF, board.castlingRights);
    TEST_ASSERT_EQUAL_UINT64(C3, board.enPassantSquare);
    TEST_ASSERT_EQUAL_INT(0, board.halfMoves);
    TEST_ASSERT_EQUAL_INT(3, board.fullMoves);

    TEST_ASSERT_EQUAL_UINT64(0x0000000085007A00ULL, board.pcbb[W_PAWN]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000042ULL, board.pcbb[W_KNIGHT]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000024ULL, board.pcbb[W_BISHOP]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000081ULL, board.pcbb[W_ROOK]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000008ULL, board.pcbb[W_QUEEN]);
    TEST_ASSERT_EQUAL_UINT64(0x0000000000000010ULL, board.pcbb[W_KING]);

    TEST_ASSERT_EQUAL_UINT64(0x00FD000002000000ULL, board.pcbb[B_PAWN]);
    TEST_ASSERT_EQUAL_UINT64(0x4200000000000000ULL, board.pcbb[B_KNIGHT]);
    TEST_ASSERT_EQUAL_UINT64(0x2400000000000000ULL, board.pcbb[B_BISHOP]);
    TEST_ASSERT_EQUAL_UINT64(0x8100000000000000ULL, board.pcbb[B_ROOK]);
    TEST_ASSERT_EQUAL_UINT64(0x0800000000000000ULL, board.pcbb[B_QUEEN]);
    TEST_ASSERT_EQUAL_UINT64(0x1000000000000000ULL, board.pcbb[B_KING]);
}

void test_bb_equals(void) {
    board_t board1, board2;
    board_t* board_ptr;
    init_board(&board1);
    init_board(&board2);
    TEST_ASSERT_TRUE(board_equal_hash(&board1, &board2));
    TEST_ASSERT_TRUE(board_equal_exact(&board1, &board2));
    TEST_ASSERT_TRUE(board_equal_bb(&board1, &board2));

    set_fen(
        &board1,
        "r1bqk2r/pp2nppp/2n1p3/3p4/2PP4/2N1PN2/PP3PPP/R1BQKB1R b KQkq - 2 8");
    TEST_ASSERT_FALSE(board_equal_hash(&board1, &board2));
    TEST_ASSERT_FALSE(board_equal_exact(&board1, &board2));
    TEST_ASSERT_FALSE(board_equal_bb(&board1, &board2));

    set_fen(
        &board2,
        "r1bqk2r/pp2nppp/2n1p3/3p4/2PP4/2N1PN2/PP3PPP/R1BQKB1R b KQkq - 2 8");
    TEST_ASSERT_TRUE(board_equal_hash(&board1, &board2));
    TEST_ASSERT_TRUE(board_equal_exact(&board1, &board2));
    TEST_ASSERT_TRUE(board_equal_bb(&board1, &board2));

    board_ptr = &board1;
    TEST_ASSERT_TRUE(board_equal_hash(&board1, board_ptr));
    TEST_ASSERT_TRUE(board_equal_exact(&board1, board_ptr));
    TEST_ASSERT_TRUE(board_equal_bb(&board1, board_ptr));
}

void test_bb_clone(void) {
    board_t board1, board2;
    init_board(&board1);
    board_clone(&board1, &board2);
    TEST_ASSERT_TRUE(board_equal_hash(&board1, &board2));
    TEST_ASSERT_TRUE(board_equal_exact(&board1, &board2));
    TEST_ASSERT_TRUE(board_equal_bb(&board1, &board2));

    set_fen(
        &board1,
        "r1bqk2r/pp2nppp/2n1p3/3p4/2PP4/2N1PN2/PP3PPP/R1BQKB1R b KQkq - 2 8");
    board_clone(&board2, &board1);
    TEST_ASSERT_TRUE(board_equal_hash(&board1, &board2));
    TEST_ASSERT_TRUE(board_equal_exact(&board1, &board2));
    TEST_ASSERT_TRUE(board_equal_bb(&board1, &board2));
}

void test_make_unmake(void) {
    board_t board_base, board_test;
    move_t move;
    init_board(&board_base);
    init_board(&board_test);
    TEST_ASSERT_TRUE(board_equal_hash(&board_base, &board_test));
    TEST_ASSERT_TRUE(board_equal_bb(&board_base, &board_test));

    move = create_move(E2, E3, W_PAWN, EMPTY, 0, 0);
    make_move(&board_test, move);
    unmake_move(&board_test);
    TEST_ASSERT_TRUE(board_equal_hash(&board_test, &board_base));
    TEST_ASSERT_TRUE(board_equal_bb(&board_test, &board_base));

    make_move(&board_test, move);
    unmake_move(&board_test);
    TEST_ASSERT_TRUE(board_equal_hash(&board_test, &board_base));
    TEST_ASSERT_TRUE(board_equal_bb(&board_test, &board_base));

    make_move(&board_test, move);
    move = create_move(E7, E5, B_PAWN, EMPTY, 0, MOVE_FLAG_DOUBLE_PAWN_PUSH);
    make_move(&board_test, move);
    move = create_move(E3, E4, W_PAWN, EMPTY, 0, 0);
    unmake_move(&board_test);
    unmake_move(&board_test);
    TEST_ASSERT_TRUE(board_equal_hash(&board_test, &board_base));
    TEST_ASSERT_TRUE(board_equal_bb(&board_test, &board_base));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_init);
    RUN_TEST(test_set_fen);
    RUN_TEST(test_bb_equals);
    RUN_TEST(test_bb_clone);
    RUN_TEST(test_make_unmake);
    return UNITY_END();
}