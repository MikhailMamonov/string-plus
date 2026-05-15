#include <check.h>
#include <stdlib.h>
#include "../s21_string.h"
#include <string.h>

#define STRING_CASES_NUM 5
#define INT_CASES_NUM 3
#define EDGE_CASES_NUM 3

typedef struct {
    const void *data;
    int chr;
    s21_size_t num;
    s21_size_t data_size;
} memsetParams;

static const memsetParams* get_string_memset_case(int index) {
    // Массив изолирован внутри функции и невидим снаружи
    static const memsetParams cases[] = {
        {"apple", 'p', 3, 6},
        {"verter", 'a', 4, 7},
        {"alll", 'l', 1, 5},
        {"supercalifragilisticexpialidocious", '\0', 34, 35},
        {"Several words and 221 122 32", '1', 14, 29}
    };
    return &cases[index];
}

static const memsetParams* get_int_memset_case(int index) {
    // 1. Создаем отдельные статические массивы для каждого тест-кейса
    static const int arr1[] = {1, 2, 3, 4, 5};
    static const int arr2[] = {100, 200, 300};
    static const int arr3[] = {-1, -2, -3};

    // 2. Инициализируем структуру, передавая указатели на эти массивы
    static const memsetParams cases[] = {
        {arr1, '\0', 4 * sizeof(int) + 1, sizeof(arr1)},
        {arr2, 'b',  3 * sizeof(int), sizeof(arr2)},
        {arr3, 0,    3 * sizeof(int), sizeof(arr3)}
    };
    return &cases[index];
}

static const memsetParams* get_edge_memset_case(int index) {
    // Массив изолирован внутри функции и невидим снаружи
    static const memsetParams cases[] = {
        {"apple", -1, 3, 6},
        {"verter", 257, 4, 7},
        {"alll", 'l', 0, 5}
    };
    return &cases[index];
}

char* create_buffer(s21_size_t len, const void* str) {
    char *buffer = malloc(len);
    ck_assert_ptr_nonnull(buffer);

    memcpy(buffer, str, len);
    return buffer;
}

void test_memset_function(memsetParams current_case, char **res, char **expected, s21_size_t *len) {
    *len = current_case.data_size;
    char *buf_s21 = create_buffer(*len, current_case.data);
    char *buf_orig = create_buffer(*len, current_case.data);

    *res = s21_memset(buf_s21, current_case.chr, current_case.num);
    *expected = memset(buf_orig, current_case.chr, current_case.num);
}

START_TEST(test_memset_string_orig_compare) {
    const memsetParams *current_case = get_string_memset_case(_i);
    char *res = s21_NULL;
    char *expected = s21_NULL;
    s21_size_t len;
    test_memset_function(*current_case, &res, &expected, &len);

    ck_assert_mem_eq(res, expected, len);
    free(res);
    free(expected);
}
END_TEST

START_TEST(test_memset_int_orig_compare) {
    const memsetParams *current_case = get_int_memset_case(_i);
    char *res = s21_NULL;
    char *expected = s21_NULL;
    s21_size_t len;
    test_memset_function(*current_case, &res, &expected, &len);

    ck_assert_mem_eq(res, expected, len);
    free(res);
    free(expected);
}
END_TEST

START_TEST(test_memset_edge_orig_compare) {
    const memsetParams *current_case = get_edge_memset_case(_i);
    char *res = s21_NULL;
    char *expected = s21_NULL;
    s21_size_t len;
    test_memset_function(*current_case, &res, &expected, &len);

    ck_assert_mem_eq(res, expected, len);
    free(res);
    free(expected);
}
END_TEST


// Функция, которую вызовет Runner
Suite *memset_suite_create(void) {
    Suite *s = suite_create("Memset");

    TCase *tc_correct = tcase_create("String_Original_Compare");
    tcase_add_loop_test(tc_correct, test_memset_string_orig_compare, 0, STRING_CASES_NUM);
    suite_add_tcase(s, tc_correct);

    TCase *tc_edge = tcase_create("Edge_Original_Compare");
    tcase_add_loop_test(tc_edge, test_memset_edge_orig_compare, 0, EDGE_CASES_NUM);
    suite_add_tcase(s, tc_edge);

    TCase *tc_int = tcase_create("Int_Original_Compare");
    tcase_add_loop_test(tc_int, test_memset_int_orig_compare, 0, INT_CASES_NUM);
    suite_add_tcase(s, tc_int);


    return s;
}
