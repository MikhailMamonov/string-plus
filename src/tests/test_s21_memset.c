#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "../s21_string.h"

// Структура параметров теста
typedef struct {
    const void *data;
    int chr;
    s21_size_t num;
    s21_size_t data_size;
} memsetParams;

// Функция выделения буфера памяти
char* create_buffer(s21_size_t len, const void* str) {
    char *buffer = malloc(len);
    ck_assert_ptr_nonnull(buffer);
    memcpy(buffer, str, len);
    return buffer;
}

// Универсальная функция запуска одиночного теста
void run_memset_test(memsetParams *params) {
    s21_size_t len = params->data_size;
    char *buf_s21 = create_buffer(len, params->data);
    char *buf_orig = create_buffer(len, params->data);

    char *res = s21_memset(buf_s21, params->chr, params->num);
    char *expected = memset(buf_orig, params->chr, params->num);

    // Проверяем корректность заполнения всей области памяти буфера
    ck_assert_mem_eq(res, expected, len);

    free(buf_s21);
    free(buf_orig);
}

// Макрос для создания тестовых наборов
#define TEST_CASES(name, ...) \
    static memsetParams name[] = {__VA_ARGS__}; \
    START_TEST(test_##name) { \
        for (size_t i = 0; i < sizeof(name)/sizeof(name[0]); i++) { \
            run_memset_test(&name[i]); \
        } \
    } \
    END_TEST

// 1. Тесты на обычных строках
TEST_CASES(string_tests,
    {"apple", 'p', 3, 6},
    {"verter", 'a', 4, 7},
    {"alll", 'l', 1, 5},
    {"supercalifragilisticexpialidocious", '\0', 34, 35},
    {"Several words and 221 122 32", '1', 14, 29}
)

// 2. Тесты на массивах целых чисел (используются составные литералы)
TEST_CASES(int_tests,
    {(int[]){1, 2, 3, 4, 5}, '\0', 4 * sizeof(int) + 1, 5 * sizeof(int)},
    {(int[]){100, 200, 300}, 'b',  3 * sizeof(int),     3 * sizeof(int)},
    {(int[]){-1, -2, -3},    0,    3 * sizeof(int),     3 * sizeof(int)}
)

// 3. Пограничные и экстремальные случаи
TEST_CASES(edge_tests,
    {"apple", -1, 3, 6},
    {"verter", 257, 4, 7},
    {"alll", 'l', 0, 5}
)

// Функция сборки Suite для Runner
Suite *memset_suite_create(void) {
    Suite *s = suite_create("Memset");

    TCase *tc_string = tcase_create("String_Original_Compare");
    tcase_add_test(tc_string, test_string_tests);
    suite_add_tcase(s, tc_string);

    TCase *tc_int = tcase_create("Int_Original_Compare");
    tcase_add_test(tc_int, test_int_tests);
    suite_add_tcase(s, tc_int);

    TCase *tc_edge = tcase_create("Edge_Original_Compare");
    tcase_add_test(tc_edge, test_edge_tests);
    suite_add_tcase(s, tc_edge);

    return s;
}

