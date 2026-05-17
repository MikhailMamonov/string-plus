#include <check.h>
#include <string.h>
#include <stdlib.h>

#include "../s21_string.h"

/* ============================================================
 *  ЛОВУШКА 1: ПУСТАЯ СТРОКА
 *  ""  →  должна мгновенно вернуть 0.
 * ============================================================ */

START_TEST(test_empty_string_literal) {
    const char *src = "";
    ck_assert_uint_eq(s21_strlen(src), 0);
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(test_empty_string_array) {
    /* Массив, начинающийся с '\0' */
    char src[10] = {'\0'};
    ck_assert_uint_eq(s21_strlen(src), 0);
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(test_empty_then_garbage) {
    /* После '\0' идут другие символы — они НЕ должны считаться */
    char src[10];
    memset(src, 'X', sizeof(src));
    src[0] = '\0';

    ck_assert_uint_eq(s21_strlen(src), 0);
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

/* ============================================================
 *  ЛОВУШКА 2: UTF-8 / МНОГОБАЙТОВЫЕ СТРОКИ
 *  strlen считает БАЙТЫ, а не символы.
 *  s21_strlen должен вести себя так же.
 * ============================================================ */

/* Кириллица: каждый символ в UTF-8 занимает 2 байта.
 *  "Привет" → 6 символов × 2 байта = 12 байт. */
START_TEST(test_utf8_cyrillic) {
    const char *src = "Привет";

    size_t expected = strlen(src);          /* эталон от libc */
    ck_assert_uint_eq(s21_strlen(src), expected);
    ck_assert_uint_eq(s21_strlen(src), 12); /* явная проверка */
}
END_TEST

/* Смесь ASCII + кириллица */
START_TEST(test_utf8_mixed_ascii_cyrillic) {
    const char *src = "Hello, Мир!";
    /* "Hello, " = 7 байт, "Мир" = 6 байт, "!" = 1 байт → 14 */

    ck_assert_uint_eq(s21_strlen(src), strlen(src));
    ck_assert_uint_eq(s21_strlen(src), 14);
}
END_TEST

/* Эмодзи: 4-байтовая последовательность UTF-8.
 *  "😀" → 4 байта. */
START_TEST(test_utf8_emoji) {
    const char *src = "😀";
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
    ck_assert_uint_eq(s21_strlen(src), 4);
}
END_TEST

/* Несколько эмодзи подряд */
START_TEST(test_utf8_emoji_multiple) {
    const char *src = "😀😀😀"; /* 3 × 4 = 12 байт */
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
    ck_assert_uint_eq(s21_strlen(src), 12);
}
END_TEST

/* 3-байтовые символы: китайские иероглифы.
 *  "中文" → 2 × 3 = 6 байт. */
START_TEST(test_utf8_three_byte) {
    const char *src = "中文";
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
    ck_assert_uint_eq(s21_strlen(src), 6);
}
END_TEST

/* Символы с диакритикой: "é" в UTF-8 — 2 байта (0xC3 0xA9) */
START_TEST(test_utf8_two_byte_latin) {
    const char *src = "café"; /* 'c','a','f' = 3 байта + 'é' = 2 → 5 байт */
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
    ck_assert_uint_eq(s21_strlen(src), 5);
}
END_TEST

/* ============================================================
 *  СТАНДАРТНЫЕ СЛУЧАИ ASCII
 * ============================================================ */

START_TEST(test_ascii_one_char) {
    const char *src = "A";
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
    ck_assert_uint_eq(s21_strlen(src), 1);
}
END_TEST

START_TEST(test_ascii_simple_word) {
    const char *src = "hello";
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
    ck_assert_uint_eq(s21_strlen(src), 5);
}
END_TEST

START_TEST(test_ascii_with_spaces) {
    const char *src = "hello world";
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
    ck_assert_uint_eq(s21_strlen(src), 11);
}
END_TEST

START_TEST(test_ascii_with_special_chars) {
    const char *src = "!@#$%^&*()_+-=[]{}|;:,.<>?/";
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(test_ascii_with_escape_chars) {
    const char *src = "line1\nline2\ttab\\backslash";
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

/* ============================================================
 *  КРАЕВЫЕ И БОЛЬШИЕ СЛУЧАИ
 * ============================================================ */

/* Один пробел — длина 1 */
START_TEST(test_single_space) {
    const char *src = " ";
    ck_assert_uint_eq(s21_strlen(src), 1);
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

/* Только '\0' в середине — должно остановиться на первом */
START_TEST(test_embedded_null) {
    char src[10] = {'a', 'b', 'c', '\0', 'd', 'e', 'f', '\0'};
    /* strlen считает до первого '\0' → 3 */
    ck_assert_uint_eq(s21_strlen(src), 3);
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

/* Длинная ASCII-строка */
START_TEST(test_long_ascii) {
    char src[1001];
    memset(src, 'a', 1000);
    src[1000] = '\0';

    ck_assert_uint_eq(s21_strlen(src), 1000);
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

/* Очень длинная строка — проверка корректности на больших объёмах */
START_TEST(test_very_long_string) {
    size_t len = 100000;
    char *src = malloc(len + 1);
    ck_assert_ptr_nonnull(src);

    memset(src, 'Z', len);
    src[len] = '\0';

    ck_assert_uint_eq(s21_strlen(src), len);
    ck_assert_uint_eq(s21_strlen(src), strlen(src));

    free(src);
}
END_TEST

/* Строка из непечатаемых символов (но не '\0') */
START_TEST(test_non_printable) {
    char src[] = {0x01, 0x02, 0x03, 0x7F, '\0'};
    ck_assert_uint_eq(s21_strlen(src), 4);
    ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

/* Содержимое — байты со значением >127 (как в UTF-8) без '\0' внутри */
START_TEST(test_high_bytes) {
    char src[] = {(char)0xC3, (char)0xA9,       /* é */
        (char)0xE4, (char)0xB8, (char)0xAD, /* 中 */
        '\0'};
        ck_assert_uint_eq(s21_strlen(src), 5);
        ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

/* ============================================================
 *  СБОРКА SUITE
 * ============================================================ */

Suite *strlen_suite_create(void) {
    Suite *s = suite_create("s21_strlen");

    TCase *tc_empty = tcase_create("Empty strings");
    tcase_add_test(tc_empty, test_empty_string_literal);
    tcase_add_test(tc_empty, test_empty_string_array);
    tcase_add_test(tc_empty, test_empty_then_garbage);
    suite_add_tcase(s, tc_empty);

    TCase *tc_utf8 = tcase_create("UTF-8 / multibyte (byte count)");
    tcase_add_test(tc_utf8, test_utf8_cyrillic);
    tcase_add_test(tc_utf8, test_utf8_mixed_ascii_cyrillic);
    tcase_add_test(tc_utf8, test_utf8_emoji);
    tcase_add_test(tc_utf8, test_utf8_emoji_multiple);
    tcase_add_test(tc_utf8, test_utf8_three_byte);
    tcase_add_test(tc_utf8, test_utf8_two_byte_latin);
    tcase_add_test(tc_utf8, test_high_bytes);
    suite_add_tcase(s, tc_utf8);

    TCase *tc_ascii = tcase_create("ASCII");
    tcase_add_test(tc_ascii, test_ascii_one_char);
    tcase_add_test(tc_ascii, test_ascii_simple_word);
    tcase_add_test(tc_ascii, test_ascii_with_spaces);
    tcase_add_test(tc_ascii, test_ascii_with_special_chars);
    tcase_add_test(tc_ascii, test_ascii_with_escape_chars);
    suite_add_tcase(s, tc_ascii);

    TCase *tc_edge = tcase_create("Edge cases");
    tcase_add_test(tc_edge, test_single_space);
    tcase_add_test(tc_edge, test_embedded_null);
    tcase_add_test(tc_edge, test_long_ascii);
    tcase_add_test(tc_edge, test_very_long_string);
    tcase_add_test(tc_edge, test_non_printable);
    suite_add_tcase(s, tc_edge);

    return s;
}
