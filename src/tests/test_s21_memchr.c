#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"
#include "s21_test_common.h"

// Универсальная функция запуска одиночного теста
void run_memchr_test(memchrParams *params) {
  char *res = s21_memchr(params->str, params->c, params->n);
  char *expected = memchr(params->str, params->c, params->n);

  // Сравниваем точные адреса указателей в памяти
  ck_assert_ptr_eq(res, expected);
}

// 1. Положительные тесты (символ гарантированно есть в области видимости n)
MEMCHR_TEST_CASES(positive_tests, {"apple", 'p', 3}, {"verter", 'r', 6},
                  {"aaa", 'a', 3},
                  {"supercalifragilisticexpialidocious", 'u', 35},
                  {"Several words and 221 122 32", ' ', 14})

// 2. Отрицательные тесты (символ отсутствует или находится за пределами n)
MEMCHR_TEST_CASES(negative_tests, {"apple", 'p', 1}, {"verter", 'a', 6},
                  {"a", 'l', 1}, {"supercalifragilisticexpialidocious", 'c', 4},
                  {"Several words and 221 122 32", ' ', 7},
                  {"Spare test", '\0', 5})

// 3. Пограничные и экстремальные случаи
MEMCHR_TEST_CASES(edge_tests, {"", '\0', 1}, {"", '\n', 0}, {"a", '\0', 1},
                  {"supercalifragilisticexpialidocious/", '/', 35},
                  {"Spare test", '\0', 11})

// Функция сборки Suite для Runner
Suite *memchr_suite_create(void) {
  Suite *s = suite_create("Memchr");

  TCase *tc_pos = tcase_create("Positive_Original_Compare");
  tcase_add_test(tc_pos, test_positive_tests);
  suite_add_tcase(s, tc_pos);

  TCase *tc_neg = tcase_create("Negative_Original_Compare");
  tcase_add_test(tc_neg, test_negative_tests);
  suite_add_tcase(s, tc_neg);

  TCase *tc_edge = tcase_create("Edge_Original_Compare");
  tcase_add_test(tc_edge, test_edge_tests);
  suite_add_tcase(s, tc_edge);

  return s;
}
