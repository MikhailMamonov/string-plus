#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "s21_test_common.h"

#define BUF_SIZE 256

static void run_strncpy_test(const strncpyParams *p) {
  char buf_std[BUF_SIZE];
  char buf_s21[BUF_SIZE];

  memset(buf_std, '#', BUF_SIZE);
  memset(buf_s21, '#', BUF_SIZE);

  char *ret_std = strncpy(buf_std, p->src, p->n);
  char *ret_s21 = s21_strncpy(buf_s21, p->src, p->n);

  ck_assert_msg(ret_std == buf_std, "FAIL [%s]: strncpy вернул не buf_std",
                p->test_name);
  ck_assert_msg(ret_s21 == buf_s21, "FAIL [%s]: s21_strncpy вернул не buf_s21",
                p->test_name);

  ck_assert_msg(s21_memcmp(buf_std, buf_s21, p->n) == 0,
                "FAIL [%s]: первые %zu байт отличаются", p->test_name,
                (size_t)p->n);

  for (s21_size_t i = p->n; i < BUF_SIZE; i++) {
    ck_assert_msg(buf_std[i] == '#' && buf_s21[i] == '#',
                  "FAIL [%s]: вышли за пределы n=%zu (i=%zu)", p->test_name,
                  (size_t)p->n, (size_t)i);
  }
}

STRNCPY_TEST_CASES(strncpy_basic, {"Hello, World!", 13, "basic_full"},
                   {"abc", 3, "abc_full"}, {"School21", 8, "school21_full"},
                   {"x", 1, "one_char"})

STRNCPY_TEST_CASES(strncpy_partial, {"Hello, World!", 5, "only_first_5"},
                   {"abcdef", 3, "only_abc"}, {"1234567890", 4, "only_1234"},
                   {"abcdef", 1, "only_a"})

STRNCPY_TEST_CASES(strncpy_n_greater_than_src, {"Hello", 20, "n_bigger_hello"},
                   {"abc", 10, "n_bigger_abc"}, {"x", 5, "n_bigger_one"},
                   {"42", 8, "n_bigger_42"})

STRNCPY_TEST_CASES(strncpy_n_equal_src, {"Hello", 5, "n_eq_hello"},
                   {"abc", 3, "n_eq_abc"}, {"a", 1, "n_eq_one"})

STRNCPY_TEST_CASES(strncpy_n_zero, {"Hello", 0, "n_zero_normal"},
                   {"", 0, "n_zero_empty_src"}, {"abc", 0, "n_zero_abc"})

STRNCPY_TEST_CASES(strncpy_empty_src, {"", 0, "empty_src_n0"},
                   {"", 1, "empty_src_n1"}, {"", 5, "empty_src_n5"},
                   {"", 50, "empty_src_n50"})

STRNCPY_TEST_CASES(strncpy_special_chars, {"line\n", 5, "newline"},
                   {"tab\t", 4, "tab_char"}, {"path/x", 6, "with_slash"},
                   {"\"hi\"", 4, "quotes"})

STRNCPY_TEST_CASES(strncpy_long_strings,
                   {"The quick brown fox jumps over the lazy dog", 43,
                    "long_full"},
                   {"The quick brown fox jumps over the lazy dog", 9,
                    "long_partial"},
                   {"aaaaaaaaaaaaaaaaaaaa", 20, "twenty_a"},
                   {"aaaaaaaaaaaaaaaaaaaa", 50, "a_with_padding"})

/* === Сборка suite === */

Suite *strncpy_suite_create(void) {
  Suite *s = suite_create("strncpy");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncpy_basic);
  tcase_add_test(tc, test_strncpy_partial);
  tcase_add_test(tc, test_strncpy_n_greater_than_src);
  tcase_add_test(tc, test_strncpy_n_equal_src);
  tcase_add_test(tc, test_strncpy_n_zero);
  tcase_add_test(tc, test_strncpy_empty_src);
  tcase_add_test(tc, test_strncpy_special_chars);
  tcase_add_test(tc, test_strncpy_long_strings);

  suite_add_tcase(s, tc);
  return s;
}
