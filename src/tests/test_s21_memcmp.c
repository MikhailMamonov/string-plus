#include <check.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../s21_string.h"

/*
 * Вспомогательный макрос: сравниваем именно знаки результатов
 * (стандарт C не гарантирует точные значения, только знак).
 */
#define ASSERT_SAME_SIGN(a, b) do { \
int _a = (a); \
int _b = (b); \
ck_assert_msg(((_a < 0 && _b < 0) || (_a == 0 && _b == 0) || (_a > 0 && _b > 0)), \
"Mismatch: s21=%d, std=%d", _a, _b); \
} while (0)

/* ====== 1. Базовые случаи ====== */

START_TEST(test_equal_strings) {
    const char *s1 = "Hello, World!";
    const char *s2 = "Hello, World!";
    size_t n = strlen(s1);
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, n), memcmp(s1, s2, n));
}
END_TEST

START_TEST(test_different_strings) {
    const char *s1 = "Hello, World!";
    const char *s2 = "Hello, world!";
    size_t n = strlen(s1);
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, n), memcmp(s1, s2, n));
}
END_TEST

START_TEST(test_first_byte_differs) {
    const char *s1 = "abcdef";
    const char *s2 = "Abcdef";
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 6), memcmp(s1, s2, 6));
}
END_TEST

START_TEST(test_last_byte_differs) {
    const char *s1 = "abcdef";
    const char *s2 = "abcdeF";
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 6), memcmp(s1, s2, 6));
}
END_TEST

START_TEST(test_middle_byte_differs) {
    const char *s1 = "abcdef";
    const char *s2 = "abCdef";
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 6), memcmp(s1, s2, 6));
}
END_TEST

/* ====== 2. n = 0 ====== */

START_TEST(test_zero_length) {
    const char *s1 = "abc";
    const char *s2 = "xyz";
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 0), memcmp(s1, s2, 0));
}
END_TEST

START_TEST(test_zero_length_empty_strings) {
    ASSERT_SAME_SIGN(s21_memcmp("", "", 0), memcmp("", "", 0));
}
END_TEST

/* ====== 3. n = 1 ====== */

START_TEST(test_one_byte_equal) {
    ASSERT_SAME_SIGN(s21_memcmp("A", "A", 1), memcmp("A", "A", 1));
}
END_TEST

START_TEST(test_one_byte_different) {
    ASSERT_SAME_SIGN(s21_memcmp("A", "B", 1), memcmp("A", "B", 1));
}
END_TEST

/* ====== 4. ЛОВУШКА: \0 в середине ====== */

START_TEST(test_null_byte_in_middle_equal) {
    const char s1[] = {'a', 'b', '\0', 'c', 'd'};
    const char s2[] = {'a', 'b', '\0', 'c', 'd'};
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 5), memcmp(s1, s2, 5));
}
END_TEST

START_TEST(test_null_byte_in_middle_diff_after) {
    const char s1[] = {'a', 'b', '\0', 'c', 'd'};
    const char s2[] = {'a', 'b', '\0', 'c', 'e'};
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 5), memcmp(s1, s2, 5));
}
END_TEST

START_TEST(test_null_byte_in_middle_diff_in_null) {
    const char s1[] = {'a', 'b', '\0', 'c', 'd'};
    const char s2[] = {'a', 'b', 'X',  'c', 'd'};
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 5), memcmp(s1, s2, 5));
}
END_TEST

START_TEST(test_only_null_bytes) {
    const char s1[] = {'\0', '\0', '\0', '\0'};
    const char s2[] = {'\0', '\0', '\0', '\0'};
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 4), memcmp(s1, s2, 4));
}
END_TEST

START_TEST(test_multiple_nulls_with_diff) {
    const char s1[] = {'\0', '\0', 'A', '\0'};
    const char s2[] = {'\0', '\0', 'B', '\0'};
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 4), memcmp(s1, s2, 4));
}
END_TEST

/* ====== 5. ЛОВУШКА: байты > 127 ====== */

START_TEST(test_high_byte_vs_low_byte) {
    unsigned char s1[] = {0xFF};
    unsigned char s2[] = {0x01};
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 1), memcmp(s1, s2, 1));
}
END_TEST

