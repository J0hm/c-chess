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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_king_attacks);
    RUN_TEST(test_get_pawn_attacks);
    RUN_TEST(test_get_knight_attacks);
    return UNITY_END();
}