#include <check.h>
#include "../s21_string.h"
#include <string.h>

char *memchr_inputs_s[] = {"apple", "verter", "a", "supercalifragilisticexpialidocious", "Several words and 221 122 32"};
char memchr_inputs_c[] = {'p', 'a', 'f', '\0', ' '};
s21_size_t memchr_inputs_n[] = {3, 5, 0, 5, 14};

START_TEST(test_find) {
    // _i — это встроенная переменная индекса
    char *res = s21_memchr(memchr_inputs_s[_i], memchr_inputs_c[_i], memchr_inputs_n[_i]);
    char *expected = memchr(memchr_inputs_s[_i], memchr_inputs_c[_i], memchr_inputs_n[_i]);
    ck_assert_msg(res == expected,
        "Ошибка на итерации %d: ожидалось %p, получили %p",
        _i, expected, res);
}
END_TEST

// Функция, которую вызовет Runner
Suite *memchr_suite_create(void) {
    Suite *s = suite_create("Memchr");
    TCase *tc = tcase_create("Core");
    tcase_add_loop_test(tc, test_find, 0, 5);
    suite_add_tcase(s, tc);
    return s;
}
