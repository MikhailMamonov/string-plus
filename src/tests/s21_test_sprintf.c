#include "../s21_string.h"
#include "s21_test_common.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../s21_string.h"
#include "s21_test_common.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static const char *fmt_d_prec = "%09.5d";
static const char *fmt_u_zero_prec = "%.0u";
static const char *fmt_u_simple = "%u";
static const char *FMT_U_PLUS = "%+u";
static const char *FMT_U_SPACE = "% u";
static const char *FMT_U_ZERO_PREC = "%09.5u";
static const char *FMT_O_HASH_PREC = "%#09.5o";
static const char *FMT_X_HASH_PREC = "%#09.5X";
static const char *FMT_CONFLICT_PS = "%+ d";
static const char *FMT_CONFLICT_SP = "% +d";
static const char *FMT_CONFLICT_MZ = "%-010d";

// ==================== STRING TESTS ====================
RUN_SPRINTF_TEST(string_basic, "%s", "Hello");
RUN_SPRINTF_TEST(string_with_space, "%s %s", "Hello", "World");
RUN_SPRINTF_TEST(string_empty, "%s", "");
RUN_SPRINTF_TEST(string_percent, "Hello%%");
RUN_SPRINTF_TEST(string_percent_start, "%%Hello");
RUN_SPRINTF_TEST(string_precision_cut, "%.3s", "International");
RUN_SPRINTF_TEST(string_precision_zero, "%.0s", "Don't print me");
RUN_SPRINTF_TEST(string_precision_overflow, "%.20s", "Short");

// ==================== CHAR TESTS ====================
RUN_SPRINTF_TEST(char_basic, "%c", 'A');
RUN_SPRINTF_TEST(char_digit, "%c", '5');
RUN_SPRINTF_TEST(char_width, "|%10c|", 'A');
RUN_SPRINTF_TEST(char_width_left_align, "|%-10c|", 'A');
RUN_SPRINTF_TEST(char_width_left_null_string, "|%-10c|", '\0');
RUN_SPRINTF_TEST(char_special, "%c", '\n');
RUN_SPRINTF_TEST(char_null, "%c", '\0');

// ==================== INTEGER TESTS ====================
RUN_SPRINTF_TEST(int_positive, "%d", 42);
RUN_SPRINTF_TEST(int_negative, "%d", -123);
RUN_SPRINTF_TEST(int_zero, "%d", 0);
RUN_SPRINTF_TEST(int_two, "%d %d", 10, 20);
RUN_SPRINTF_TEST(int_three, "%d + %d = %d", 10, 20, 30);
RUN_SPRINTF_TEST(int_width, "|%8d|", 42);
RUN_SPRINTF_TEST(int_width_left_align, "|%-8d|", 42);
RUN_SPRINTF_TEST(int_negative_width, "|%10d|", -42);
RUN_SPRINTF_TEST(int_negative_width_left_align, "|%-10d|", -42);
RUN_SPRINTF_TEST(short_int, "%hd", (short)2342);
RUN_SPRINTF_TEST(signed_char, "%hhd", (signed char)-56);
RUN_SPRINTF_TEST(int_min_boundary, "%d", -2147483647 - 1);
RUN_SPRINTF_TEST(int_max_boundary, "%d", 2147483647);
RUN_SPRINTF_TEST(int_precision_zero_val_zero, "%.0d", 0);
RUN_SPRINTF_TEST(d_zero_and_precision_pos, fmt_d_prec, 42);
RUN_SPRINTF_TEST(d_zero_and_precision_neg, fmt_d_prec, -42);

