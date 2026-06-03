#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "s21_test_common.h"

#define BUF_SIZE 256

static void run_strncat_test(const strncatParams *p) {
  char buf_std[BUF_SIZE];
  char buf_s21[BUF_SIZE];

  /* Заполним буферы маркером, чтобы потом сравнить «хвост» —
   *      убедимся, что ни одна реализация не вышла за пределы. */
  s21_memset(buf_std, '#', BUF_SIZE);
  s21_memset(buf_s21, '#', BUF_SIZE);

  /* Начальное содержимое dest (с завершающим нулём) */
  strcpy(buf_std, p->dest_init);
  strcpy(buf_s21, p->dest_init);

  char *ret_std = strncat(buf_std, p->src, p->n);
  char *ret_s21 = s21_strncat(buf_s21, p->src, p->n);

  /* Возвращаемое значение должно совпадать с переданным dest */
  ck_assert_msg(ret_std == buf_std, "FAIL [%s]: strncat вернул не buf_std",
                p->test_name);
  ck_assert_msg(ret_s21 == buf_s21, "FAIL [%s]: s21_strncat вернул не buf_s21",
                p->test_name);

  /* Содержимое результирующих строк должно совпадать */
  ck_assert_msg(strcmp(buf_std, buf_s21) == 0,
                "FAIL [%s]: std=\"%s\", s21=\"%s\"", p->test_name, buf_std,
                buf_s21);

  /* Длины тоже должны совпадать */
  ck_assert_msg(s21_strlen(buf_std) == s21_strlen(buf_s21),
                "FAIL [%s]: len std=%zu, len s21=%zu", p->test_name,
                (size_t)s21_strlen(buf_std), (size_t)s21_strlen(buf_s21));
}

/* === Наборы тестов === */

STRNCAT_TEST_CASES(strncat_basic, {"Hello, ", "World!", 6, "basic_full"},
                   {"foo", "bar", 3, "foo_bar"}, {"abc", "def", 3, "abc_def"},
                   {"School", "21", 2, "school_21"})

STRNCAT_TEST_CASES(strncat_partial, {"Hello, ", "World!", 3, "only_first_3"},
                   {"abc", "defghi", 2, "only_de"},
                   {"start_", "1234567", 4, "only_1234"},
                   {"x", "yyyyy", 1, "only_one_y"})

STRNCAT_TEST_CASES(strncat_n_greater_than_src,
                   {"Hello, ", "World!", 100, "n_bigger_than_src"},
                   {"abc", "d", 50, "n_bigger_one_char"},
                   {"42", "School", 20, "n_bigger_school"})

STRNCAT_TEST_CASES(strncat_n_zero, {"Hello", "World", 0, "n_zero_normal"},
                   {"", "abc", 0, "n_zero_empty_dest"},
                   {"abc", "", 0, "n_zero_empty_src"})

STRNCAT_TEST_CASES(strncat_empty_strings, {"", "World", 5, "empty_dest"},
                   {"Hello", "", 5, "empty_src"}, {"", "", 5, "both_empty"},
                   {"", "abc", 2, "empty_dest_partial"})

STRNCAT_TEST_CASES(strncat_special_chars, {"line1\n", "line2\n", 6, "newlines"},
                   {"tab\t", "end", 3, "tab_char"},
                   {"path/", "file.txt", 8, "path_with_slash"},
                   {"\"hi\"", " there", 6, "quotes"})

STRNCAT_TEST_CASES(strncat_long_strings,
                   {"The quick brown fox ", "jumps over the lazy dog", 23,
                    "long_full"},
                   {"The quick brown fox ", "jumps over the lazy dog", 5,
                    "long_partial"},
                   {"aaaaaaaaaa", "bbbbbbbbbb", 10, "ten_a_ten_b"})

/* === Сборка suite === */

Suite *strncat_suite_create(void) {
  Suite *s = suite_create("s21_strncat");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncat_basic);
  tcase_add_test(tc, test_strncat_partial);
  tcase_add_test(tc, test_strncat_n_greater_than_src);
  tcase_add_test(tc, test_strncat_n_zero);
  tcase_add_test(tc, test_strncat_empty_strings);
  tcase_add_test(tc, test_strncat_special_chars);
  tcase_add_test(tc, test_strncat_long_strings);

  suite_add_tcase(s, tc);
  return s;
}
