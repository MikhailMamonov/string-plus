#include <string.h>
#include <stdlib.h>
#include <check.h>
#include "../s21_string.h"

// Структура параметров теста
typedef struct {
    const char *str1;
    const char *str2;
    s21_size_t n;
} strncmpParams;

// Макрос для создания тестовых наборов
#define TEST_CASES(name, ...) \
    static strncmpParams name[] = {__VA_ARGS__}; \
    START_TEST(test_##name) { \
        for (s21_size_t i = 0; i < sizeof(name)/sizeof(name[0]); i++) { \
            run_strncmp_test(&name[i]); \
        } \
    } \
    END_TEST

// Публичная функция запуска теста
void run_strncmp_test(strncmpParams *params) {
    ck_assert_int_eq(s21_strncmp(params->str1, params->str2, params->n), strncmp(params->str1, params->str2, params->n));
}

TEST_CASES(string_tests,
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

TEST_CASES(edge_tests,
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