// ==================== LONG INTEGER TESTS ====================
RUN_SPRINTF_TEST(d_length_h_normal, "%hd", (short)12345);
RUN_SPRINTF_TEST(i_length_h_neg, "%hi", (short)-32768);
RUN_SPRINTF_TEST(d_length_h_max, "%hd", (short)32767);
RUN_SPRINTF_TEST(d_length_l_normal, "%ld", 1234567890L);
#if __WORDSIZE == 64
RUN_SPRINTF_TEST(i_length_l_min, "%li", -9223372036854775807L - 1L);
RUN_SPRINTF_TEST(d_length_l_max, "%ld", 9223372036854775807L);
#else
RUN_SPRINTF_TEST(i_length_l_min, "%li", -2147483647L - 1L);
RUN_SPRINTF_TEST(d_length_l_max, "%ld", 2147483647L);
#endif
RUN_SPRINTF_TEST(d_length_mixed, "Result is: %012ld!", -1234567890L);

// ==================== UNSIGNED TESTS ====================
RUN_SPRINTF_TEST(u_simple, "%u", 12345);
RUN_SPRINTF_TEST(u_zero, "%u", 0);
RUN_SPRINTF_TEST(u_precision, "%.5u", 42);
RUN_SPRINTF_TEST(u_zero_precision_zero_val, fmt_u_zero_prec, 0);
RUN_SPRINTF_TEST(u_negative, fmt_u_simple, -1);
RUN_SPRINTF_TEST(u_negative_large, fmt_u_simple, -12345);
RUN_SPRINTF_TEST(u_plus_flag, FMT_U_PLUS, 100);
RUN_SPRINTF_TEST(u_space_flag, FMT_U_SPACE, 100);
RUN_SPRINTF_TEST(u_zero_and_precision, FMT_U_ZERO_PREC, 42);
RUN_SPRINTF_TEST(u_length_h, "%hu", (unsigned short)-1);
RUN_SPRINTF_TEST(u_length_l, "%lu", 4294967295L);
RUN_SPRINTF_TEST(uint_precision_zero_val_zero, "%.0u", 0);

// ==================== OCTAL TESTS ====================
RUN_SPRINTF_TEST(o_simple, "%o", 10);
RUN_SPRINTF_TEST(o_zero, "%o", 0);
RUN_SPRINTF_TEST(o_large, "%o", 1000);
RUN_SPRINTF_TEST(o_precision_normal, "%.4o", 10);
RUN_SPRINTF_TEST(o_precision_smaller, "%.1o", 10);
RUN_SPRINTF_TEST(o_zero_precision_zero_val, "%.0o", 0);
RUN_SPRINTF_TEST(o_hash_normal, "%#o", 10);
RUN_SPRINTF_TEST(o_hash_zero, "%#o", 0);
RUN_SPRINTF_TEST(o_hash_and_precision, "%#.4o", 10);
RUN_SPRINTF_TEST(o_negative, "%o", -1);
RUN_SPRINTF_TEST(o_length_h, "%ho", (unsigned short)-1);
RUN_SPRINTF_TEST(o_length_l, "%lo", (unsigned long)-1);
RUN_SPRINTF_TEST(o_middle_of_str, "Permissions: %#o is secure.", 493);
RUN_SPRINTF_TEST(o_width_right_align, "%5o", 10);
RUN_SPRINTF_TEST(o_width_zero_flag, "%05o", 10);
RUN_SPRINTF_TEST(o_hash_width_flags, "%#5o", 10);
RUN_SPRINTF_TEST(o_uint_max, "%o", 4294967295U);
RUN_SPRINTF_TEST(o_zero_precision_and_hash, FMT_O_HASH_PREC, 10);
RUN_SPRINTF_TEST(o_zero_width_hash_flag, "%#05o", 8);
RUN_SPRINTF_TEST(octal_hash_precision_zero_val_zero, "%#.0o", 0);

