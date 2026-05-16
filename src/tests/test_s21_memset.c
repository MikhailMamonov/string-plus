#include <check.h>
#include <stdlib.h>
#include "../s21_string.h"
#include <string.h>

char *memset_correct_inputs_s[] = {"apple", "verter", "alll", "supercalifragilisticexpialidocious", "Several words and 221 122 32"};
int memset_correct_inputs_c[] = {'p', 'a', 'l', '\0', '1'};
s21_size_t memset_correct_inputs_n[] = {3, 4, 1, 34, 14};

START_TEST(test_memset_correct_input_orig_compare) {
    // 1. Создаем два изменяемых буфера в стеке под текущую строку
    // Выделяем память с запасом (+1 для '\0')
    s21_size_t len = strlen(memset_correct_inputs_s[_i]) + 1;
    char *buf_s21 = malloc(len);
    char *buf_orig = malloc(len);

    // Копируем неизменяемый литерал в наши изменяемые буферы
    strcpy(buf_s21, memset_correct_inputs_s[_i]);
    strcpy(buf_orig, memset_correct_inputs_s[_i]);

    // 2. Вызываем функции на изменяемой памяти
    char *res = s21_memset(buf_s21, memset_correct_inputs_c[_i], memset_correct_inputs_n[_i]);
    char *expected = memset(buf_orig, memset_correct_inputs_c[_i], memset_correct_inputs_n[_i]);

    // 3. Проверяем результат
    // Важно: сравнивать нужно не только указатели (они будут разными адресами malloc),
    // а содержимое памяти! Используем ck_assert_mem_eq, так как в c может быть '\0'
    ck_assert_mem_eq(res, expected, len);

    // 4. Обязательно освобождаем память
    free(buf_s21);
    free(buf_orig);
}
END_TEST


char *memset_edge_inputs_s[] = {"apple", "verter", "alll"};
int memset_edge_inputs_c[] = {-1, 257, 'l'};
s21_size_t memset_edge_inputs_n[] = {3, 4, 0};

START_TEST(test_memset_edge_input_orig_compare) {
    // 1. Создаем два изменяемых буфера в стеке под текущую строку
    // Выделяем память с запасом (+1 для '\0')
    s21_size_t len = strlen(memset_edge_inputs_s[_i]) + 1;
    char *buf_s21 = malloc(len);
    char *buf_orig = malloc(len);

    // Копируем неизменяемый литерал в наши изменяемые буферы
    strcpy(buf_s21, memset_edge_inputs_s[_i]);
    strcpy(buf_orig, memset_edge_inputs_s[_i]);

    // 2. Вызываем функции на изменяемой памяти
    char *res = s21_memset(buf_s21, memset_edge_inputs_c[_i], memset_edge_inputs_n[_i]);
    char *expected = memset(buf_orig, memset_edge_inputs_c[_i], memset_edge_inputs_n[_i]);

    // 3. Проверяем результат
    // Важно: сравнивать нужно не только указатели (они будут разными адресами malloc),
    // а содержимое памяти! Используем ck_assert_mem_eq, так как в c может быть '\0'
    ck_assert_mem_eq(res, expected, len);

    // 4. Обязательно освобождаем память
    free(buf_s21);
    free(buf_orig);
}
END_TEST


// Функция, которую вызовет Runner
Suite *memset_suite_create(void) {
    Suite *s = suite_create("Memset");

    TCase *tc_correct = tcase_create("Correct_Input_Original_Compare");
    tcase_add_loop_test(tc_correct, test_memset_correct_input_orig_compare, 0, (int)(sizeof(memset_correct_inputs_s) / sizeof(memset_correct_inputs_s[0])));
    suite_add_tcase(s, tc_correct);

    TCase *tc_edge = tcase_create("Edge_Input_Original_Compare");
    tcase_add_loop_test(tc_edge, test_memset_edge_input_orig_compare, 0, (int)(sizeof(memset_edge_inputs_s) / sizeof(memset_edge_inputs_s[0])));
    suite_add_tcase(s, tc_edge);


    return s;
}
