#include <check.h>
#include "../s21_string.h"
#include <string.h>
#include <signal.h>

char *memchr_positive_inputs_s[] = {"apple", "verter", "aaa", "supercalifragilisticexpialidocious", "Several words and 221 122 32"};
char memchr_positive_inputs_c[] = {'p', 'r', 'a', 'u', ' '};
s21_size_t memchr_positive_inputs_n[] = {3, 6, 3, 35, 14};

START_TEST(test_memchr_positive_orig_compare) {
    // _i — это встроенная переменная индекса
    char *res = s21_memchr(memchr_positive_inputs_s[_i], memchr_positive_inputs_c[_i], memchr_positive_inputs_n[_i]);
    char *expected = memchr(memchr_positive_inputs_s[_i], memchr_positive_inputs_c[_i], memchr_positive_inputs_n[_i]);
    ck_assert_msg(res == expected,
        "Ошибка на итерации %d: ожидалось %p, получили %p",
        _i, expected, res);
}
END_TEST


char *memchr_negative_inputs_s[] = {"apple", "verter", "a", "supercalifragilisticexpialidocious", "Several words and 221 122 32", "Spare test"};
char memchr_negative_inputs_c[] = {'p', 'a', 'l', 'c', ' ', '\0'};
s21_size_t memchr_negative_inputs_n[] = {1, 6, 1, 4, 7, 5};

START_TEST(test_memchr_negative_orig_compare) {
    // _i — это встроенная переменная индекса
    char *res = s21_memchr(memchr_negative_inputs_s[_i], memchr_negative_inputs_c[_i], memchr_negative_inputs_n[_i]);
    char *expected = memchr(memchr_negative_inputs_s[_i], memchr_negative_inputs_c[_i], memchr_negative_inputs_n[_i]);
    ck_assert_msg(res == expected,
        "Ошибка на итерации %d: ожидалось %p, получили %p",
        _i, expected, res);
}
END_TEST

char *memchr_edge_inputs_s[] = {"", "", "a", "supercalifragilisticexpialidocious/", "Spare test"};
char memchr_edge_inputs_c[] = {'\0', '\n', '\0', '/', '\0'};
s21_size_t memchr_edge_inputs_n[] = {1, 0, 1, 35, 11};

START_TEST(test_memchr_edge_orig_compare) {
    // _i — это встроенная переменная индекса
    char *res = s21_memchr(memchr_edge_inputs_s[_i], memchr_edge_inputs_c[_i], memchr_edge_inputs_n[_i]);
    char *expected = memchr(memchr_edge_inputs_s[_i], memchr_edge_inputs_c[_i], memchr_edge_inputs_n[_i]);
    ck_assert_msg(res == expected,
        "Ошибка на итерации %d: ожидалось %p, получили %p",
        _i, expected, res);
}
END_TEST


// Функция, которую вызовет Runner
Suite *memchr_suite_create(void) {
    Suite *s = suite_create("Memchr");

    TCase *tc_pos = tcase_create("Positive_Original_Compare");
    tcase_add_loop_test(tc_pos, test_memchr_positive_orig_compare, 0, (int)(sizeof(memchr_positive_inputs_s) / sizeof(memchr_positive_inputs_s[0])));
    suite_add_tcase(s, tc_pos);

    TCase *tc_neg = tcase_create("Negative_Original_Compare");
    tcase_add_loop_test(tc_neg, test_memchr_negative_orig_compare, 0, (int)(sizeof(memchr_negative_inputs_s) / sizeof(memchr_negative_inputs_s[0])));
    suite_add_tcase(s, tc_neg);

    TCase *tc_edge = tcase_create("Edge_Original_Compare");
    tcase_add_loop_test(tc_edge, test_memchr_edge_orig_compare, 0, (int)(sizeof(memchr_edge_inputs_s) / sizeof(memchr_edge_inputs_s[0])));
    suite_add_tcase(s, tc_edge);

    return s;
}
