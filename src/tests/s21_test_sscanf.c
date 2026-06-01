#include "../s21_string.h"
#include "s21_test_common.h"
#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== STRING TESTS ====================
START_TEST(test_string_basic) {
  char std_buf[1024] = {0}, test_buf[1024] = {0};
  const char *input = "Hello";
  const char *format = "%s";
  
  int std_len = sscanf(input, format, std_buf);
  int test_len = s21_sscanf(input, format, test_buf);
  
  ck_assert_str_eq(std_buf, test_buf);
  ck_assert_str_eq(std_buf, "Hello");
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_string_with_space) {
  char std_buf1[1024] = {0}, std_buf2[1024] = {0};
  char test_buf1[1024] = {0}, test_buf2[1024] = {0};
  const char *input = "Hello World";
  const char *format = "%s %s";
  
  int std_len = sscanf(input, format, std_buf1, std_buf2);
  int test_len = s21_sscanf(input, format, test_buf1, test_buf2);
  
  ck_assert_str_eq(std_buf1, test_buf1);
  ck_assert_str_eq(std_buf1, "Hello");
  ck_assert_str_eq(std_buf2, test_buf2);
  ck_assert_str_eq(std_buf2, "World");
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 2);
}
END_TEST

START_TEST(test_string_empty) {
  char std_buf[1024] = {0}, test_buf[1024] = {0};
  const char *input = "";
  const char *format = "%s";
  
  int std_len = sscanf(input, format, std_buf);
  int test_len = s21_sscanf(input, format, test_buf);
  
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, -1);
}
END_TEST

START_TEST(test_string_percent) {
  const char *input = "Hello";
  
  int std_len = sscanf(input, "Hello%%");
  int test_len = s21_sscanf(input, "Hello%%");
  
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 0);
}
END_TEST

START_TEST(test_string_percent_start) {
  const char *input = "Hello";
  
  int std_len = sscanf(input, "%%Hello");
  int test_len = s21_sscanf(input, "%%Hello");
  
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 0);
}
END_TEST

// ==================== CHAR TESTS ====================
START_TEST(test_char_basic) {
  char std_val = 0, test_val = 0;
  const char *input = "A";
  const char *format = "%c";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 'A');
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_char_digit) {
  char std_val = 0, test_val = 0;
  const char *input = "5";
  const char *format = "%c";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, '5');
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_char_special) {
  char std_val = 0, test_val = 0;
  const char *input = "\n";
  const char *format = "%c";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, '\n');
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

// ==================== INTEGER TESTS ====================
START_TEST(test_int_positive) {
  int std_val = 0, test_val = 0;
  const char *input = "42";
  const char *format = "%d";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 42);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_int_negative) {
  int std_val = 0, test_val = 0;
  const char *input = "-123";
  const char *format = "%d";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, -123);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_int_zero) {
  int std_val = 0, test_val = 0;
  const char *input = "0";
  const char *format = "%d";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 0);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_int_two) {
  int std_a = 0, std_b = 0, test_a = 0, test_b = 0;
  const char *input = "10 20";
  const char *format = "%d %d";
  
  int std_len = sscanf(input, format, &std_a, &std_b);
  int test_len = s21_sscanf(input, format, &test_a, &test_b);
  
  ck_assert_int_eq(std_a, test_a);
  ck_assert_int_eq(std_a, 10);
  ck_assert_int_eq(std_b, test_b);
  ck_assert_int_eq(std_b, 20);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 2);
}
END_TEST

START_TEST(test_int_three) {
  int std_a = 0, std_b = 0, std_c = 0;
  int test_a = 0, test_b = 0, test_c = 0;
  const char *input = "10 + 20 = 30";
  const char *format = "%d + %d = %d";
  
  int std_len = sscanf(input, format, &std_a, &std_b, &std_c);
  int test_len = s21_sscanf(input, format, &test_a, &test_b, &test_c);
  
  ck_assert_int_eq(std_a, test_a);
  ck_assert_int_eq(std_a, 10);
  ck_assert_int_eq(std_b, test_b);
  ck_assert_int_eq(std_b, 20);
  ck_assert_int_eq(std_c, test_c);
  ck_assert_int_eq(std_c, 30);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 3);
}
END_TEST

