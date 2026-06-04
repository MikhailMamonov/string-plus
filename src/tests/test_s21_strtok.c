#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"
#include "s21_test_common.h"

#define MAX_TEST_STR_LEN 1024

// Публичная функция запуска теста
void run_strtok_test(strtokParams *params) {
  char str_orig[MAX_TEST_STR_LEN];
  char str_test[MAX_TEST_STR_LEN];
  strcpy(str_orig, params->str);
  strcpy(str_test, params->str);

  char *expected = strtok(str_orig, params->delim);
  char *result = s21_strtok(str_test, params->delim);

  while (1) {
    if (expected == s21_NULL) {
      ck_assert_ptr_eq(result, s21_NULL);
      break;
    }
    ck_assert_ptr_ne(result, s21_NULL);
    ck_assert_str_eq(result, expected);

    expected = strtok(s21_NULL, params->delim);
    result = s21_strtok(s21_NULL, params->delim);
  }

  ck_assert_ptr_eq(expected, s21_NULL);
  ck_assert_ptr_eq(result, s21_NULL);
}

STRTOK_TEST_CASES(strtok_string_basic_tests,
                  {"a,b,c", ",", "test basic tokenization."},
                  {"Hello.", ",", "test basic token not found."},
                  {"a,b;c:d", ";,:", "multiple delimiters."},
                  {"a,,b,,,c", ",", "consecutive delimiters"},
                  {",,,a,b,c", ",", "delimiters at start"},
                  {"a,b,c,,,", ",", "test delimiters at end"},
                  {"", ",", "empty string"},
                  {",,;:,,;", ",", " Only delimiters"},
                  {",,,,,,;", ",", " Only delimiters"}

)

START_TEST(test_strtok_modification_string) {
  char str[] = "hello,world,c11";
  char original_copy[MAX_TEST_STR_LEN];
  strcpy(original_copy, str);

  strtok(str, ",");

  ck_assert_msg(str[5] == '\0',
                "Character mismatch: expected '%c' (0x%x), got '%c' (0x%x)",
                '\0', '\0', str[5], str[5]);
  ck_assert_str_eq(str, "hello");
}
END_TEST

STRTOK_TEST_CASES(strtok_edge_tests, {"Hello", "", "empty delimiter."},
                  {"привет,мир", ",", "unicode symbols."},
                  {"  abc  def", " ", "skip leader spaces."},
                  {"  abc  def", "", "Empty delimiter."})

// Функция, которую вызовет Runner
Suite *strtok_suite_create(void) {
  Suite *s = suite_create("strtok");

  TCase *tc_string = tcase_create("String tests");
  tcase_add_test(tc_string, test_strtok_string_basic_tests);
  suite_add_tcase(s, tc_string);

  TCase *tc_modification = tcase_create("String modification test");
  tcase_add_test(tc_modification, test_strtok_modification_string);
  suite_add_tcase(s, tc_modification);

  TCase *tc_edge = tcase_create("edge string tests");
  tcase_add_test(tc_edge, test_strtok_edge_tests);
  suite_add_tcase(s, tc_edge);
  return s;
}