// ==================== HEX TESTS ====================
RUN_SPRINTF_TEST(x_simple, "%x", 171);
RUN_SPRINTF_TEST(X_simple_caps, "%X", 171);
RUN_SPRINTF_TEST(x_zero, "%x", 0);
RUN_SPRINTF_TEST(x_precision, "%.4x", 171);
RUN_SPRINTF_TEST(x_zero_precision_zero_val, "%.0x", 0);
RUN_SPRINTF_TEST(x_hash, "%#x", 171);
RUN_SPRINTF_TEST(X_hash_caps, "%#X", 171);
RUN_SPRINTF_TEST(x_hash_zero, "%#x", 0);
RUN_SPRINTF_TEST(x_hash_and_precision, "%#.4x", 171);
RUN_SPRINTF_TEST(x_uint_max, "%x", 4294967295U);
RUN_SPRINTF_TEST(x_middle_str, "Address: %#.4x is loaded.", 255);
RUN_SPRINTF_TEST(X_zero_precision_hash, FMT_X_HASH_PREC, 171);
RUN_SPRINTF_TEST(x_zero_width_hash_and_plus, "%#09x", 171);
RUN_SPRINTF_TEST(x_zero_width_hash_and_space, "%#09x", 171);

// ==================== FLOAT TESTS ====================
RUN_SPRINTF_TEST(zero_float, "%f", 0.0);
RUN_SPRINTF_TEST(negative_zero_float, "%f", -0.0);
RUN_SPRINTF_TEST(positive_number_float, "%f", 123.456);
RUN_SPRINTF_TEST(negative_number_float, "%f", -123.456);
RUN_SPRINTF_TEST(precision_zero_float, "%.0f", 123.456);
RUN_SPRINTF_TEST(precision_short_float, "%.2f", 123.456);
RUN_SPRINTF_TEST(precision_long_float, "%.8f", 0.00123);
RUN_SPRINTF_TEST(round_down_float, "%.2f", 1.234);
RUN_SPRINTF_TEST(round_up_float, "%.2f", 1.236);
RUN_SPRINTF_TEST(round_carry_to_int_float, "%.2f", 9.999);
RUN_SPRINTF_TEST(flag_plus_positive_float, "%+f", 1.23);
RUN_SPRINTF_TEST(flag_plus_negative_float, "%+f", -1.23);
RUN_SPRINTF_TEST(flag_space_positive_float, "% f", 1.23);
RUN_SPRINTF_TEST(flag_space_negative_float, "% f", -1.23);
RUN_SPRINTF_TEST(infinity_lowercase_float, "%f", INFINITY);
RUN_SPRINTF_TEST(nan_lowercase_float, "%f", NAN);
RUN_SPRINTF_TEST(nan_with_plus_flag_float, "%+f", NAN);
RUN_SPRINTF_TEST(very_small_float, "%f", 1e-10);
RUN_SPRINTF_TEST(large_number_float, "%f", 1000000000.0);
RUN_SPRINTF_TEST(f_zero_width_plus_flag, "%+010f", 5.5);
RUN_SPRINTF_TEST(f_hash_zero_precision, "%#.0f", 123.0);
RUN_SPRINTF_TEST(f_hash_normal, "%#f", 123.456);
RUN_SPRINTF_TEST(f_hash_zero_val, "%#.0f", 0.0);
RUN_SPRINTF_TEST(f_zero_width_nan, "%08f", NAN);
RUN_SPRINTF_TEST(f_zero_width_inf, "%08f", INFINITY);
RUN_SPRINTF_TEST(f_zero_width_neg_inf, "%08f", -INFINITY);

// ==================== EXPONENT TESTS ====================
RUN_SPRINTF_TEST(zero_exponent, "%e", 0.0);
RUN_SPRINTF_TEST(positive_number_exponent, "%e", 123.456);
RUN_SPRINTF_TEST(negative_zero_exponent, "%e", -0.0);
RUN_SPRINTF_TEST(negative_number_exponent, "%e", -123.456);
RUN_SPRINTF_TEST(negative_exponent, "%e", -0.00123);
RUN_SPRINTF_TEST(capital_letter_exponent, "%E", -0.00123);
RUN_SPRINTF_TEST(round_exponent, "%.2e", 1239.56);
RUN_SPRINTF_TEST(infinity_exponent, "%e", -INFINITY);
RUN_SPRINTF_TEST(nan_exponent, "%E", NAN);
RUN_SPRINTF_TEST(e_hash_zero_precision, "%#.0e", 123.0);
RUN_SPRINTF_TEST(E_hash_zero_precision, "%#.0E", 123.0);
RUN_SPRINTF_TEST(e_hash_normal, "%#e", 123.456);