START_TEST(test_int_min_boundary) {
  int std_val = 0, test_val = 0;
  const char *input = "-2147483648";
  const char *format = "%d";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, -2147483647 - 1);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_int_max_boundary) {
  int std_val = 0, test_val = 0;
  const char *input = "2147483647";
  const char *format = "%d";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 2147483647);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_short_int) {
  short std_val = 0, test_val = 0;
  const char *input = "2342";
  const char *format = "%hd";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 2342);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST


START_TEST(test_long_int) {
  long std_val = 0, test_val = 0;
  const char *input = "1234567890";
  const char *format = "%ld";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 1234567890L);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

// ==================== UNSIGNED TESTS ====================
START_TEST(test_u_simple) {
  unsigned int std_val = 0, test_val = 0;
  const char *input = "12345";
  const char *format = "%u";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 12345);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_u_zero) {
  unsigned int std_val = 0, test_val = 0;
  const char *input = "0";
  const char *format = "%u";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 0);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

// ==================== OCTAL TESTS ====================
START_TEST(test_o_simple) {
  unsigned int std_val = 0, test_val = 0;
  const char *input = "12";
  const char *format = "%o";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 10);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

// ==================== HEX TESTS ====================
START_TEST(test_x_simple) {
  unsigned int std_val = 0, test_val = 0;
  const char *input = "ab";
  const char *format = "%x";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 171);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_x_zero) {
  unsigned int std_val = 0, test_val = 0;
  const char *input = "0";
  const char *format = "%x";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 0);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

// ==================== FLOAT TESTS ====================
START_TEST(test_zero_float) {
  float std_val = 0.0f, test_val = 0.0f;
  const char *input = "0.0";
  const char *format = "%f";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_float_eq_tol(std_val, test_val, 1e-6);
  ck_assert_float_eq_tol(std_val, 0.0, 1e-6);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_positive_number_float) {
  float std_val = 0.0f, test_val = 0.0f;
  const char *input = "123.456";
  const char *format = "%f";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_float_eq_tol(std_val, test_val, 1e-6);
  ck_assert_float_eq_tol(std_val, 123.456, 1e-6);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_negative_number_float) {
  float std_val = 0.0f, test_val = 0.0f;
  const char *input = "-123.456";
  const char *format = "%f";
  
  int std_len = sscanf(input, format, &std_val);
  int test_len = s21_sscanf(input, format, &test_val);
  
  ck_assert_float_eq_tol(std_val, test_val, 1e-6);
  ck_assert_float_eq_tol(std_val, -123.456, 1e-6);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

// ==================== POINTER TESTS ====================
static int dummy_var = 42;

START_TEST(test_p_simple) {
  void *std_ptr = NULL, *test_ptr = NULL;
  char input[100];
  sprintf(input, "%p", &dummy_var);
  const char *format = "%p";
  
  int std_len = sscanf(input, format, &std_ptr);
  int test_len = s21_sscanf(input, format, &test_ptr);
  
  ck_assert_ptr_eq(std_ptr, test_ptr);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

START_TEST(test_p_zero_null) {
  void *std_ptr = NULL, *test_ptr = NULL;
  const char *input = "(nil)";
  const char *format = "%p";
  
  int std_len = sscanf(input, format, &std_ptr);
  int test_len = s21_sscanf(input, format, &test_ptr);
  
  ck_assert_ptr_eq(std_ptr, test_ptr);
  ck_assert_ptr_eq(std_ptr, NULL);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 1);
}
END_TEST

// ==================== MIXED TESTS ====================
START_TEST(test_mixed_string_int) {
  char std_str[100] = {0}, test_str[100] = {0};
  int std_val = 0, test_val = 0;
  const char *input = "answer 42";
  const char *format = "%s %d";
  
  int std_len = sscanf(input, format, std_str, &std_val);
  int test_len = s21_sscanf(input, format, test_str, &test_val);
  
  ck_assert_str_eq(std_str, test_str);
  ck_assert_str_eq(std_str, "answer");
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 42);
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 2);
}
END_TEST

START_TEST(test_mixed_int_string) {
  char std_str1[100] = {0}, std_str2[100] = {0};
  char test_str1[100] = {0}, test_str2[100] = {0};
  int std_val = 0, test_val = 0;
  const char *input = "42 is answer";
  const char *format = "%d %s %s";
  
  int std_len = sscanf(input, format, &std_val, std_str1, std_str2);
  int test_len = s21_sscanf(input, format, &test_val, test_str1, test_str2);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 42);
  ck_assert_str_eq(std_str1, test_str1);
  ck_assert_str_eq(std_str1, "is");
  ck_assert_str_eq(std_str2, test_str2);
  ck_assert_str_eq(std_str2, "answer");
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 3);
}
END_TEST

