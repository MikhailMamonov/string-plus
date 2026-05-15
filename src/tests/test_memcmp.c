#include <check.h>
#include "../s21_string.h"
#include <string.h>

char *src1[] = {"apple", "abc", "xyz"};
char *src2[] = {"apple", "abd", "aaa"};
s21_size_t sizes[] = {5, 3, 3};

START_TEST(test_memcmp) {
    int result   = s21_memcmp(src1[_i], src2[_i], sizes[_i]);
    int expected =    memcmp(src1[_i], src2[_i], sizes[_i]);
    ck_assert_int_eq((result > 0) - (result < 0), (expected > 0) - (expected < 0));
}
END_TEST

Suite *memcmp_suite_create(void) {
    Suite *s = suite_create("Memcmp");
    TCase *tc = tcase_create("Valid");

    int num_tests = sizeof(sizes) / sizeof(sizes[0]);
    tcase_add_loop_test(tc, test_memcmp, 0, num_tests);
    suite_add_tcase(s, tc);
    return s;
}
