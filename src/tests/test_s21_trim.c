#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"
#include "s21_test_common.h"

static void run_trim_test(trimParams *params) {
  char *result = (char *)s21_trim(params->src, params->trim_chars);

  if (params->expected == s21_NULL) {
    ck_assert_ptr_null(result);
  } else {
    ck_assert_ptr_nonnull(result);
    ck_assert_pstr_eq(result, params->expected);
    ck_assert_ptr_ne((void *)result, (void *)params->src);
    free(result);
  }

  printf("[PASS] %s\n", params->test_name);
}

TRIM_TEST_CASES(trim_basic,
                {"   hello   ", " ", "hello", "trim spaces both sides"},
                {"***важно***", "*", "важно", "trim stars both sides"},
                {"  ##hello##  ", " #", "hello", "trim multiple chars"},
                {"abcXYZabc", "abc", "XYZ", "trim_chars is set, not substring"},
                {"abcXYZabc", "cba", "XYZ", "set order does not matter"})

TRIM_TEST_CASES(trim_middle, {"a b a", "a", " b ", "middle 'a' kept"},
                {"  hello   world  ", " ", "hello   world",
                 "inner spaces kept"},
                {"##a#b#c##", "#", "a#b#c", "inner hashes kept"})

TRIM_TEST_CASES(trim_asymmetric, {"xxxhello", "x", "hello", "trim only left"},
                {"helloxxx", "x", "hello", "trim only right"},
                {"hello", "xyz", "hello", "nothing to trim"},
                {"   hello", " ", "hello", "leading spaces only"},
                {"hello   ", " ", "hello", "trailing spaces only"})

TRIM_TEST_CASES(trim_edges, {"", "abc", "", "empty src"},
                {"hello", "", "hello", "empty trim_chars (nothing to trim)"},
                {"", "", "", "both empty"},
                {"aaaa", "a", "", "all chars are trim chars"},
                {"ababab", "ab", "", "all chars in mixed set"},
                {"xxxAxxx", "x", "A", "single char remains in middle"},
                {"A", "x", "A", "single char src kept"},
                {"x", "x", "", "single char src removed"})

TRIM_TEST_CASES(trim_special_chars,
                {"\t\n  hello  \n\t", " \t\n", "hello", "tabs and newlines"},
                {"12345text54321", "0123456789", "text", "trim digits"},
                {"...!!!hello!!!...", ".!", "hello", "trim punctuation"},
                {"-=-=value=-=-", "-=", "value", "trim dashes and equals"})

TRIM_TEST_CASES(trim_empty,
                {"Hello, World!", "", "Hello, World!", "trim without symbols"},
                {"", "a", "", "empty src"}, {"", "", "", "empty src and trim"})

TRIM_TEST_CASES(trim_null, {"hello", "\0", "hello", "trim with NULL"},
                {"\0", "abc", "\0", "src is null"},
                {"\0", "\0", "\0", "trim and src are null"})

TRIM_TEST_CASES(
    trim_long,
    {"          The quick brown fox jumps over the lazy dog          ", " ",
     "The quick brown fox jumps over the lazy dog",
     "trim long sentence with many spaces"})

TRIM_TEST_CASES(trim_errors, {s21_NULL, " ", s21_NULL, "NULL src returns NULL"},
                {"hello", s21_NULL, s21_NULL, "NULL trim_chars returns NULL"},
                {s21_NULL, s21_NULL, s21_NULL, "both NULL returns NULL"})

START_TEST(test_trim_src_unchanged) {
  char src[] = "  Hello world  ";
  char *result = (char *)s21_trim(src, " ");

  ck_assert_ptr_nonnull(result);
  ck_assert_pstr_eq(src, "  Hello world  ");
  ck_assert_pstr_eq(result, "Hello world");

  free(result);
  printf("[PASS] src string is not modified\n");
}
END_TEST

Suite *trim_suite_create(void) {
  Suite *s = suite_create("trim");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_trim_basic);
  tcase_add_test(tc, test_trim_middle);
  tcase_add_test(tc, test_trim_asymmetric);
  tcase_add_test(tc, test_trim_edges);
  tcase_add_test(tc, test_trim_special_chars);
  tcase_add_test(tc, test_trim_null);
  tcase_add_test(tc, test_trim_long);
  tcase_add_test(tc, test_trim_empty);
  tcase_add_test(tc, test_trim_errors);
  tcase_add_test(tc, test_trim_src_unchanged);

  suite_add_tcase(s, tc);
  return s;
}
