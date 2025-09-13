#include "move.h"
#include "types.h"
#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_create_move(void) {
    move_t move = create_move(A2, A4, W_PAWN, EMPTY, 0xF, MOVE_FLAG_DOUBLE_PAWN_PUSH);
    uint32_t m32 = move.move32;

    TEST_ASSERT_EQUAL_UINT32(A2, MOVE32_SRC(m32));
    TEST_ASSERT_EQUAL_UINT32(A4, MOVE32_DST(m32));
    TEST_ASSERT_EQUAL_UINT32(W_PAWN, MOVE32_PIECE_TYPE(m32));
    TEST_ASSERT_EQUAL_UINT32(EMPTY, MOVE32_CAPTURED_PIECE(m32));
    TEST_ASSERT_EQUAL_UINT32(0xF, MOVE32_CASTLING_RIGHTS(m32));
    TEST_ASSERT_EQUAL_UINT32(MOVE_FLAG_DOUBLE_PAWN_PUSH, MOVE32_FLAGS(m32));

    MOVE32_SET_CAPTURED_PIECE_TYPE(m32, B_PAWN);
    TEST_ASSERT_EQUAL_UINT32(B_PAWN, MOVE32_CAPTURED_PIECE(m32));

    MOVE32_SET_DST(m32, A5);
    TEST_ASSERT_EQUAL_UINT32(A5, MOVE32_DST(m32));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_move);
    return UNITY_END();
}