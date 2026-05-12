#include <check.h>
#include "../s21_string.h"
#include <string.h>

char *inputs_s[] = {"apple", "verter", "a", "supercalifragilisticexpialidocious", "Several words and 221 122 32"};
char inputs_c[] = {'p', 'a', 'f', '\0', '1'};
s21_size_t inputs_n[] = {3, 10, -1, 5, 14};

START_TEST(test_find) {
    // _i — это встроенная переменная индекса
    char *res = s21_memchr(inputs_s[_i], inputs_c[_i], inputs_n[_i]);
    char *expected = memchr(inputs_s[_i], inputs_c[_i], inputs_n[_i]);
    ck_assert_msg(res == expected,
        "Ошибка на итерации %d: ожидалось %p, получили %p",
        _i, expected, res);
}
END_TEST

// Функция, которую вызовет Runner
Suite *memchr_suite_create(void) {
    Suite *s = suite_create("Memchr");
    TCase *tc = tcase_create("Core");
    tcase_add_test(tc, test_find);
    suite_add_tcase(s, tc);
    return s;
}
