#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"
#include "s21_test_common.h"

static void run_insert_test(insertParams *params) {
  char *result =
      (char *)s21_insert(params->src, params->str, params->start_index);

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

// Базовые случаи: вставка в середину, начало, конец
INSERT_TEST_CASES(insert_basic,
                  {"Hello world", ", beautiful", 5, "Hello, beautiful world",
                   "insert into middle"},
                  {"world", "Hello, ", 0, "Hello, world", "insert at start"},
                  {"Hello", " world", 5, "Hello world",
                   "insert at end (index == len)"},
                  {"abc", "XYZ", 1, "aXYZbc", "insert after first char"},
                  {"abc", "XYZ", 2, "abXYZc", "insert before last char"})

// Вставка пустых строк
INSERT_TEST_CASES(insert_empty,
                  {"hello", "", 0, "hello", "empty insert at start"},
                  {"hello", "", 3, "hello", "empty insert in middle"},
                  {"hello", "", 5, "hello", "empty insert at end"},
                  {"", "hello", 0, "hello", "insert into empty src"},
                  {"", "", 0, "", "both empty"})

// Граничные индексы
INSERT_TEST_CASES(insert_boundary, {"abc", "X", 0, "Xabc", "index 0"},
                  {"abc", "X", 3, "abcX", "index == strlen"},
                  {"a", "BC", 0, "BCa",
                   "insert into single-char string at start"},
                  {"a", "BC", 1, "aBC",
                   "insert into single-char string at end"})

// Спецсимволы и пробелы
INSERT_TEST_CASES(insert_special_chars,
                  {"line1\nline2", "MID-", 6, "line1\nMID-line2",
                   "insert after newline"},
                  {"a\tb", "X", 2, "a\tXb", "insert after tab"},
                  {"Hello, World!", "C ", 7, "Hello, C World!",
                   "insert with punctuation"},
                  {"123", "456", 1,
                   "1456"
                   "23",
                   "insert digits"})

// Длинные строки
INSERT_TEST_CASES(insert_long,
                  {"The quick brown fox jumps over the lazy dog", " very ", 19,
                   "The quick brown fox very  jumps over the lazy dog",
                   "insert into long sentence"})

// Ошибочные случаи: NULL и невалидный индекс
INSERT_TEST_CASES(insert_errors,
                  {s21_NULL, "abc", 0, s21_NULL, "NULL src returns NULL"},
                  {"hello", s21_NULL, 0, s21_NULL, "NULL str returns NULL"},
                  {s21_NULL, s21_NULL, 0, s21_NULL, "both NULL returns NULL"},
                  {"hello", "X", 6, s21_NULL, "index > strlen returns NULL"},
                  {"hello", "X", 100, s21_NULL,
                   "index far beyond strlen returns NULL"},
                  {"", "X", 1, s21_NULL, "index 1 on empty src returns NULL"})

// ============================================================
//  Дополнительно: проверка, что src не изменяется
// ============================================================
START_TEST(test_insert_src_unchanged) {
  char src[] = "Hello world";
  char *result = (char *)s21_insert(src, "XXX", 5);

  ck_assert_ptr_nonnull(result);
  ck_assert_pstr_eq(src, "Hello world"); // оригинал не тронут
  ck_assert_pstr_eq(result, "HelloXXX world");

  free(result);
  printf("[PASS] src string is not modified\n");
}
END_TEST

Suite *insert_suite_create(void) {
  Suite *s = suite_create("insert");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_insert_basic);
  tcase_add_test(tc, test_insert_empty);
  tcase_add_test(tc, test_insert_boundary);
  tcase_add_test(tc, test_insert_special_chars);
  tcase_add_test(tc, test_insert_long);
  tcase_add_test(tc, test_insert_errors);
  tcase_add_test(tc, test_insert_src_unchanged);

  suite_add_tcase(s, tc);
  return s;
}
