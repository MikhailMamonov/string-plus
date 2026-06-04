#include "../s21_string.h"
#include "s21_test_common.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

static void run_to_lower_test(toLowerParams *params) {
  char *result = (char *)s21_to_lower(params->str);

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
TO_LOWER_TEST_CASES(to_lower_basic, {"HELLO", "hello", "all upperrcase"},
                    {"hello", "hello", "already lowercase"},
                    {"HeLLo WoRLd", "hello world", "mixed case"},
                    {"Hello, World! 123", "hello, world! 123",
                     "letters + punct + digits"},
                    {"1234567890", "1234567890", "only digits"},
                    {"!@#$%^&*()", "!@#$%^&*()", "only symbols"})

// Граничные случаи
TO_LOWER_TEST_CASES(to_lower_edge, {"", "", "empty string"},
                    {"A", "a", "single uppercase letter"},
                    {"a", "a", "single lowerrcase letter"},
                    {"?", "?", "single non-letter"},
                    {"AZ", "az", "boundary letters a and z"},
                    {"`{|}", "`{|}", "ASCII neighbors of letters"})

// Пробельные символы
TO_LOWER_TEST_CASES(to_lower_whitespace,
                    {"  HELLO\tWORLD\n", "  hello\tworld\n",
                     "spaces, tab, newline"},
                    {"     ", "     ", "only spaces"},
                    {"\t\n\r", "\t\n\r", "only control whitespace"})

// Длинная строка
TO_LOWER_TEST_CASES(
    to_lower_long,
    {"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG 1234567890 TIMES",
     "the quick brown fox jumps over the lazy dog 1234567890 times",
     "long pangram"})

// NULL на входе — ожидаем NULL на выходе
TO_LOWER_TEST_CASES(to_lower_null,
                    {s21_NULL, s21_NULL, "NULL input returns NULL"})

START_TEST(test_to_lower_original_unchanged) {
  char original[] = "HELLO";
  char *result = (char *)s21_to_lower(original);

  ck_assert_ptr_nonnull(result);
  ck_assert_pstr_eq(original, "HELLO");
  ck_assert_pstr_eq(result, "hello");

  free(result);
  printf("[PASS] original string is not modified\n");
}
END_TEST

Suite *to_lower_suite_create(void) {
  Suite *s = suite_create("to_lower");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_to_lower_basic);
  tcase_add_test(tc, test_to_lower_edge);
  tcase_add_test(tc, test_to_lower_whitespace);
  tcase_add_test(tc, test_to_lower_long);
  tcase_add_test(tc, test_to_lower_null);
  tcase_add_test(tc, test_to_lower_original_unchanged);

  suite_add_tcase(s, tc);
  return s;
}
