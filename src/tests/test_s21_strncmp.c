#include <string.h>
#include <stdlib.h>
#include <check.h>
#include "../s21_string.h"
#include "s21_test_common.h"

int sign(int x) {
    return (x > 0) - (x < 0);
}

// Публичная функция запуска теста
void run_strncmp_test(strncmpParams *params) {
    ck_assert_int_eq(sign(s21_strncmp(params->str1, params->str2, params->n)), sign(strncmp(params->str1, params->str2, params->n)));
}

STRNCMP_TEST_CASES(string_tests,
    {"hello", "hello", 5},
    {"hello", "hell", 4},
    {"apple", "apricot", 2},
    {"apple", "banana", 0},
    {"cat", "cat", 10},
    {"Hello", "hello", 5},
    {"hello", "Hello", 5},
    {"apple", "applepie", 8},
    {"applepie", "apple", 8},
    {"abc", "xyz", 3}
)

STRNCMP_TEST_CASES(edge_tests,
    {"", "", 5},
    {"", "abc", 3},
    {"abc", "", 3},
    {"", "hello", 0},
    {"\x80", "\x10", 1},
    {"hell\0no", "hell", 6}
);

// Функция, которую вызовет Runner
Suite *strncmp_suite_create(void) {
    Suite *s = suite_create("strncmp");

    TCase *tc_string = tcase_create("String tests");
    tcase_add_test(tc_string, test_string_tests);
    suite_add_tcase(s, tc_string);

    TCase *tc_edge = tcase_create("Edge tests");
    tcase_add_test(tc_edge, test_edge_tests);
    suite_add_tcase(s, tc_edge);
    return s;
}