// ==================== G TESTS ====================
RUN_SPRINTF_TEST(g_zero, "%g", 0.0);
RUN_SPRINTF_TEST(g_negative_zero, "%g", -0.0);
RUN_SPRINTF_TEST(g_simple_float, "%g", 123.456);
RUN_SPRINTF_TEST(g_trailing_zeros_flat, "%g", 1.230000);
RUN_SPRINTF_TEST(g_no_dot_needed, "%g", 125.000000);
RUN_SPRINTF_TEST(g_large_number, "%g", 1234560.0);
RUN_SPRINTF_TEST(g_small_number, "%g", 0.0000123456);
RUN_SPRINTF_TEST(g_capital_letter, "%G", 1234560.0);
RUN_SPRINTF_TEST(g_exp_trailing_zeros, "%g", 1200000.0);
RUN_SPRINTF_TEST(g_exp_no_dot, "%G", 1000000.0);
RUN_SPRINTF_TEST(g_precision_large, "%.2g", 12.345);
RUN_SPRINTF_TEST(g_precision_round, "%.3g", 1.23956);
RUN_SPRINTF_TEST(g_precision_zero, "%.0g", 1.2345);
RUN_SPRINTF_TEST(g_infinity, "%g", -INFINITY);
RUN_SPRINTF_TEST(g_nan, "%G", NAN);
RUN_SPRINTF_TEST(g_mixed_str, "Value: %g and %g", 0.000123, 45.67);
RUN_SPRINTF_TEST(g_hash_zero, "%#g", 0.0);
RUN_SPRINTF_TEST(g_hash_flat_zeros, "%#g", 1.23);
RUN_SPRINTF_TEST(g_hash_no_dot_originally, "%#g", 125.0);
RUN_SPRINTF_TEST(g_hash_exp_zeros, "%#g", 1200000.0);
RUN_SPRINTF_TEST(g_hash_exp_no_dot_originally, "%#G", 1000000.0);
RUN_SPRINTF_TEST(g_hash_with_precision, "%#.4g", 1.24);

// ==================== LONG DOUBLE TESTS ====================
RUN_SPRINTF_TEST(float_length_L, "%Lf", 123.456789L);
RUN_SPRINTF_TEST(exp_length_L, "%Le", 987654.321L);
RUN_SPRINTF_TEST(g_length_L, "%Lg", 0.000012345L);
RUN_SPRINTF_TEST(float_L_width_flags, "%+015.4Lf", 12345.6789L);
RUN_SPRINTF_TEST(float_L_asterisk_precision, "%.*Lf", 3, 123.456789L);
RUN_SPRINTF_TEST(float_L_asterisk_zero_precision, "%.*Lf", 0, 123.456789L);
RUN_SPRINTF_TEST(exp_L_asterisk_precision, "%.*Le", 4, 987654.321L);
RUN_SPRINTF_TEST(exp_LE_asterisk_precision, "%.*LE", 2, 0.00123L);
RUN_SPRINTF_TEST(g_L_asterisk_precision, "%.*Lg", 4, 1234.5678L);
RUN_SPRINTF_TEST(G_L_asterisk_precision, "%.*LG", 2, 987654.0L);
RUN_SPRINTF_TEST(float_L_asterisk_width_and_precision, "%*.*Lf", 12, 4, 45.678912L);

// ==================== POINTER TESTS ====================
int dummy_var = 42;
RUN_SPRINTF_TEST(p_simple, "%p", &dummy_var);
RUN_SPRINTF_TEST(p_zero_null, "%p", NULL);
RUN_SPRINTF_TEST(p_width_normal, "%20p", &dummy_var);
RUN_SPRINTF_TEST(p_width_null, "%10p", NULL);
RUN_SPRINTF_TEST(p_width_left_align_null, "%-10p", NULL);

