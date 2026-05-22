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

// Test char symbols
RUN_SPRINTF_TEST(char_basic, "A", "%c", 'A');
RUN_SPRINTF_TEST(char_digit, "5", "%c", '5');
RUN_SPRINTF_TEST(char_width, "|         A|", "|%10c|", 'A');
RUN_SPRINTF_TEST(char_width_left_align, "|A         |", "|%-10c|", 'A');
RUN_SPRINTF_TEST(char_width_left_null_string, "|          |", "|%-10c|", '\0');
RUN_SPRINTF_TEST(char_special, "\n", "%c", '\n');
RUN_SPRINTF_TEST(char_null, "", "%c", '\0');

// Test strings with precision
// RUN_SPRINTF_TEST(string_precision, "Hell", "%.4s", "Hello");
// RUN_SPRINTF_TEST(string_precision_more, "Hello", "%.10s", "Hello");
// RUN_SPRINTF_TEST(string_precision_zero, "", "%.0s", "Hello");
// RUN_SPRINTF_TEST(string_precision_star, "Hell", "%.*s", 4, "Hello");

RUN_SPRINTF_TEST(int_positive, "42", "%d", 42);
RUN_SPRINTF_TEST(int_negative, "-123", "%d", -123);
RUN_SPRINTF_TEST(int_zero, "0", "%d", 0);
RUN_SPRINTF_TEST(int_two, "10 20", "%d %d", 10, 20);
RUN_SPRINTF_TEST(int_three, "10 + 20 = 30", "%d + %d = %d", 10, 20, 30);
RUN_SPRINTF_TEST(int_width, "|      42|", "|%8d|", 42);
RUN_SPRINTF_TEST(int_width_left_align, "|42      |", "|%-8d|", 42);
RUN_SPRINTF_TEST(int_negative_width, "|       -42|", "|%10d|", -42);
RUN_SPRINTF_TEST(int_negative_width_left_align, "|-42       |", "|%-10d|",
                 -42);

RUN_SPRINTF_TEST(short_int, "2342", "%hd", (short)2342);
RUN_SPRINTF_TEST(long_long, "45646546546465", "%lld", 45646546546465LL);
RUN_SPRINTF_TEST(signed_char, "-56", "%hhd", (signed char)-56)

RUN_SPRINTF_TEST(mixed_string_int, "answer 42", "%s %d", "answer", 42);
RUN_SPRINTF_TEST(mixed_int_string, "42 is answer", "%d %s %s", 42, "is",
                 "answer");

RUN_SPRINTF_TEST(zero_exponent, "0.000000e+00", "%e", 0.0);
RUN_SPRINTF_TEST(positive_number_exponent, "1.234560e+02", "%e", 123.456);
RUN_SPRINTF_TEST(negative_zero_exponent, "-0.000000e+00", "%e", -0.0);
RUN_SPRINTF_TEST(negative_number_exponent, "-1.234560e+02", "%e", -123.456);
RUN_SPRINTF_TEST(negative_exponent, "-1.230000e-03", "%e", -0.00123);
RUN_SPRINTF_TEST(capital_letter_exponent, "-1.230000E-03", "%E", -0.00123);
RUN_SPRINTF_TEST(round_exponent, "1.24e+03", "%.2e", 1239.56);
RUN_SPRINTF_TEST(infinity_exponent, "-inf", "%e", -INFINITY);
RUN_SPRINTF_TEST(nan_exponent, "NAN", "%E", NAN);
RUN_SPRINTF_TEST(
    mixed_str_int_exp,
    "The number 1000 can be presented as 1.000000E+03. Interesting!",
    "The number %d can be presented as %E. Interesting!", 1000, 1000.0);

