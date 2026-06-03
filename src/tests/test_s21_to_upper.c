#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"
#include "s21_test_common.h"

static void run_to_upper_test(toUpperParams *params) {
    char *result = (char *)s21_to_upper(params->str);

    if (params->expected == s21_NULL) {
        ck_assert_ptr_null(result);
    } else {
        ck_assert_ptr_nonnull(result);
        ck_assert_pstr_eq(result, params->expected);
        ck_assert_ptr_ne((void *)result, (void *)params->str);
        free(result);
    }

    printf("[PASS] %s\n", params->test_name);
}

// Основные случаи: разный регистр, цифры, символы
TO_UPPER_TEST_CASES(
    to_upper_basic,
    {"hello",            "HELLO",            "all lowercase"},
    {"HELLO",            "HELLO",            "already uppercase"},
    {"HeLLo WoRLd",      "HELLO WORLD",      "mixed case"},
    {"Hello, World! 123","HELLO, WORLD! 123","letters + punct + digits"},
    {"1234567890",       "1234567890",       "only digits"},
    {"!@#$%^&*()",       "!@#$%^&*()",       "only symbols"})

// Граничные случаи
TO_UPPER_TEST_CASES(
    to_upper_edge,
    {"",          "",          "empty string"},
    {"a",         "A",         "single lowercase letter"},
    {"Z",         "Z",         "single uppercase letter"},
    {"?",         "?",         "single non-letter"},
    {"az",        "AZ",        "boundary letters a and z"},
    {"`{|}",      "`{|}",      "ASCII neighbors of letters"})

// Пробельные символы
TO_UPPER_TEST_CASES(
    to_upper_whitespace,
    {"  hello\tworld\n", "  HELLO\tWORLD\n", "spaces, tab, newline"},
    {"     ",         "     ",         "only spaces"},
    {"\t\n\r",        "\t\n\r",        "only control whitespace"})

// Длинная строка
TO_UPPER_TEST_CASES(
    to_upper_long,
    {"the quick brown fox jumps over the lazy dog 1234567890 times",
        "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG 1234567890 TIMES",
        "long pangram"})

// NULL на входе — ожидаем NULL на выходе
TO_UPPER_TEST_CASES(
    to_upper_null,
    {s21_NULL, s21_NULL, "NULL input returns NULL"})

START_TEST(test_to_upper_original_unchanged) {
    char original[] = "hello";
    char *result = (char *)s21_to_upper(original);

    ck_assert_ptr_nonnull(result);
    ck_assert_pstr_eq(original, "hello");   // оригинал не тронут
    ck_assert_pstr_eq(result, "HELLO");

    free(result);
    printf("[PASS] original string is not modified\n");
}
END_TEST

Suite *to_upper_suite_create(void) {
    Suite *s = suite_create("to_upper");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_to_upper_basic);
    tcase_add_test(tc, test_to_upper_edge);
    tcase_add_test(tc, test_to_upper_whitespace);
    tcase_add_test(tc, test_to_upper_long);
    tcase_add_test(tc, test_to_upper_null);
    tcase_add_test(tc, test_to_upper_original_unchanged);

    suite_add_tcase(s, tc);
    return s;
}
