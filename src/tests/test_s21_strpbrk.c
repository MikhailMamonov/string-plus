#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"
#include "s21_test_common.h"

void run_strpbrk_test(strpbrkParams *params) {
  char *expected = strpbrk(params->str1, params->str2);
  char *result = s21_strpbrk(params->str1, params->str2);

  ck_assert_ptr_eq(result, expected);
}

STRPBRK_TEST_CASES(
    strpbrk_string_tests, {"Hello world", "world", "Find in middle."},
    {"Hello, world.", "as", "Find all."},
    {"Hello, world.", "Hi", "Find first."},
    {"Hello, world.", "\t\n\r", "Find whitespace."},
    {"", "cfgchgfc", "Find in with null terminator"},
    {"cfgchgfc", "", "Find by null terminator"},
    {"abc123def", "0123456789", "Different symbols."},
    {"user@domain.com", "@", "Find special symbols."},
    {"HelloWorld", "w", "Different Cases."},
    {"helloWORLD", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "Find Upper Cases."},
    {"HELLOworld", "abcdefghijklmnopqrstuvwxyz", "Find Lower Cases."},
    {"aaaaaaaaab", "b", "repeated symbols."},
    {"abcdef", "eeefff", "find by repeated symbols."},
    {"Hello\x00World", "W", "Find with control chars"})

START_TEST(test_strpbrk_long_string) {
  // Длинная строка
  char str1[1000];
  memset(str1, 'a', 999);
  str1[999] = '\0';
  char str2[] = "b";
  char *result = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

STRPBRK_TEST_CASES(strpbrk_edge_tests, {"", "abc", "empty str1 string."},
                   {"Hello, ", "", "empty str2 string."},
                   {"", "", "Both empty."},
                   {"Hello, world.", "abc", "No match."},
                   {"", "cfgchgfc", "Find in with null terminator"},
                   {"Hello\nWorld", "\n", "Special symbol."})

// Функция, которую вызовет Runner
Suite *strpbrk_suite_create(void) {
  Suite *s = suite_create("strpbrk");

  TCase *tc_string = tcase_create("String tests");
  tcase_add_test(tc_string, test_strpbrk_string_tests);
  suite_add_tcase(s, tc_string);

  TCase *tc_edge = tcase_create("edge string tests");
  tcase_add_test(tc_edge, test_strpbrk_long_string);
  tcase_add_test(tc_edge, test_strpbrk_edge_tests);
  suite_add_tcase(s, tc_edge);
  return s;
}
