#include "../s21_string.h"
#include "s21_test_common.h"
#include <check.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEST_STR_LEN 1024

void run_sprintf_test(sprintfParams *params) {

  char str_orig[MAX_TEST_STR_LEN];
  char str_test[MAX_TEST_STR_LEN];
  strcpy(str_orig, params->str);
  strcpy(str_test, params->str);

  char *expected = sprintf(str_orig, params->delim);
  char *result = s21_sprintf(str_test, params->delim);

  while (1) {
    if (expected == NULL) {
      ck_assert_ptr_eq(result, NULL);
      break;
    }
    ck_assert_ptr_ne(result, NULL);
    ck_assert_str_eq(result, expected);

    expected = sprintf(NULL, params->delim);
    result = s21_sprintf(NULL, params->delim);
  }

  ck_assert_ptr_eq(expected, NULL);
  ck_assert_ptr_eq(result, NULL);
}

SPRINTF_TEST_CASES(sprintf_string_basic_tests,
                   {"", "Hello", "test basic without specification."},
                   {"", "Hello%%", "test basic with screening in end."},
                   {"", "%%Hello", "test basic with screening in start."}

)

SPRINTF_TEST_CASES(sprintf_integer_specifier_tests,
                   {"", "integer input equals %d",
                    "test basic with positive integer specifier."},
                   {"", "integer input equals %d",
                    "test basic with negative integer specifier."},
                   {"", "integer input converted short  %hd",
                    "test basic with converting to short."},
                   {"", "integer input converted short  %lld",
                    "test basic with converting to long long."},
                   {"", "integer input converted short  %hhd",
                    "test basic with convertting to signed char."}

)

SPRINTF_TEST_CASES(sprintf_edge_tests, {"Hello", "", "empty delimiter."},
                   {"привет,мир", ",", "unicode symbols."},
                   {"  abc  def", " ", "skip leader spaces."},
                   {"  abc  def", "", "Empty delimiter."})

// Функция, которую вызовет Runner
Suite *sprintf_suite_create(void) {
  Suite *s = suite_create("sprintf");

  TCase *tc_string = tcase_create("String tests");
  tcase_add_test(tc_string, test_sprintf_string_basic_tests);
  suite_add_tcase(s, tc_string);

  TCase *tc_modification = tcase_create("String modification test");
  tcase_add_test(tc_modification, test_sprintf_modification_string);
  suite_add_tcase(s, tc_modification);

  TCase *tc_edge = tcase_create("edge string tests");
  tcase_add_test(tc_edge, test_sprintf_edge_tests);
  suite_add_tcase(s, tc_edge);
  return s;
}
