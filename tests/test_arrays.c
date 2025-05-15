#include "greatest.h"
#include "../src/ar.h"
#include <stddef.h>

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

TEST ar_pop_should_pop(void) {
    // Example with int array
    int* int_array = NULL;
    ar_put(int_array, 10);
    ar_put(int_array, 20);
    ar_put(int_array, 30);
    ar_put(int_array, 40);

    printf("Int Array Original (len %td): ", ar_len(int_array));
    for (ptrdiff_t i = 0; i < ar_len(int_array); ++i) {
        printf("%d ", int_array[i]);
    }
    printf("\n"); // Expected: 10 20 30 40

    // Pop last element using 1-arg ar_pop
    int popped_int_last = ar_pop(int_array);
    printf("Popped last int (1 arg ar_pop): %d (len %td)\n", popped_int_last, ar_len(int_array)); // Expected: 40, len 3
    printf("Int Array After 1-arg ar_pop: ");
    for (ptrdiff_t i = 0; i < ar_len(int_array); ++i) {
        printf("%d ", int_array[i]);
    }
    printf("\n"); // Expected: 10 20 30

    // Pop element at index 1 using 2-arg ar_pop (value 20)
    int popped_int_indexed = ar_pop(int_array, 1);
    printf("Popped int at index 1 (2 args ar_pop): %d (len %td)\n", popped_int_indexed, ar_len(int_array)); // Expected: 20, len 2

    printf("Int Array After 2-arg ar_pop: ");
    for (ptrdiff_t i = 0; i < ar_len(int_array); ++i) {
        printf("%d ", int_array[i]);
    }
    printf("\n"); // Expected: 10 30
    ar_free(int_array);
    PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
    RUN_TEST(arrput_should_put);
    RUN_TEST(ar_shift_should_change_array);
    RUN_TEST(ar_pop_should_pop);
    GREATEST_MAIN_END();
    return 0;
}
