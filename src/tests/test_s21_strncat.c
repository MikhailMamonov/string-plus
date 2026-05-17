#include <check.h>
#include <string.h>
#include <stdlib.h>
#include "../s21_string.h"  // подключи свой заголовок

// ============================================================
// Базовые тесты: сравнение с эталонной strncat
// ============================================================

START_TEST(test_basic_concat) {
    char dest1[64] = "Hello, ";
    char dest2[64] = "Hello, ";
    const char *src = "World!";

    s21_strncat(dest1, src, 6);
    strncat(dest2, src, 6);

    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_concat_empty_src) {
    char dest1[64] = "Hello";
    char dest2[64] = "Hello";
    const char *src = "";

    s21_strncat(dest1, src, 10);
    strncat(dest2, src, 10);

    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_concat_to_empty_dest) {
    char dest1[64] = "";
    char dest2[64] = "";
    const char *src = "Hello";

    s21_strncat(dest1, src, 5);
    strncat(dest2, src, 5);

    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_concat_n_zero) {
    char dest1[64] = "Hello";
    char dest2[64] = "Hello";
    const char *src = "World";

    s21_strncat(dest1, src, 0);
    strncat(dest2, src, 0);

    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_concat_both_empty) {
    char dest1[64] = "";
    char dest2[64] = "";
    const char *src = "";

    s21_strncat(dest1, src, 5);
    strncat(dest2, src, 5);

    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_return_value) {
    char dest1[64] = "abc";
    char dest2[64] = "abc";
    const char *src = "def";

    char *res1 = s21_strncat(dest1, src, 3);
    char *res2 = strncat(dest2, src, 3);

    // Обе функции должны вернуть указатель на dest
    ck_assert_ptr_eq(res1, dest1);
    ck_assert_ptr_eq(res2, dest2);
    ck_assert_str_eq(res1, res2);
}
END_TEST

// ============================================================
// Ловушка №1: Терминатор конца строки
// Функция обязана всегда добавить '\0' в конец dest
// ============================================================

START_TEST(test_null_terminator_added) {
    // Заполняем dest "мусором", чтобы убедиться,
    // что '\0' действительно записывается
    char dest1[20];
    char dest2[20];
    memset(dest1, 'X', sizeof(dest1));
    memset(dest2, 'X', sizeof(dest2));
    dest1[0] = '\0';
    dest2[0] = '\0';

    const char *src = "ABC";

    s21_strncat(dest1, src, 3);
    strncat(dest2, src, 3);

    // Проверяем, что после "ABC" стоит '\0'
    ck_assert_int_eq(dest1[3], '\0');
    ck_assert_int_eq(dest2[3], '\0');
    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_null_terminator_when_n_limits) {
    // n меньше длины src — всё равно должен быть '\0' в конце
    char dest1[20];
    char dest2[20];
    memset(dest1, 'X', sizeof(dest1));
    memset(dest2, 'X', sizeof(dest2));
    dest1[0] = '\0';
    dest2[0] = '\0';

    const char *src = "Hello, World!";

    s21_strncat(dest1, src, 5);
    strncat(dest2, src, 5);

    // Скопировали 5 символов — '\0' должен быть на позиции 5
    ck_assert_int_eq(dest1[5], '\0');
    ck_assert_int_eq(dest2[5], '\0');
    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_null_terminator_after_existing_text) {
    char dest1[20];
    char dest2[20];
    memset(dest1, 'X', sizeof(dest1));
    memset(dest2, 'X', sizeof(dest2));
    strcpy(dest1, "Hi");
    strcpy(dest2, "Hi");

    const char *src = "There";

    s21_strncat(dest1, src, 5);
    strncat(dest2, src, 5);

    // "Hi" (2) + "There" (5) + '\0' = позиция 7
    ck_assert_int_eq(dest1[7], '\0');
    ck_assert_int_eq(dest2[7], '\0');
    ck_assert_str_eq(dest1, dest2);
}
END_TEST

// ============================================================
// Ловушка №2: Длина src меньше, чем n
// Функция должна остановиться на '\0' src,
// НЕ дозаполнять нулями (в отличие от strncpy)
// ============================================================

START_TEST(test_src_shorter_than_n) {
    char dest1[30];
    char dest2[30];
    memset(dest1, 'Z', sizeof(dest1));
    memset(dest2, 'Z', sizeof(dest2));
    strcpy(dest1, "Start:");
    strcpy(dest2, "Start:");

    const char *src = "ABC";  // длина 3
    volatile size_t vn = 100; // прячем константу от статического анализа
    size_t n = vn;

    s21_strncat(dest1, src, n);
    strncat(dest2, src, n);

    ck_assert_str_eq(dest1, "Start:ABC");
    ck_assert_str_eq(dest2, "Start:ABC");
    ck_assert_str_eq(dest1, dest2);

    // "Start:" (6) + "ABC" (3) + '\0' (1) = 10
    ck_assert_int_eq(dest1[10], 'Z');
    ck_assert_int_eq(dest2[10], 'Z');
}
END_TEST

