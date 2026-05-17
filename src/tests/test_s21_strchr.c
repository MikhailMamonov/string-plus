#include <string.h>
#include <check.h>
#include "../s21_string.h"
#include "s21_test_common.h"


static const char ext_ascii_str1[] = { 'a', 'b', 'c', 0x80, 0x81, 'd', 'e', 'f', '\0' };
static const char ext_ascii_str2[] = { 'a', 'b', 'c', 0xFF, 'd', 'e', 'f', '\0' };
static const char long_str_middle[500] = 
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaacaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaacaaaaaaaaaaaaaaaaaaaa"; 
// Публичная функция запуска теста
void run_strchr_test(StrChrTestParams *params) {
    
    char *result_test = s21_strchr(params->str, params->c);
    char *result_std = strchr(params->str, params->c);

    // Проверяем всю область памяти, включая границы с паттерном 0xAA
    ck_assert_ptr_eq(result_test, result_std);
}



STRCHR_TEST_CASES(strchr_base_tests,
    {"Hello",'H' ,  "Existed char in start"},
    {"Hello, world.",'w', "Existed char in middle."},
    {"World", 'd', "Existed char in end."},
    {"abracadabra", 'a', "Repeated char in str." },
    {"Hello, world.",'\0' , "Search null terminator."},
)

STRCHR_TEST_CASES(strchr_symbol_not_found,
    {"Hello",'x' ,  "Not existed char not found."},
)

STRCHR_TEST_CASES(strchr_empty_string,
    {"", 'x', "symbol not found."},
    {"", '\0', "null terminator found."},
)

STRCHR_TEST_CASES(strchr_case_sensitive,
    {"Hello World", 'h', "symbol not existed ."},
    {"Hello World", 'H', "symbol existed."},
)

STRCHR_TEST_CASES(strchr_negative_char,
    {"Hello World", -1, "symbol not existed ."},
    {"Hello World", -100, "symbol existed."},
)

STRCHR_TEST_CASES(strchr_long_string_middle,
    {long_str_middle, 'c', "c char in middle long string."},
    {"Hello World", -100, "symbol existed."},
)

STRCHR_TEST_CASES(strchr_long_string_beginning,
    {
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", 
        'b', "long string with char at the very end."
    },
    { 
        "baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 
        'b', "long string with char at the very beginning."
    },
)

STRCHR_TEST_CASES(strchr_integer_ascii_values,
    {"Hello", 72, "ASCII 'H' (72) - Existed symbol"},
    {"Hello", 101, "ASCII 'e' (101) - Existed symbol"},
    {"Hello", 111, "ASCII 'o' (111) - Existed symbol"},
    {"Hello", 120, "ASCII 'x' (120) - Not existed symbol"},
    {"Hello", 0, "NULL terminator (0)"},
)

START_TEST(test_strchr_extended_ascii_bytes) {
    // Тест 1: поиск 0x80
    char *result_test = s21_strchr(ext_ascii_str1, 0x80);
    char *result_std = strchr(ext_ascii_str1, 0x80);
    ck_assert_ptr_eq(result_test, result_std);
    
    // Тест 2: поиск 0x81
    result_test = s21_strchr(ext_ascii_str1, 0x81);
    result_std = strchr(ext_ascii_str1, 0x81);
    ck_assert_ptr_eq(result_test, result_std);
    
    // Тест 3: поиск 0xFF
    result_test = s21_strchr(ext_ascii_str2, 0xFF);
    result_std = strchr(ext_ascii_str2, 0xFF);
    ck_assert_ptr_eq(result_test, result_std);
    
    // Тест 4: поиск несуществующего символа
    result_test = s21_strchr(ext_ascii_str1, 0x90);
    result_std = strchr(ext_ascii_str1, 0x90);
    ck_assert_ptr_eq(result_test, result_std);
    ck_assert_ptr_null(result_test);
}
END_TEST

// Заменяем тесты с hex на отдельные тесты
START_TEST(test_strchr_integer_extended_ascii_bytes) {
    // Тест 1: 128 (0x80)
    char *result_test = s21_strchr(ext_ascii_str1, 128);
    char *result_std = strchr(ext_ascii_str1, 128);
    ck_assert_ptr_eq(result_test, result_std);
    ck_assert_ptr_eq(result_test, ext_ascii_str1 + 3);
    
    // Тест 2: 129 (0x81)
    result_test = s21_strchr(ext_ascii_str1, 129);
    result_std = strchr(ext_ascii_str1, 129);
    ck_assert_ptr_eq(result_test, result_std);
    ck_assert_ptr_eq(result_test, ext_ascii_str1 + 4);
    
    // Тест 3: 255 (0xFF)
    result_test = s21_strchr(ext_ascii_str2, 255);
    result_std = strchr(ext_ascii_str2, 255);
    ck_assert_ptr_eq(result_test, result_std);
    ck_assert_ptr_eq(result_test, ext_ascii_str2 + 3);
    
    // Тест 4: 200 - не найден
    result_test = s21_strchr(ext_ascii_str1, 200);
    result_std = strchr(ext_ascii_str1, 200);
    ck_assert_ptr_eq(result_test, result_std);
    ck_assert_ptr_null(result_test);
}
END_TEST


// Функция, которую вызовет Runner
Suite *strchr_suite_create(void) {
    Suite *s = suite_create("strchr");
    
    TCase *tc_string = tcase_create("String tests");
    tcase_add_test(tc_string, test_strchr_base_tests);
    tcase_add_test(tc_string, test_strchr_symbol_not_found);
    tcase_add_test(tc_string, test_strchr_empty_string);
    tcase_add_test(tc_string, test_strchr_extended_ascii_bytes);
    tcase_add_test(tc_string, test_strchr_case_sensitive);
    suite_add_tcase(s, tc_string);
    
    TCase *tc_int = tcase_create("Integer tests");
    tcase_add_test(tc_int, test_strchr_integer_ascii_values);
    tcase_add_test(tc_int, test_strchr_integer_extended_ascii_bytes);
    tcase_add_test(tc_int, test_strchr_negative_char);
    suite_add_tcase(s, tc_int);
    
    TCase *tc_edge = tcase_create("Edge tests");
    tcase_add_test(tc_edge, test_strchr_long_string_middle);
    tcase_add_test(tc_edge, test_strchr_long_string_beginning);
    suite_add_tcase(s, tc_edge);
    
    return s;
}
