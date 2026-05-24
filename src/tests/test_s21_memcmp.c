#include <check.h>
#include <string.h>
#include <stdlib.h>

#include "../s21_string.h"          // здесь у вас должна быть s21_memcmp и s21_size_t
#include "s21_test_common.h"

/* Нормализация знака результата к -1, 0, 1, чтобы сравнения были устойчивы
 *  между разными реализациями memcmp (некоторые возвращают разницу байтов,
 *  а наша может возвращать -1/0/1). */
static int sign(int v) {
    return (v > 0) - (v < 0);
}

static void run_memcmp_test(const memcmpParams *p) {
    int expected = memcmp(p->str1, p->str2, p->n);
    int actual   = s21_memcmp(p->str1, p->str2, p->n);
    ck_assert_msg(sign(expected) == sign(actual),
                  "FAIL [%s]: s21_memcmp=%d, memcmp=%d, n=%zu",
                  p->test_name ? p->test_name : "no_name",
                  actual, expected, (size_t)p->n);
}

/* Наборы тестов */

MEMCMP_TEST_CASES(memcmp_equal_strings,
                  {"Hello, World!", "Hello, World!", 13, "equal_strings"},
                  {"",              "",              0,  "empty_zero_n"},
                  {"abc",           "abc",           3,  "abc_equal"},
                  {"abcdef",        "abcdef",        6,  "abcdef_equal"}
)

MEMCMP_TEST_CASES(memcmp_different_strings,
                  {"Hello",   "World",   5, "hello_vs_world"},
                  {"abc",     "abd",     3, "abc_vs_abd"},
                  {"abc",     "abz",     3, "abc_vs_abz"},
                  {"A",       "B",       1, "A_vs_B"},
                  {"School21","School42",8, "school21_vs_school42"}
)

MEMCMP_TEST_CASES(memcmp_partial_compare,
                  {"Hello, World!", "Hello, There!", 5,  "first_5_equal"},
                  {"abcdef",        "abcxyz",        3,  "first_3_equal"},
                  {"abcdef",        "abcxyz",        4,  "first_4_diff"},
                  {"12345",         "12399",         3,  "first_3_eq_num"}
)

MEMCMP_TEST_CASES(memcmp_zero_length,
                  {"abc",   "xyz",   0, "zero_n_diff"},
                  {"same",  "same",  0, "zero_n_same"},
                  {"",      "",      0, "zero_n_empty"}
)

MEMCMP_TEST_CASES(memcmp_binary_data,
                  {"\x00\x01\x02\x03", "\x00\x01\x02\x03", 4, "binary_equal"},
                  {"\x00\x01\x02\x03", "\x00\x01\x02\x04", 4, "binary_last_diff"},
                  {"\xff\xfe\xfd",     "\x01\x02\x03",     3, "high_byte_vs_low"},
                  {"\x00\x00\x00",     "\x00\x00\x01",     3, "trailing_diff"}
)

MEMCMP_TEST_CASES(memcmp_with_nulls_inside,
                  {"abc\0def", "abc\0def", 7, "nulls_inside_equal"},
                  {"abc\0def", "abc\0xyz", 7, "nulls_inside_diff"},
                  {"abc\0def", "abc\0def", 3, "before_null"}
)

/* Сборка suite */

Suite *memcmp_suite_create(void) {
    Suite *s = suite_create("memcmp");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, test_memcmp_equal_strings);
    tcase_add_test(tc, test_memcmp_different_strings);
    tcase_add_test(tc, test_memcmp_partial_compare);
    tcase_add_test(tc, test_memcmp_zero_length);
    tcase_add_test(tc, test_memcmp_binary_data);
    tcase_add_test(tc, test_memcmp_with_nulls_inside);

    suite_add_tcase(s, tc);
    return s;
}