// ==================== N SPECIFIER TESTS ====================
START_TEST(test_n_simple) {
    char std_buf[100] = {0};
    char test_buf[100] = {0};
    int std_count = -1, test_count = -1;
    int std_len = sprintf(std_buf, "Hello, %nworld!", &std_count);
    int test_len = s21_sprintf(test_buf, "Hello, %nworld!", &test_count);
    ck_assert_int_eq(std_len, test_len);
    ck_assert_str_eq(std_buf, test_buf);
    ck_assert_int_eq(std_count, test_count);
}
END_TEST

START_TEST(test_n_length_h) {
    char std_buf[100] = {0};
    char test_buf[100] = {0};
    short std_count = -1, test_count = -1;
    int std_len = sprintf(std_buf, "Short int %hn test", &std_count);
    int test_len = s21_sprintf(test_buf, "Short int %hn test", &test_count);
    ck_assert_int_eq(std_len, test_len);
    ck_assert_str_eq(std_buf, test_buf);
    ck_assert_int_eq(std_count, test_count);
}
END_TEST

START_TEST(test_n_length_l) {
    char std_buf[100] = {0};
    char test_buf[100] = {0};
    long std_count = -1, test_count = -1;
    int std_len = sprintf(std_buf, "Width %5d and %-8s%ln", 42, "text", &std_count);
    int test_len = s21_sprintf(test_buf, "Width %5d and %-8s%ln", 42, "text", &test_count);
    ck_assert_int_eq(std_len, test_len);
    ck_assert_str_eq(std_buf, test_buf);
    ck_assert_int_eq(std_count, test_count);
}
END_TEST

// ==================== EXTRA DYNAMIC & CONFLICT TESTS ====================
RUN_SPRINTF_TEST(asterisk_negative_width, "%*d", -10, 42);
RUN_SPRINTF_TEST(asterisk_negative_precision, "%.*d", -5, 99);
RUN_SPRINTF_TEST(flags_conflict_plus_space, FMT_CONFLICT_PS, 7);
RUN_SPRINTF_TEST(flags_conflict_space_plus, FMT_CONFLICT_SP, 7);
RUN_SPRINTF_TEST(flags_conflict_minus_zero, FMT_CONFLICT_MZ, 42);

// ==================== FLAG COMBINATION TESTS ====================
RUN_SPRINTF_TEST(d_zero_width_plus_flag, "%+05d", 5);
RUN_SPRINTF_TEST(d_zero_width_space_flag, "% 05d", 5);

// ==================== MIXED TESTS ====================
RUN_SPRINTF_TEST(mixed_string_int, "%s %d", "answer", 42);
RUN_SPRINTF_TEST(mixed_int_string, "%d %s %s", 42, "is", "answer");
RUN_SPRINTF_TEST(mixed_str_int_float, "Price: %.2f %s (discounted from %d)", 49.99, "USD", 50);
RUN_SPRINTF_TEST(mixed_str_int_exp, "The number %d can be presented as %E. Interesting!", 1000, 1000.0);
RUN_SPRINTF_TEST(mixed_string_and_int, "User: %-8.3s | ID: %05d", "Administrator", 42);
RUN_SPRINTF_TEST(mixed_multiple_numbers, "Hex: %#-8x Oct: %#06o Val: %+5d", 255, 8, 12);
RUN_SPRINTF_TEST(mixed_complex_row, "(%5.2s) status is %08f (code %X)", "OK_DONE", NAN, 15);

void register_string_tests(TCase *tc) {
    tcase_add_test(tc, test_string_basic);
    tcase_add_test(tc, test_string_with_space);
    tcase_add_test(tc, test_string_empty);
    tcase_add_test(tc, test_string_percent);
    tcase_add_test(tc, test_string_percent_start);
    tcase_add_test(tc, test_string_precision_cut);
    tcase_add_test(tc, test_string_precision_zero);
    tcase_add_test(tc, test_string_precision_overflow);
}

