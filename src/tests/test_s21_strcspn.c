#include "../s21_string.h"
#include "s21_test_common.h"
#include <check.h>
#include <stdlib.h>
#include <string.h>

// Публичная функция запуска теста
void run_strcspn_test(StrCSpnTestParams *params) {

  s21_size_t expected = strcspn(params->str1, params->str2);
  s21_size_t result = s21_strcspn(params->str1, params->str2);

  ck_assert_uint_eq(result, expected);
}

STRCSPN_TEST_CASES(strcspn_string_tests,
                   {"Hello world", "world", "Find in middle."},
                   {"Hello, world.", "as", "Find all."},
                   {"Hello, world.", "Hi", "Find first."},
                   {"Hello, world.", "\t\n\r", "Find whitespace."},
                   {"", "cfgchgfc", "Find in with null terminator"},
                   {"cfgchgfc", "", "Find by null terminator"},
                   {"abc123def", "0123456789", "Different symbols."},
                   {"user@domain.com", "@", "Find special symbols."},
                   {"HelloWorld", "w", "Different Cases."},
                   {"helloWORLD", "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                    "Find Upper Cases."},
                   {"aaaaaaaaab", "b", "repeated symbols."},
                   {"abcdef", "eeefff", "find by repeated symbols."},
                   {"Hello\x00World", "W", "Find with control chars"})

START_TEST(test_strcspn_long_string) {
  // Длинная строка
  char str1[1000];
  s21_memset(str1, 'a', 999);
  str1[999] = '\0';
  char str2[] = "b";
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t expected = strcspn(str1, str2);
  ck_assert_uint_eq(result, expected);
}
END_TEST

// Функция, которую вызовет Runner
Suite *strcspn_suite_create(void) {
  Suite *s = suite_create("strcspn");

  TCase *tc_string = tcase_create("String tests");
  tcase_add_test(tc_string, test_strcspn_string_tests);
  suite_add_tcase(s, tc_string);

  TCase *tc_boundary = tcase_create("boundary string tests");
  tcase_add_test(tc_boundary, test_strcspn_long_string);
  suite_add_tcase(s, tc_boundary);
  return s;
}
