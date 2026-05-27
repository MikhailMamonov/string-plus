#include "../s21_string.h"
#include "s21_test_common.h"
#include <check.h>
#include <stdlib.h>
#include <string.h>

// Вспомогательная функция проверки (сравниваем возвращаемые указатели)
void run_strrchr_test(strrchrParams *params) {
  char *orig_res = strrchr(params->str, params->c);
  char *s21_res = s21_strrchr(params->str, params->c);

  // Проверяем, что оба указателя смотрят на один и тот же адрес памяти
  ck_assert_ptr_eq(s21_res, orig_res);
}

// 1. Стандартный поиск символов
STRRCHR_TEST_CASES(
    standard_tests, {"hello", 'e'}, // Одиночный символ в середине
    {"hello", 'l'}, // Повторяющийся символ (должен найти ПОСЛЕДНИЙ)
    {"hello", 'h'}, // Символ в самом начале
    {"hello", 'o'}, // Символ в самом конце перед \0
    {"hello", 'z'}, // Символ отсутствует (должен вернуть NULL)
    {"AbAaB", 'A'} // Проверка регистра (последняя 'A' на индексе 2)
)

// 2. Особые случаи: поиск терминального нуля
STRRCHR_TEST_CASES(
    zero_tests, {"hello", '\0'}, // Поиск \0 в обычной строке
    {"", '\0'},                  // Поиск \0 в пустой строке
    {"a\0b\0c",
     '\0'}, // Поиск \0 в строке с внутренними нулями (должен найти ПЕРВЫЙ \0)
    {"hello", 0} // Передача нуля как int напрямую
)

// 3. Крайние случаи и расширенный ASCII
STRRCHR_TEST_CASES(
    edge_tests,
    {"", 'a'}, // Поиск символа в пустой строке (должен вернуть NULL)
    {"\x80\x90\x80",
     0x80}, // Расширенный ASCII (проверка корректности unsigned char)
    {"hello",
     256 + 'e'}, // Символ за пределами char (256 + 'e' приводится к 'e')
    {"hello", -1} // Отрицательное значение int
)

// Функция создания Suite для Runner
Suite *strrchr_suite_create(void) {
  Suite *s = suite_create("strrchr");

  TCase *tc_standard = tcase_create("Standard Tests");
  tcase_add_test(tc_standard, test_standard_tests);
  suite_add_tcase(s, tc_standard);

  TCase *tc_zero = tcase_create("Zero Tests");
  tcase_add_test(tc_zero, test_zero_tests);
  suite_add_tcase(s, tc_zero);

  TCase *tc_edge = tcase_create("Edge Tests");
  tcase_add_test(tc_edge, test_edge_tests);
  suite_add_tcase(s, tc_edge);

  return s;
}