void register_char_tests(TCase *tc) {
    tcase_add_test(tc, test_char_basic);
    tcase_add_test(tc, test_char_digit);
    tcase_add_test(tc, test_char_width);
    tcase_add_test(tc, test_char_width_left_align);
    tcase_add_test(tc, test_char_width_left_null_string);
    tcase_add_test(tc, test_char_special);
    tcase_add_test(tc, test_char_null);
}

void register_int_tests(TCase *tc) {
    tcase_add_test(tc, test_int_positive);
    tcase_add_test(tc, test_int_negative);
    tcase_add_test(tc, test_int_zero);
    tcase_add_test(tc, test_int_two);
    tcase_add_test(tc, test_int_three);
    tcase_add_test(tc, test_int_width);
    tcase_add_test(tc, test_int_width_left_align);
    tcase_add_test(tc, test_int_negative_width);
    tcase_add_test(tc, test_int_negative_width_left_align);
    tcase_add_test(tc, test_short_int);
    tcase_add_test(tc, test_signed_char);
    tcase_add_test(tc, test_int_min_boundary);
    tcase_add_test(tc, test_int_max_boundary);
    tcase_add_test(tc, test_int_precision_zero_val_zero);
    tcase_add_test(tc, test_d_zero_and_precision_pos);
    tcase_add_test(tc, test_d_zero_and_precision_neg);
}

void register_long_int_tests(TCase *tc) {
    tcase_add_test(tc, test_d_length_h_normal);
    tcase_add_test(tc, test_i_length_h_neg);
    tcase_add_test(tc, test_d_length_h_max);
    tcase_add_test(tc, test_d_length_l_normal);
    tcase_add_test(tc, test_i_length_l_min);
    tcase_add_test(tc, test_d_length_l_max);
    tcase_add_test(tc, test_d_length_mixed);
}

void register_unsigned_tests(TCase *tc) {
    tcase_add_test(tc, test_u_simple);
    tcase_add_test(tc, test_u_zero);
    tcase_add_test(tc, test_u_precision);
    tcase_add_test(tc, test_u_zero_precision_zero_val);
    tcase_add_test(tc, test_u_negative);
    tcase_add_test(tc, test_u_negative_large);
    tcase_add_test(tc, test_u_plus_flag);
    tcase_add_test(tc, test_u_space_flag);
    tcase_add_test(tc, test_u_zero_and_precision);
    tcase_add_test(tc, test_u_length_h);
    tcase_add_test(tc, test_u_length_l);
    tcase_add_test(tc, test_uint_precision_zero_val_zero);
}

void register_octal_tests(TCase *tc) {
    tcase_add_test(tc, test_o_simple);
    tcase_add_test(tc, test_o_zero);
    tcase_add_test(tc, test_o_large);
    tcase_add_test(tc, test_o_precision_normal);
    tcase_add_test(tc, test_o_precision_smaller);
    tcase_add_test(tc, test_o_zero_precision_zero_val);
    tcase_add_test(tc, test_o_hash_normal);
    tcase_add_test(tc, test_o_hash_zero);
    tcase_add_test(tc, test_o_hash_and_precision);
    tcase_add_test(tc, test_o_negative);
    tcase_add_test(tc, test_o_length_h);
    tcase_add_test(tc, test_o_length_l);
    tcase_add_test(tc, test_o_middle_of_str);
    tcase_add_test(tc, test_o_width_right_align);
    tcase_add_test(tc, test_o_width_zero_flag);
    tcase_add_test(tc, test_o_hash_width_flags);
    tcase_add_test(tc, test_o_uint_max);
    tcase_add_test(tc, test_o_zero_precision_and_hash);
    tcase_add_test(tc, test_o_zero_width_hash_flag);
    tcase_add_test(tc, test_octal_hash_precision_zero_val_zero);
}

