#include "unity.h"
#include "util.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_get_value_returns_20(void) {
    TEST_ASSERT_EQUAL_INT(20, get_value());
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_value_returns_20);
    return UNITY_END();
}