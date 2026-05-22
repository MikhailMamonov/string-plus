#include "../s21_string.h"
#include "s21_test_common.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RUN_SPRINTF_TEST(string_basic, "Hello", "%s", "Hello");
RUN_SPRINTF_TEST(string_with_space, "Hello World", "%s %s", "Hello", "World");
RUN_SPRINTF_TEST(string_empty, "", "%s", "");
RUN_SPRINTF_TEST(string_percent, "Hello%", "Hello%%");
RUN_SPRINTF_TEST(string_percent_start, "%Hello", "%%Hello");

RUN_SPRINTF_TEST(int_positive, "42", "%d", 42);
RUN_SPRINTF_TEST(int_negative, "-123", "%d", -123);
RUN_SPRINTF_TEST(int_zero, "0", "%d", 0);
RUN_SPRINTF_TEST(int_two, "10 20", "%d %d", 10, 20);
RUN_SPRINTF_TEST(int_three, "10 + 20 = 30", "%d + %d = %d", 10, 20, 30);

RUN_SPRINTF_TEST(short_int, "2342", "%hd", (short)2342);
RUN_SPRINTF_TEST(long_long, "45646546546465", "%lld", 45646546546465LL);
RUN_SPRINTF_TEST(signed_char, "-56", "%hhd", (signed char)-56)

RUN_SPRINTF_TEST(mixed_string_int, "answer 42", "%s %d", "answer", 42);
RUN_SPRINTF_TEST(mixed_int_string, "42 is answer", "%d %s %s", 42, "is",
                 "answer");

// Функция, которую вызовет Runner
Suite *sprintf_suite_create(void) {
  Suite *s = suite_create("sprintf");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_string_basic);
  tcase_add_test(tc_core, test_string_with_space);
  tcase_add_test(tc_core, test_string_empty);
  tcase_add_test(tc_core, test_string_percent);
  tcase_add_test(tc_core, test_string_percent_start);

  tcase_add_test(tc_core, test_int_positive);
  tcase_add_test(tc_core, test_int_negative);
  tcase_add_test(tc_core, test_int_zero);
  tcase_add_test(tc_core, test_int_two);
  tcase_add_test(tc_core, test_int_three);

  tcase_add_test(tc_core, test_short_int);
  tcase_add_test(tc_core, test_long_long);
  tcase_add_test(tc_core, test_signed_char);

  tcase_add_test(tc_core, test_mixed_string_int);
  tcase_add_test(tc_core, test_mixed_int_string);
  suite_add_tcase(s, tc_core);

  return s;
}