void register_hex_tests(TCase *tc) {
    tcase_add_test(tc, test_x_simple);
    tcase_add_test(tc, test_X_simple_caps);
    tcase_add_test(tc, test_x_zero);
    tcase_add_test(tc, test_x_precision);
    tcase_add_test(tc, test_x_zero_precision_zero_val);
    tcase_add_test(tc, test_x_hash);
    tcase_add_test(tc, test_X_hash_caps);
    tcase_add_test(tc, test_x_hash_zero);
    tcase_add_test(tc, test_x_hash_and_precision);
    tcase_add_test(tc, test_x_uint_max);
    tcase_add_test(tc, test_x_middle_str);
    tcase_add_test(tc, test_X_zero_precision_hash);
    tcase_add_test(tc, test_x_zero_width_hash_and_plus);
    tcase_add_test(tc, test_x_zero_width_hash_and_space);
}

void register_float_tests(TCase *tc) {
    tcase_add_test(tc, test_zero_float);
    tcase_add_test(tc, test_negative_zero_float);
    tcase_add_test(tc, test_positive_number_float);
    tcase_add_test(tc, test_negative_number_float);
    tcase_add_test(tc, test_precision_zero_float);
    tcase_add_test(tc, test_precision_short_float);
    tcase_add_test(tc, test_precision_long_float);
    tcase_add_test(tc, test_round_down_float);
    tcase_add_test(tc, test_round_up_float);
    tcase_add_test(tc, test_round_carry_to_int_float);
    tcase_add_test(tc, test_flag_plus_positive_float);
    tcase_add_test(tc, test_flag_plus_negative_float);
    tcase_add_test(tc, test_flag_space_positive_float);
    tcase_add_test(tc, test_flag_space_negative_float);
    tcase_add_test(tc, test_infinity_lowercase_float);
    tcase_add_test(tc, test_nan_lowercase_float);
    tcase_add_test(tc, test_nan_with_plus_flag_float);
    tcase_add_test(tc, test_very_small_float);
    tcase_add_test(tc, test_large_number_float);
    tcase_add_test(tc, test_f_zero_width_plus_flag);
    tcase_add_test(tc, test_f_hash_zero_precision);
    tcase_add_test(tc, test_f_hash_normal);
    tcase_add_test(tc, test_f_hash_zero_val);
    tcase_add_test(tc, test_f_zero_width_nan);
    tcase_add_test(tc, test_f_zero_width_inf);
    tcase_add_test(tc, test_f_zero_width_neg_inf);
}

void register_exponent_tests(TCase *tc) {
    tcase_add_test(tc, test_zero_exponent);
    tcase_add_test(tc, test_positive_number_exponent);
    tcase_add_test(tc, test_negative_zero_exponent);
    tcase_add_test(tc, test_negative_number_exponent);
    tcase_add_test(tc, test_negative_exponent);
    tcase_add_test(tc, test_capital_letter_exponent);
    tcase_add_test(tc, test_round_exponent);
    tcase_add_test(tc, test_infinity_exponent);
    tcase_add_test(tc, test_nan_exponent);
    tcase_add_test(tc, test_e_hash_zero_precision);
    tcase_add_test(tc, test_E_hash_zero_precision);
    tcase_add_test(tc, test_e_hash_normal);
}

