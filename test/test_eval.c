#include "board.h"
#include "eval.h"
#include "unity.h"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_eval(void)
{
    board_t board;
    initialize_eval();
    init_board(&board);
    TEST_ASSERT_EQUAL_INT(0, evaluate_board(&board));

//     set_fen(&board,
//             "4k3/1Q4P1/8/2b5/5n2/8/2r5/4K3 w - - 0 1");
//     TEST_ASSERT_EQUAL_INT(0, evaluate_board(&board));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_eval);
    return UNITY_END();
}