START_TEST(test_src_shorter_no_overwrite) {
    char dest1[20];
    char dest2[20];
    memset(dest1, 'M', sizeof(dest1));
    memset(dest2, 'M', sizeof(dest2));
    dest1[0] = '\0';
    dest2[0] = '\0';

    const char *src = "Hi";   // длина 2
    volatile size_t vn = 10;
    size_t n = vn;

    s21_strncat(dest1, src, n);
    strncat(dest2, src, n);

    ck_assert_str_eq(dest1, "Hi");
    ck_assert_str_eq(dest2, "Hi");

    for (int i = 3; i < 10; i++) {
        ck_assert_int_eq(dest1[i], 'M');
        ck_assert_int_eq(dest2[i], 'M');
    }
}
END_TEST

START_TEST(test_src_exact_length_as_n) {
    char dest1[20] = "X:";
    char dest2[20] = "X:";
    const char *src = "abc";  // длина 3
    size_t n = 3;             // n == strlen(src)

    s21_strncat(dest1, src, n);
    strncat(dest2, src, n);

    ck_assert_str_eq(dest1, "X:abc");
    ck_assert_str_eq(dest2, "X:abc");
    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_n_smaller_than_src) {
    char dest1[20] = "X:";
    char dest2[20] = "X:";
    const char *src = "abcdef";
    size_t n = 3;  // копируем только "abc"

    s21_strncat(dest1, src, n);
    strncat(dest2, src, n);

    ck_assert_str_eq(dest1, "X:abc");
    ck_assert_str_eq(dest2, "X:abc");
    ck_assert_str_eq(dest1, dest2);
}
END_TEST

// ============================================================
// Дополнительные тесты с особыми символами
// ============================================================

START_TEST(test_special_chars) {
    char dest1[64] = "Tab:";
    char dest2[64] = "Tab:";
    const char *src = "\t\n\r";

    s21_strncat(dest1, src, 3);
    strncat(dest2, src, 3);

    ck_assert_str_eq(dest1, dest2);
    ck_assert_int_eq(dest1[7], '\0');
}
END_TEST

START_TEST(test_long_strings) {
    char dest1[256] = "Lorem ipsum ";
    char dest2[256] = "Lorem ipsum ";
    const char *src =
    "dolor sit amet, consectetur adipiscing elit, "
    "sed do eiusmod tempor incididunt ut labore.";

    s21_strncat(dest1, src, 50);
    strncat(dest2, src, 50);

    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_single_char) {
    char dest1[10] = "A";
    char dest2[10] = "A";
    const char *src = "B";

    s21_strncat(dest1, src, 1);
    strncat(dest2, src, 1);

    ck_assert_str_eq(dest1, "AB");
    ck_assert_str_eq(dest2, "AB");
    ck_assert_int_eq(dest1[2], '\0');
}
END_TEST

// ============================================================
// Сборка набора тестов
// ============================================================

Suite *strncat_suite_create(void) {
    Suite *s = suite_create("s21_strncat");

    TCase *tc_basic = tcase_create("Basic");
    tcase_add_test(tc_basic, test_basic_concat);
    tcase_add_test(tc_basic, test_concat_empty_src);
    tcase_add_test(tc_basic, test_concat_to_empty_dest);
    tcase_add_test(tc_basic, test_concat_n_zero);
    tcase_add_test(tc_basic, test_concat_both_empty);
    tcase_add_test(tc_basic, test_return_value);
    suite_add_tcase(s, tc_basic);

    TCase *tc_null = tcase_create("NullTerminator");
    tcase_add_test(tc_null, test_null_terminator_added);
    tcase_add_test(tc_null, test_null_terminator_when_n_limits);
    tcase_add_test(tc_null, test_null_terminator_after_existing_text);
    suite_add_tcase(s, tc_null);

    TCase *tc_short = tcase_create("SrcShorterThanN");
    tcase_add_test(tc_short, test_src_shorter_than_n);
    tcase_add_test(tc_short, test_src_shorter_no_overwrite);
    tcase_add_test(tc_short, test_src_exact_length_as_n);
    tcase_add_test(tc_short, test_n_smaller_than_src);
    suite_add_tcase(s, tc_short);

    TCase *tc_extra = tcase_create("Extra");
    tcase_add_test(tc_extra, test_special_chars);
    tcase_add_test(tc_extra, test_long_strings);
    tcase_add_test(tc_extra, test_single_char);
    suite_add_tcase(s, tc_extra);

    return s;
}
