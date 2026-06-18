#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "s21_test_common.h"

static void run_strlen_test(const strlenParams *p) {
  s21_size_t len_std = strlen(p->str);
  s21_size_t len_s21 = s21_strlen(p->str);

  ck_assert_msg(len_std == len_s21, "FAIL [%s]: s21_strlen=%zu, strlen=%zu",
                p->test_name, (s21_size_t)len_s21, (s21_size_t)len_std);

  ck_assert_msg(len_s21 == p->expected,
                "FAIL [%s]: s21_strlen=%zu, expected=%zu", p->test_name,
                (s21_size_t)len_s21, (s21_size_t)p->expected);
}

STRLEN_TEST_CASES(strlen_basic, {"Hello, World!", 13, "hello_world"},
                  {"abc", 3, "abc"}, {"School21", 8, "school21"},
                  {"x", 1, "one_char"})

STRLEN_TEST_CASES(strlen_empty, {"", 0, "empty_string"})

STRLEN_TEST_CASES(strlen_spaces, {" ", 1, "single_space"},
                  {"   ", 3, "three_spaces"}, {"a b c", 5, "with_spaces"},
                  {"  abc  ", 7, "padded_spaces"})

STRLEN_TEST_CASES(strlen_special_chars, {"line\n", 5, "newline"},
                  {"tab\there", 8, "tab_inside"},
                  {"path/to/x", 9, "with_slashes"}, {"\"quoted\"", 8, "quotes"},
                  {"!@#$%^&*()", 10, "punctuation"})

STRLEN_TEST_CASES(strlen_numbers, {"42", 2, "two_digits"},
                  {"1234567890", 10, "ten_digits"}, {"0", 1, "zero"})

STRLEN_TEST_CASES(strlen_long_strings,
                  {"The quick brown fox jumps over the lazy dog", 43,
                   "pangram"},
                  {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 50,
                   "fifty_a"},
                  {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                   "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                   100, "hundred_a"})

STRLEN_TEST_CASES(strlen_terminator_only_counts_before_null,
                  {"abc\0def", 3, "null_in_middle"},
                  {"\0abc", 0, "null_at_start"})

Suite *strlen_suite_create(void) {
  Suite *s = suite_create("strlen");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strlen_basic);
  tcase_add_test(tc, test_strlen_empty);
  tcase_add_test(tc, test_strlen_spaces);
  tcase_add_test(tc, test_strlen_special_chars);
  tcase_add_test(tc, test_strlen_numbers);
  tcase_add_test(tc, test_strlen_long_strings);
  tcase_add_test(tc, test_strlen_terminator_only_counts_before_null);

  suite_add_tcase(s, tc);
  return s;
}
