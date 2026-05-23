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

// Тесты для обычных чисел, которые должны выводиться через %f (без экспоненты)
RUN_SPRINTF_TEST(g_zero, "0", "%g", 0.0);
RUN_SPRINTF_TEST(g_negative_zero, "-0", "%g", -0.0);
RUN_SPRINTF_TEST(g_simple_float, "123.456", "%g", 123.456);
RUN_SPRINTF_TEST(g_trailing_zeros_flat, "1.23", "%g", 1.230000);
RUN_SPRINTF_TEST(g_no_dot_needed, "125", "%g", 125.000000);

// Тесты для чисел, которые переключаются в экспоненциальную форму (%e)
RUN_SPRINTF_TEST(g_large_number, "1.23456e+06", "%g", 1234560.0);
RUN_SPRINTF_TEST(g_small_number, "1.23456e-05", "%g", 0.0000123456);
RUN_SPRINTF_TEST(g_capital_letter, "1.23456E+06", "%G", 1234560.0);

// Тесты со специфическим удалением нулей перед экспонентой
RUN_SPRINTF_TEST(g_exp_trailing_zeros, "1.2e+06", "%g", 1200000.0);
RUN_SPRINTF_TEST(g_exp_no_dot, "1E+06", "%G", 1000000.0);

// Тесты на явное указание точности (precision)
RUN_SPRINTF_TEST(g_precision_large, "12", "%.2g", 12.345);
RUN_SPRINTF_TEST(g_precision_round, "1.24", "%.3g", 1.23956);
RUN_SPRINTF_TEST(g_precision_zero, "1", "%.0g", 1.2345); // Точность 0 должна трактоваться как 1

// Специальные значения
RUN_SPRINTF_TEST(g_infinity, "-inf", "%g", -INFINITY);
RUN_SPRINTF_TEST(g_nan, "NAN", "%G", NAN);

// Смешанный тест в строке
RUN_SPRINTF_TEST(g_mixed_str, "Value: 0.000123 and 45.67", "Value: %g and %g", 0.000123, 45.67);

RUN_SPRINTF_TEST(g_hash_zero, "0.00000", "%#g", 0.0);
RUN_SPRINTF_TEST(g_hash_flat_zeros, "1.23000", "%#g", 1.23);
RUN_SPRINTF_TEST(g_hash_no_dot_originally, "125.000", "%#g", 125.0);
RUN_SPRINTF_TEST(g_hash_exp_zeros, "1.20000e+06", "%#g", 1200000.0);
RUN_SPRINTF_TEST(g_hash_exp_no_dot_originally, "1.00000E+06", "%#G", 1000000.0);
RUN_SPRINTF_TEST(g_hash_with_precision, "1.240", "%#.4g", 1.24);

// Тесты для %f с флагом #
RUN_SPRINTF_TEST(f_hash_zero_precision, "123.", "%#.0f", 123.0);
RUN_SPRINTF_TEST(f_hash_normal, "123.456000", "%#f", 123.456);     // обычный вывод с дефолтной точностью 6
RUN_SPRINTF_TEST(f_hash_zero_val, "0.", "%#.0f", 0.0);             // ноль с точностью 0 и точкой

// Тесты для %e и %E с флагом #
RUN_SPRINTF_TEST(e_hash_zero_precision, "1.e+02", "%#.0e", 123.0);  // точка перед экспонентой сохраняется при .0
RUN_SPRINTF_TEST(E_hash_zero_precision, "1.E+02", "%#.0E", 123.0);  // то же самое для заглавной E
RUN_SPRINTF_TEST(e_hash_normal, "1.234560e+02", "%#e", 123.456);   // стандартный вывод не ломается

// Базовые тесты %o
RUN_SPRINTF_TEST(o_simple, "12", "%o", 10);
RUN_SPRINTF_TEST(o_zero, "0", "%o", 0);
RUN_SPRINTF_TEST(o_large, "1750", "%o", 1000);

// Тесты с точностью (precision)
RUN_SPRINTF_TEST(o_precision_normal, "0012", "%.4o", 10);
RUN_SPRINTF_TEST(o_precision_smaller, "12", "%.1o", 10);
RUN_SPRINTF_TEST(o_zero_precision_zero_val, "", "%.0o", 0); // Пустая строка по стандарту

