#include "greatest.h"
#include "../src/ar.h"

TEST arrput_should_put(void) {
    int *array = NULL;
    ar_put(array, 1);
    ar_put(array, 2);
    ar_put(array, 3);
    ar_free(array);
    PASS();
}

TEST ar_shift_should_change_array(void) {
    int *array = NULL;
    ar_put(array, 1);
    ar_put(array, 2);
    ar_shift(array);
    ASSERT_EQ(ar_len(array), 1);
    ar_free(array);
    PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
    RUN_TEST(arrput_should_put);
    RUN_TEST(ar_shift_should_change_array);
    GREATEST_MAIN_END();
    return 0;
}
