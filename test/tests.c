#include <string.h>

int bad_assertions = 0;
int tests_ran = 0;

static void assert_fail() {
    printf("assertion failed.\n");
    bad_assertions++;
}

static int test_finish() {
    printf("finished testing.\n");
    printf("%d/%d test(s) passed\n", tests_ran - bad_assertions, tests_ran);

    return bad_assertions == 0;
}

#define assert(condition) \
    do { \
        tests_ran++; \
        if (!(condition)) { \
            assert_fail(); \
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