// Тесты с флагом # (alt_format)
RUN_SPRINTF_TEST(o_hash_normal, "012", "%#o", 10);
RUN_SPRINTF_TEST(o_hash_zero, "0", "%#o", 0); // Для нуля решетка не должна плодить лишний 0
RUN_SPRINTF_TEST(o_hash_and_precision, "0012", "%#.4o", 10); // Проверка конфликта нулей

// Тесты на беззнаковое приведение (отрицательные числа)
RUN_SPRINTF_TEST(o_negative, "37777777777", "%o", -1);

// Модификаторы длины (если они у тебя уже поддержаны в sprintf)
RUN_SPRINTF_TEST(o_length_h, "177777", "%ho", (unsigned short)-1);
RUN_SPRINTF_TEST(o_length_l, "1777777777777777777777", "%lo", (unsigned long)-1);
// Число в середине строки с текстом вокруг
RUN_SPRINTF_TEST(o_middle_of_str, "Permissions: 0755 is secure.", "Permissions: %#o is secure.", 493); 

// Тесты на ширину поля (width) и флаг '0'
RUN_SPRINTF_TEST(o_width_right_align, "   12", "%5o", 10);        // Дополнение пробелами слева
RUN_SPRINTF_TEST(o_width_zero_flag, "00012", "%05o", 10);        // Дополнение нулями с флагом 0
RUN_SPRINTF_TEST(o_hash_width_flags, "  012", "%#5o", 10);       // Совместная работа ширины и решетки

// Необычные беззнаковые границы (максимальное значение 32-битного unsigned int)
RUN_SPRINTF_TEST(o_uint_max, "37777777777", "%o", 4294967295U);
// Модификатор h (short int / signed char)
RUN_SPRINTF_TEST(d_length_h_normal, "12345", "%hd", (short)12345);
RUN_SPRINTF_TEST(i_length_h_neg, "-32768", "%hi", (short)-32768); // SHRT_MIN
RUN_SPRINTF_TEST(d_length_h_max, "32767", "%hd", (short)32767);   // SHRT_MAX

// Модификатор l (long int)
RUN_SPRINTF_TEST(d_length_l_normal, "1234567890", "%ld", 1234567890L);
#if __WORDSIZE == 64
RUN_SPRINTF_TEST(i_length_l_min, "-9223372036854775808", "%li", -9223372036854775807L - 1L); // LONG_MIN на 64-бит
RUN_SPRINTF_TEST(d_length_l_max, "9223372036854775807", "%ld", 9223372036854775807L);        // LONG_MAX на 64-бит
#else
RUN_SPRINTF_TEST(i_length_l_min, "-2147483648", "%li", -2147483647L - 1L); // LONG_MIN на 32-бит
RUN_SPRINTF_TEST(d_length_l_max, "2147483647", "%ld", 2147483647L);        // LONG_MAX на 32-бит
#endif
// Модификаторы длины вместе с шириной и точностью в середине строки
RUN_SPRINTF_TEST(d_length_mixed, "Result is: -01234567890!", "Result is: %012ld!", -1234567890L);
// Базовые тесты %x и %X
RUN_SPRINTF_TEST(x_simple, "ab", "%x", 171);
RUN_SPRINTF_TEST(X_simple_caps, "AB", "%X", 171);
RUN_SPRINTF_TEST(x_zero, "0", "%x", 0);

// Тесты с точностью (precision)
RUN_SPRINTF_TEST(x_precision, "00ab", "%.4x", 171);
RUN_SPRINTF_TEST(x_zero_precision_zero_val, "", "%.0x", 0); // Должна быть пустая строка

// Тесты с флагом # (alt_format)
RUN_SPRINTF_TEST(x_hash, "0xab", "%#x", 171);
RUN_SPRINTF_TEST(X_hash_caps, "0XAB", "%#X", 171);
RUN_SPRINTF_TEST(x_hash_zero, "0", "%#x", 0); // Для нуля 0x выводиться НЕ должен!

// Совместная работа флага # и точности (они независимы)
RUN_SPRINTF_TEST(x_hash_and_precision, "0x00ab", "%#.4x", 171);

