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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_king_attacks);
    RUN_TEST(test_get_pawn_attacks);
    RUN_TEST(test_get_knight_attacks);
    RUN_TEST(test_get_bishop_attacks);
    RUN_TEST(test_get_rook_attacks);
    return UNITY_END();
}