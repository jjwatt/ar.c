#include "greatest.h"
#include "../src/stb_ds.h"
#include "../src/ar.h"

TEST arrput_should_put(void) {
    int *array = NULL;
    arrput(array, 2);
    arrput(array, 3);
    FAIL();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
    RUN_TEST(arrput_should_put);
    GREATEST_MAIN_END();
    return 0;
}