RUN_SPRINTF_TEST(zero_float, "0.000000", "%f", 0.0);
RUN_SPRINTF_TEST(negative_zero_float, "-0.000000", "%f", -0.0);
RUN_SPRINTF_TEST(positive_number_float, "123.456000", "%f", 123.456);
RUN_SPRINTF_TEST(negative_number_float, "-123.456000", "%f", -123.456);
RUN_SPRINTF_TEST(precision_zero_float, "123", "%.0f", 123.456);
RUN_SPRINTF_TEST(precision_short_float, "123.46", "%.2f", 123.456);
RUN_SPRINTF_TEST(precision_long_float, "0.00123000", "%.8f", 0.00123);
RUN_SPRINTF_TEST(round_down_float, "1.23", "%.2f", 1.234);
RUN_SPRINTF_TEST(round_up_float, "1.24", "%.2f", 1.236);
RUN_SPRINTF_TEST(round_carry_to_int_float, "10.00", "%.2f", 9.999); // Перенос разряда в целую часть
RUN_SPRINTF_TEST(flag_plus_positive_float, "+1.230000", "%+f", 1.23);
RUN_SPRINTF_TEST(flag_plus_negative_float, "-1.230000", "%+f", -1.23);
RUN_SPRINTF_TEST(flag_space_positive_float, " 1.230000", "% f", 1.23);
RUN_SPRINTF_TEST(flag_space_negative_float, "-1.230000", "% f", -1.23);
RUN_SPRINTF_TEST(infinity_lowercase_float, "inf", "%f", INFINITY);
RUN_SPRINTF_TEST(nan_lowercase_float, "nan", "%f", NAN);
RUN_SPRINTF_TEST(nan_with_plus_flag_float, "+nan", "%+f", NAN);
RUN_SPRINTF_TEST(very_small_float, "0.000000", "%f", 1e-10); // Округляется до 0 при дефолтной точности 6
RUN_SPRINTF_TEST(large_number_float, "1000000000.000000", "%f", 1000000000.0);
RUN_SPRINTF_TEST(mixed_str_int_float, "Price: 49.99 USD (discounted from 50)", "Price: %.2f %s (discounted from %d)", 49.99, "USD", 50);

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
  tcase_add_test(tc_core, test_int_width);
  tcase_add_test(tc_core, test_int_width_left_align);
  tcase_add_test(tc_core, test_int_negative_width);
  tcase_add_test(tc_core, test_int_negative_width_left_align);

  tcase_add_test(tc_core, test_short_int);
  tcase_add_test(tc_core, test_long_long);
  tcase_add_test(tc_core, test_signed_char);

  tcase_add_test(tc_core, test_mixed_string_int);
  tcase_add_test(tc_core, test_mixed_int_string);

  tcase_add_test(tc_core, test_zero_exponent);
  tcase_add_test(tc_core, test_positive_number_exponent);
  tcase_add_test(tc_core, test_negative_zero_exponent);
  tcase_add_test(tc_core, test_negative_number_exponent);
  tcase_add_test(tc_core, test_negative_exponent);
  tcase_add_test(tc_core, test_capital_letter_exponent);
  tcase_add_test(tc_core, test_round_exponent);
  tcase_add_test(tc_core, test_infinity_exponent);
  tcase_add_test(tc_core, test_nan_exponent);
  tcase_add_test(tc_core, test_mixed_str_int_exp);

  tcase_add_test(tc_core, test_char_basic);
  tcase_add_test(tc_core, test_char_digit);
  tcase_add_test(tc_core, test_char_special);
  tcase_add_test(tc_core, test_char_null);
  tcase_add_test(tc_core, test_char_width);
  tcase_add_test(tc_core, test_char_width_left_align);
  tcase_add_test(tc_core, test_char_width_left_null_string);

  tcase_add_test(tc_core, test_zero_float);
  tcase_add_test(tc_core, test_negative_zero_float);
  tcase_add_test(tc_core, test_positive_number_float);
  tcase_add_test(tc_core, test_negative_number_float);
  tcase_add_test(tc_core, test_precision_zero_float);
  tcase_add_test(tc_core, test_precision_short_float);
  tcase_add_test(tc_core, test_precision_long_float);
  tcase_add_test(tc_core, test_round_down_float);
  tcase_add_test(tc_core, test_round_up_float);
  tcase_add_test(tc_core, test_round_carry_to_int_float);
  tcase_add_test(tc_core, test_flag_plus_positive_float);
  tcase_add_test(tc_core, test_flag_plus_negative_float);
  tcase_add_test(tc_core, test_flag_space_positive_float);
  tcase_add_test(tc_core, test_flag_space_negative_float);
  tcase_add_test(tc_core, test_infinity_lowercase_float);
  tcase_add_test(tc_core, test_nan_lowercase_float);
  tcase_add_test(tc_core, test_nan_with_plus_flag_float);
  tcase_add_test(tc_core, test_very_small_float);
  tcase_add_test(tc_core, test_large_number_float);
  tcase_add_test(tc_core, test_mixed_str_int_float);

  suite_add_tcase(s, tc_core);

  return s;
}
