#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "s21_test_common.h"

static void run_strstr_test(const strstrParams *p) {
  char *res_std = strstr(p->haystack, p->needle);
  char *res_s21 = s21_strstr(p->haystack, p->needle);

  ck_assert_msg(
      res_std == res_s21,
      "FAIL [%s]: strstr=%p, s21_strstr=%p (haystack=\"%s\", needle=\"%s\")",
      p->test_name, (void *)res_std, (void *)res_s21, p->haystack, p->needle);
}

STRSTR_TEST_CASES(strstr_basic_found, {"Hello, World!", "World", "find_world"},
                  {"Hello, World!", "Hello", "find_at_start"},
                  {"Hello, World!", "!", "find_last_char"},
                  {"abcdef", "cd", "find_middle"},
                  {"School21", "21", "find_digits"})

STRSTR_TEST_CASES(strstr_not_found,
                  {"Hello, World!", "world", "case_sensitive"},
                  {"abcdef", "xyz", "totally_absent"},
                  {"abc", "abcd", "needle_longer"},
                  {"School21", "22", "wrong_digits"},
                  {"Hello", "Hella", "almost_match"})

STRSTR_TEST_CASES(strstr_empty_needle, {"Hello", "", "empty_needle_normal"},
                  {"", "", "both_empty"}, {"abc", "", "empty_needle_abc"})

STRSTR_TEST_CASES(strstr_empty_haystack, {"", "a", "empty_haystack_one_char"},
                  {"", "abc", "empty_haystack_word"})

STRSTR_TEST_CASES(strstr_full_match, {"abc", "abc", "exact_match_short"},
                  {"Hello", "Hello", "exact_match_word"},
                  {"x", "x", "exact_match_one_char"})

STRSTR_TEST_CASES(strstr_multiple_occurrences,
                  {"ababab", "ab", "first_of_three"},
                  {"aaaa", "aa", "overlapping"}, {"banana", "na", "first_na"},
                  {"abc abc abc", "abc", "first_abc"})

STRSTR_TEST_CASES(strstr_special_chars, {"line1\nline2", "\n", "find_newline"},
                  {"tab\there", "\t", "find_tab"},
                  {"path/to/file", "/to/", "find_with_slashes"},
                  {"\"quoted\"", "quoted", "find_in_quotes"},
                  {"!@#$%^&*()", "#$", "find_punct"})

STRSTR_TEST_CASES(strstr_partial_prefix,
                  {"abcdef", "abcx", "wrong_after_prefix"},
                  {"abcabd", "abcd", "almost_full"},
                  {"aaab", "aab", "shifted_match"})

STRSTR_TEST_CASES(
    strstr_long_strings,
    {"The quick brown fox jumps over the lazy dog", "brown fox", "long_middle"},
    {"The quick brown fox jumps over the lazy dog", "lazy dog", "long_end"},
    {"The quick brown fox jumps over the lazy dog", "The quick", "long_start"},
    {"aaaaaaaaaaaaaaaaaaab", "aaab", "tail_in_long"})

Suite *strstr_suite_create(void) {
  Suite *s = suite_create("strstr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strstr_basic_found);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_empty_needle);
  tcase_add_test(tc, test_strstr_empty_haystack);
  tcase_add_test(tc, test_strstr_full_match);
  tcase_add_test(tc, test_strstr_multiple_occurrences);
  tcase_add_test(tc, test_strstr_special_chars);
  tcase_add_test(tc, test_strstr_partial_prefix);
  tcase_add_test(tc, test_strstr_long_strings);

  suite_add_tcase(s, tc);
  return s;
}
