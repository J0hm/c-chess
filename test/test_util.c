#include "unity.h"
#include "util.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_printbb(void) {
    TEST_ASSERT_EQUAL_INT32(20, 20);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_printbb);
    return UNITY_END();
}