START_TEST(test_high_byte_vs_high_byte) {
    unsigned char s1[] = {0xFE};
    unsigned char s2[] = {0xFF};
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 1), memcmp(s1, s2, 1));
}
END_TEST

START_TEST(test_127_vs_128) {
    unsigned char s1[] = {0x7F};
    unsigned char s2[] = {0x80};
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 1), memcmp(s1, s2, 1));
}
END_TEST

START_TEST(test_cyrillic_strings_equal) {
    const char *s1 = "Привет, мир!";
    const char *s2 = "Привет, мир!";
    size_t n = strlen(s1);
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, n), memcmp(s1, s2, n));
}
END_TEST

START_TEST(test_cyrillic_strings_diff) {
    const char *s1 = "Привет";
    const char *s2 = "Превет";
    size_t n = strlen(s1);
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, n), memcmp(s1, s2, n));
}
END_TEST

START_TEST(test_ascii_vs_cyrillic) {
    const char *s1 = "A";
    const char *s2 = "Б";
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 1), memcmp(s1, s2, 1));
}
END_TEST

/* ====== 6. Бинарные данные ====== */

START_TEST(test_binary_data_equal) {
    unsigned char s1[] = {0x00, 0xFF, 0x7F, 0x80, 0x01, 0xAA};
    unsigned char s2[] = {0x00, 0xFF, 0x7F, 0x80, 0x01, 0xAA};
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 6), memcmp(s1, s2, 6));
}
END_TEST

START_TEST(test_binary_data_diff) {
    unsigned char s1[] = {0x00, 0xFF, 0x7F, 0x80, 0x01, 0xAA};
    unsigned char s2[] = {0x00, 0xFF, 0x7F, 0x80, 0x01, 0xAB};
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 6), memcmp(s1, s2, 6));
}
END_TEST

START_TEST(test_all_bytes_combinations) {
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            unsigned char a = (unsigned char)i;
            unsigned char b = (unsigned char)j;
            int r1 = s21_memcmp(&a, &b, 1);
            int r2 = memcmp(&a, &b, 1);
            ck_assert_msg(((r1 < 0 && r2 < 0) || (r1 == 0 && r2 == 0) || (r1 > 0 && r2 > 0)),
                          "Fail at %d vs %d: s21=%d, std=%d", i, j, r1, r2);
        }
    }
}
END_TEST

/* ====== 7. Частичное сравнение ====== */

START_TEST(test_partial_compare_equal_prefix) {
    const char *s1 = "abcXYZ";
    const char *s2 = "abcQRS";
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 3), memcmp(s1, s2, 3));
}
END_TEST

START_TEST(test_partial_compare_diff_in_range) {
    const char *s1 = "abcXYZ";
    const char *s2 = "abdQRS";
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 3), memcmp(s1, s2, 3));
}
END_TEST

/* ====== 8. Большие буферы ====== */

START_TEST(test_large_buffer_equal) {
    size_t size = 10000;
    char *s1 = malloc(size);
    char *s2 = malloc(size);
    memset(s1, 'A', size);
    memset(s2, 'A', size);
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, size), memcmp(s1, s2, size));
    free(s1);
    free(s2);
}
END_TEST

START_TEST(test_large_buffer_diff_at_end) {
    size_t size = 10000;
    char *s1 = malloc(size);
    char *s2 = malloc(size);
    memset(s1, 'A', size);
    memset(s2, 'A', size);
    s2[size - 1] = 'B';
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, size), memcmp(s1, s2, size));
    free(s1);
    free(s2);
}
END_TEST

START_TEST(test_large_buffer_diff_at_start) {
    size_t size = 10000;
    char *s1 = malloc(size);
    char *s2 = malloc(size);
    memset(s1, 'A', size);
    memset(s2, 'A', size);
    s2[0] = 'B';
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, size), memcmp(s1, s2, size));
    free(s1);
    free(s2);
}
END_TEST

START_TEST(test_large_buffer_diff_middle) {
    size_t size = 10000;
    char *s1 = malloc(size);
    char *s2 = malloc(size);
    memset(s1, 'A', size);
    memset(s2, 'A', size);
    s2[size / 2] = 'B';
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, size), memcmp(s1, s2, size));
    free(s1);
    free(s2);
}
END_TEST