void register_g_tests(TCase *tc) {
    tcase_add_test(tc, test_g_zero);
    tcase_add_test(tc, test_g_negative_zero);
    tcase_add_test(tc, test_g_simple_float);
    tcase_add_test(tc, test_g_trailing_zeros_flat);
    tcase_add_test(tc, test_g_no_dot_needed);
    tcase_add_test(tc, test_g_large_number);
    tcase_add_test(tc, test_g_small_number);
    tcase_add_test(tc, test_g_capital_letter);
    tcase_add_test(tc, test_g_exp_trailing_zeros);
    tcase_add_test(tc, test_g_exp_no_dot);
    tcase_add_test(tc, test_g_precision_large);
    tcase_add_test(tc, test_g_precision_round);
    tcase_add_test(tc, test_g_precision_zero);
    tcase_add_test(tc, test_g_infinity);
    tcase_add_test(tc, test_g_nan);
    tcase_add_test(tc, test_g_mixed_str);
    tcase_add_test(tc, test_g_hash_zero);
    tcase_add_test(tc, test_g_hash_flat_zeros);
    tcase_add_test(tc, test_g_hash_no_dot_originally);
    tcase_add_test(tc, test_g_hash_exp_zeros);
    tcase_add_test(tc, test_g_hash_exp_no_dot_originally);
    tcase_add_test(tc, test_g_hash_with_precision);
}

void register_long_double_tests(TCase *tc) {
    tcase_add_test(tc, test_float_length_L);
    tcase_add_test(tc, test_exp_length_L);
    tcase_add_test(tc, test_g_length_L);
    tcase_add_test(tc, test_float_L_width_flags);
    tcase_add_test(tc, test_float_L_asterisk_precision);
    tcase_add_test(tc, test_float_L_asterisk_zero_precision);
    tcase_add_test(tc, test_exp_L_asterisk_precision);
    tcase_add_test(tc, test_exp_LE_asterisk_precision);
    tcase_add_test(tc, test_g_L_asterisk_precision);
    tcase_add_test(tc, test_G_L_asterisk_precision);
    tcase_add_test(tc, test_float_L_asterisk_width_and_precision);
}

void register_pointer_tests(TCase *tc) {
    tcase_add_test(tc, test_p_simple);
    tcase_add_test(tc, test_p_zero_null);
    tcase_add_test(tc, test_p_width_normal);
    tcase_add_test(tc, test_p_width_null);
    tcase_add_test(tc, test_p_width_left_align_null);
}

void register_n_tests(TCase *tc) {
    tcase_add_test(tc, test_n_simple);
    tcase_add_test(tc, test_n_length_h);
    tcase_add_test(tc, test_n_length_l);
}

void register_flag_tests(TCase *tc) {
    tcase_add_test(tc, test_d_zero_width_plus_flag);
    tcase_add_test(tc, test_d_zero_width_space_flag);
    tcase_add_test(tc, test_asterisk_negative_width);
    tcase_add_test(tc, test_asterisk_negative_precision);
    tcase_add_test(tc, test_flags_conflict_plus_space);
    tcase_add_test(tc, test_flags_conflict_space_plus);
    tcase_add_test(tc, test_flags_conflict_minus_zero);
}

void register_mixed_tests(TCase *tc) {
    tcase_add_test(tc, test_mixed_string_int);
    tcase_add_test(tc, test_mixed_int_string);
    tcase_add_test(tc, test_mixed_str_int_float);
    tcase_add_test(tc, test_mixed_str_int_exp);
    tcase_add_test(tc, test_mixed_string_and_int);
    tcase_add_test(tc, test_mixed_multiple_numbers);
    tcase_add_test(tc, test_mixed_complex_row);
}

Suite *sprintf_suite_create(void) {
    Suite *s = suite_create("sprintf");
    TCase *tc_core = tcase_create("Core");
    
    register_string_tests(tc_core);
    register_char_tests(tc_core);
    register_int_tests(tc_core);
    register_long_int_tests(tc_core);
    register_unsigned_tests(tc_core);
    register_octal_tests(tc_core);
    register_hex_tests(tc_core);
    register_float_tests(tc_core);
    register_exponent_tests(tc_core);
    register_g_tests(tc_core);
    register_long_double_tests(tc_core);
    register_pointer_tests(tc_core);
    register_n_tests(tc_core);
    register_flag_tests(tc_core);
    register_mixed_tests(tc_core);
    suite_add_tcase(s, tc_core);
    return s;
}