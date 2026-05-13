#include <check.h>
#include "../s21_string.h"
#include <string.h>

char *inputs_src[] = {"apple", "verter", "", ""};
s21_size_t inputs_n[] = {5, 3, 1, 0};

START_TEST(test_copy) {
    char dest_expected[20] = {0};
    char dest_test[20] = {0};

    s21_memcpy(dest_test, inputs_src[_i], inputs_n[_i]);
    memcpy(dest_expected, inputs_src[_i], inputs_n[_i]);
    ck_assert_mem_eq(dest_test, dest_expected, inputs_n[_i]);
}
END_TEST

// Функция, которую вызовет Runner
Suite *memcpy_suite_create(void) {
    Suite *s = suite_create("Memcpy");
    TCase *tc = tcase_create("Valid");

    int num_tests = sizeof(inputs_n) / sizeof(inputs_n[0]);
    tcase_add_loop_test(tc, test_copy, 0, num_tests);
    suite_add_tcase(s, tc);
    return s;
}