/* ====== 9. Один и тот же указатель ====== */

START_TEST(test_same_pointer) {
    const char *s = "Some string";
    ASSERT_SAME_SIGN(s21_memcmp(s, s, strlen(s)), memcmp(s, s, strlen(s)));
}
END_TEST

/* ====== 10. Спецсимволы ====== */

START_TEST(test_special_chars) {
    const char *s1 = "\t\n\r\v\f\a";
    const char *s2 = "\t\n\r\v\f\a";
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 6), memcmp(s1, s2, 6));
}
END_TEST

START_TEST(test_special_chars_diff) {
    const char *s1 = "\t\n\r\v\f\a";
    const char *s2 = "\t\n\r\v\f\b";
    ASSERT_SAME_SIGN(s21_memcmp(s1, s2, 6), memcmp(s1, s2, 6));
}
END_TEST

/* ====== 11. Рандом ====== */

START_TEST(test_random_buffers) {
    srand(42);
    for (int iter = 0; iter < 1000; iter++) {
        size_t size = (rand() % 256) + 1;
        unsigned char *s1 = malloc(size);
        unsigned char *s2 = malloc(size);
        for (size_t i = 0; i < size; i++) {
            s1[i] = rand() % 256;
            s2[i] = rand() % 256;
        }
        int r1 = s21_memcmp(s1, s2, size);
        int r2 = memcmp(s1, s2, size);
        ck_assert_msg(((r1 < 0 && r2 < 0) || (r1 == 0 && r2 == 0) || (r1 > 0 && r2 > 0)),
                      "Random test failed at iter %d, size %zu: s21=%d, std=%d",
                      iter, size, r1, r2);
        free(s1);
        free(s2);
    }
}
END_TEST

/* ====== Сборка suite ====== */

Suite *s21_memcmp_suite_create(void) {
    Suite *s = suite_create("s21_memcmp");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, test_equal_strings);
    tcase_add_test(tc, test_different_strings);
    tcase_add_test(tc, test_first_byte_differs);
    tcase_add_test(tc, test_last_byte_differs);
    tcase_add_test(tc, test_middle_byte_differs);

    tcase_add_test(tc, test_zero_length);
    tcase_add_test(tc, test_zero_length_empty_strings);

    tcase_add_test(tc, test_one_byte_equal);
    tcase_add_test(tc, test_one_byte_different);

    tcase_add_test(tc, test_null_byte_in_middle_equal);
    tcase_add_test(tc, test_null_byte_in_middle_diff_after);
    tcase_add_test(tc, test_null_byte_in_middle_diff_in_null);
    tcase_add_test(tc, test_only_null_bytes);
    tcase_add_test(tc, test_multiple_nulls_with_diff);

    tcase_add_test(tc, test_high_byte_vs_low_byte);
    tcase_add_test(tc, test_high_byte_vs_high_byte);
    tcase_add_test(tc, test_127_vs_128);
    tcase_add_test(tc, test_cyrillic_strings_equal);
    tcase_add_test(tc, test_cyrillic_strings_diff);
    tcase_add_test(tc, test_ascii_vs_cyrillic);

    tcase_add_test(tc, test_binary_data_equal);
    tcase_add_test(tc, test_binary_data_diff);
    tcase_add_test(tc, test_all_bytes_combinations);

    tcase_add_test(tc, test_partial_compare_equal_prefix);
    tcase_add_test(tc, test_partial_compare_diff_in_range);

    tcase_add_test(tc, test_large_buffer_equal);
    tcase_add_test(tc, test_large_buffer_diff_at_end);
    tcase_add_test(tc, test_large_buffer_diff_at_start);
    tcase_add_test(tc, test_large_buffer_diff_middle);

    tcase_add_test(tc, test_same_pointer);
    tcase_add_test(tc, test_special_chars);
    tcase_add_test(tc, test_special_chars_diff);
    tcase_add_test(tc, test_random_buffers);

    tcase_set_timeout(tc, 10);

    suite_add_tcase(s, tc);
    return s;
}