// Большие беззнаковые числа и вывод в середине строки
RUN_SPRINTF_TEST(x_uint_max, "ffffffff", "%x", 4294967295U);
RUN_SPRINTF_TEST(x_middle_str, "Address: 0x00ff is loaded.", "Address: %#.4x is loaded.", 255);

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
  tcase_add_test(tc_core, test_positive_number_exponent);

  tcase_add_test(tc_core, test_g_zero);
  tcase_add_test(tc_core, test_g_negative_zero);
  tcase_add_test(tc_core, test_g_simple_float);
  tcase_add_test(tc_core, test_g_trailing_zeros_flat);
  tcase_add_test(tc_core, test_g_no_dot_needed);
  tcase_add_test(tc_core, test_g_large_number);
  tcase_add_test(tc_core, test_g_small_number);
  tcase_add_test(tc_core, test_g_capital_letter);
  tcase_add_test(tc_core, test_g_exp_trailing_zeros);
  tcase_add_test(tc_core, test_g_exp_no_dot);
  tcase_add_test(tc_core, test_g_precision_large);
  tcase_add_test(tc_core, test_g_precision_round);
  tcase_add_test(tc_core, test_g_precision_zero);
  tcase_add_test(tc_core, test_g_infinity);
  tcase_add_test(tc_core, test_g_nan);
  tcase_add_test(tc_core, test_g_mixed_str);
  tcase_add_test(tc_core, test_g_hash_zero);
  tcase_add_test(tc_core, test_g_hash_flat_zeros);
  tcase_add_test(tc_core, test_g_hash_no_dot_originally);
  tcase_add_test(tc_core, test_g_hash_exp_zeros);
  tcase_add_test(tc_core, test_g_hash_exp_no_dot_originally);
  tcase_add_test(tc_core, test_g_hash_with_precision);
  tcase_add_test(tc_core, test_f_hash_zero_precision);
  tcase_add_test(tc_core, test_f_hash_normal);
  tcase_add_test(tc_core, test_f_hash_zero_val);
  tcase_add_test(tc_core, test_e_hash_zero_precision);
  tcase_add_test(tc_core, test_E_hash_zero_precision);
  tcase_add_test(tc_core, test_e_hash_normal);

  tcase_add_test(tc_core, test_o_simple);
  tcase_add_test(tc_core, test_o_zero);
  tcase_add_test(tc_core, test_o_large);
  tcase_add_test(tc_core, test_o_precision_normal);
  tcase_add_test(tc_core, test_o_precision_smaller);
  tcase_add_test(tc_core, test_o_zero_precision_zero_val);
  tcase_add_test(tc_core, test_o_hash_normal);
  tcase_add_test(tc_core, test_o_hash_zero);
  tcase_add_test(tc_core, test_o_hash_and_precision);
  tcase_add_test(tc_core, test_o_negative);
  tcase_add_test(tc_core, test_o_length_h);
  tcase_add_test(tc_core, test_o_length_l);
  tcase_add_test(tc_core, test_o_middle_of_str);
  tcase_add_test(tc_core, test_o_width_right_align);
  tcase_add_test(tc_core, test_o_width_zero_flag);
  tcase_add_test(tc_core, test_o_hash_width_flags);
  tcase_add_test(tc_core, test_o_uint_max);

  tcase_add_test(tc_core, test_d_length_h_normal);
  tcase_add_test(tc_core, test_i_length_h_neg);
  tcase_add_test(tc_core, test_d_length_h_max);
  tcase_add_test(tc_core, test_d_length_l_normal);
  tcase_add_test(tc_core, test_i_length_l_min);
  tcase_add_test(tc_core, test_d_length_l_max);
  tcase_add_test(tc_core, test_d_length_mixed);

  tcase_add_test(tc_core, test_x_simple);
  tcase_add_test(tc_core, test_X_simple_caps);
  tcase_add_test(tc_core, test_x_zero);
  tcase_add_test(tc_core, test_x_precision);
  tcase_add_test(tc_core, test_x_zero_precision_zero_val);
  tcase_add_test(tc_core, test_x_hash);
  tcase_add_test(tc_core, test_X_hash_caps);
  tcase_add_test(tc_core, test_x_hash_zero);
  tcase_add_test(tc_core, test_x_hash_and_precision);
  tcase_add_test(tc_core, test_x_uint_max);
  tcase_add_test(tc_core, test_x_middle_str);

  suite_add_tcase(s, tc_core);

  return s;
}
