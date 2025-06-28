#include <string.h>
#include <stdio.h>

int tests_failed = 0;
int tests_ran = 0;
int assertions_failed = 0;

static int test_finish() {
    printf("\n%d assertions failed\n", assertions_failed);
    printf("\nfinished testing.\n");
    printf("%d/%d tests(s) passed\n", tests_ran - tests_failed, tests_ran);

    return tests_failed == 0;
}

void run_test(void (*fp)()) {
    int prev_assertions_failed = assertions_failed;
    fp();
    tests_ran++;

    if (prev_assertions_failed != assertions_failed) {
        printf("test '%d' failed", tests_ran - 1);
        tests_failed++;
    }
}

#define assert(condition) \
    do { \
        if (!(condition)) { \
            assertions_failed++; \
        } \
    } while (0)

void assert_char_eq(char a, char b) {
    assert(a == b);
}

void assert_string_eq(char *a, char *b) {
    assert(strcmp(a, b) == 0);
}

void assert_true(int condition) {
    assert(condition);
}

void assert_false(int condition) {
    assert(!condition);
}