// ==================== PERCENT TESTS ====================
START_TEST(test_percent_simple) {
  const char *input = "%";
  
  int std_len = sscanf(input, "%%");
  int test_len = s21_sscanf(input, "%%");
  
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 0);
}
END_TEST

START_TEST(test_percent_mixed) {
  int std_val = 0, test_val = 0;
  float std_float = 0.0f, test_float = 0.0f;
  char std_str[100] = {0}, test_str[100] = {0};
  const char *input = "Our discount is more than 50%. Now it only costs 249.99USD!";
  const char *format = "Our discount is more than %d%%. Now it only costs %f%s!";
  
  int std_len = sscanf(input, format, &std_val, &std_float, std_str);
  int test_len = s21_sscanf(input, format, &test_val, &test_float, test_str);
  
  ck_assert_int_eq(std_val, test_val);
  ck_assert_int_eq(std_val, 50);
  ck_assert_float_eq_tol(std_float, test_float, 1e-6);
  ck_assert_float_eq_tol(std_float, 249.99, 1e-6);
  ck_assert_str_eq(std_str, test_str);
  ck_assert_str_eq(std_str, "USD");
  ck_assert_int_eq(std_len, test_len);
  ck_assert_int_eq(std_len, 3);
}
END_TEST

// ==================== REGISTRATION FUNCTIONS ====================
void register_sscanf_string_tests(TCase *tc) {
  tcase_add_test(tc, test_string_basic);
  tcase_add_test(tc, test_string_with_space);
  tcase_add_test(tc, test_string_empty);
  tcase_add_test(tc, test_string_percent);
  tcase_add_test(tc, test_string_percent_start);
}

void register_sscanf_char_tests(TCase *tc) {
  tcase_add_test(tc, test_char_basic);
  tcase_add_test(tc, test_char_digit);
  tcase_add_test(tc, test_char_special);
}

void register_sscanf_int_tests(TCase *tc) {
  tcase_add_test(tc, test_int_positive);
  tcase_add_test(tc, test_int_negative);
  tcase_add_test(tc, test_int_zero);
  tcase_add_test(tc, test_int_two);
  tcase_add_test(tc, test_int_three);
  tcase_add_test(tc, test_int_min_boundary);
  tcase_add_test(tc, test_int_max_boundary);
  tcase_add_test(tc, test_short_int);
  tcase_add_test(tc, test_long_int);
}

void register_sscanf_unsigned_tests(TCase *tc) {
  tcase_add_test(tc, test_u_simple);
  tcase_add_test(tc, test_u_zero);
}

void register_sscanf_octal_tests(TCase *tc) {
  tcase_add_test(tc, test_o_simple);
}

void register_sscanf_hex_tests(TCase *tc) {
  tcase_add_test(tc, test_x_simple);
  tcase_add_test(tc, test_x_zero);
}

void register_sscanf_float_tests(TCase *tc) {
  tcase_add_test(tc, test_zero_float);
  tcase_add_test(tc, test_positive_number_float);
  tcase_add_test(tc, test_negative_number_float);
}

void register_sscanf_pointer_tests(TCase *tc) {
  tcase_add_test(tc, test_p_simple);
  tcase_add_test(tc, test_p_zero_null);
}

void register_sscanf_mixed_tests(TCase *tc) {
  tcase_add_test(tc, test_mixed_string_int);
  tcase_add_test(tc, test_mixed_int_string);
}

void register_sscanf_percent_tests(TCase *tc) {
  tcase_add_test(tc, test_percent_simple);
  tcase_add_test(tc, test_percent_mixed);
}

Suite *sscanf_suite_create(void) {
  Suite *s = suite_create("s21_sscanf");
  TCase *tc_core = tcase_create("Core");
  
  register_sscanf_string_tests(tc_core);
  register_sscanf_char_tests(tc_core);
  register_sscanf_int_tests(tc_core);
  register_sscanf_unsigned_tests(tc_core);
  register_sscanf_octal_tests(tc_core);
  register_sscanf_hex_tests(tc_core);
  register_sscanf_float_tests(tc_core);
  register_sscanf_pointer_tests(tc_core);
  register_sscanf_mixed_tests(tc_core);
  register_sscanf_percent_tests(tc_core);
  
  suite_add_tcase(s, tc_core);
  return s;
}