#include <check.h>
#include <stdlib.h>
#include "../s21_string.h"
#include <string.h>

#define CORRECT_CASES_NUM 5
#define EDGE_CASES_NUM 3

typedef struct {
    char *string;
    int chr;
    s21_size_t num;
} memsetParams;

static const memsetParams* get_correct_memset_case(int index) {
    // Массив изолирован внутри функции и невидим снаружи
    static const memsetParams cases[] = {
        {"apple", 'p', 3},
        {"verter", 'a', 4},
        {"alll", 'l', 1},
        {"supercalifragilisticexpialidocious", '\0', 34},
        {"Several words and 221 122 32", '1', 14}
    };
    return &cases[index];
}

static const memsetParams* get_edge_memset_case(int index) {
    // Массив изолирован внутри функции и невидим снаружи
    static const memsetParams cases[] = {
        {"apple", -1, 3},
        {"verter", 257, 4},
        {"alll", 'l', 0}
    };
    return &cases[index];
}

char* create_buffer(s21_size_t len, char* str) {
    char *buffer = malloc(len);
    strcpy(buffer, str);
    return buffer;
}

void test_memset_function(memsetParams current_case, char **res, char **expected, s21_size_t *len) {
    *len = strlen(current_case.string) + 1;
    char *buf_s21 = create_buffer(*len, current_case.string);
    char *buf_orig = create_buffer(*len, current_case.string);

    *res = s21_memset(buf_s21, current_case.chr, current_case.num);
    *expected = memset(buf_orig, current_case.chr, current_case.num);
}

START_TEST(test_memset_correct_input_orig_compare) {
    const memsetParams *current_case = get_correct_memset_case(_i);
    char *res = s21_NULL;
    char *expected = s21_NULL;
    s21_size_t len;
    test_memset_function(*current_case, &res, &expected, &len);

    ck_assert_mem_eq(res, expected, len);
}
END_TEST

START_TEST(test_memset_edge_input_orig_compare) {
    const memsetParams *current_case = get_edge_memset_case(_i);
    char *res = s21_NULL;
    char *expected = s21_NULL;
    s21_size_t len;
    test_memset_function(*current_case, &res, &expected, &len);

    ck_assert_mem_eq(res, expected, len);
}
END_TEST


// Функция, которую вызовет Runner
Suite *memset_suite_create(void) {
    Suite *s = suite_create("Memset");

    TCase *tc_correct = tcase_create("Correct_Input_Original_Compare");
    tcase_add_loop_test(tc_correct, test_memset_correct_input_orig_compare, 0, CORRECT_CASES_NUM);
    suite_add_tcase(s, tc_correct);

    TCase *tc_edge = tcase_create("Edge_Input_Original_Compare");
    tcase_add_loop_test(tc_edge, test_memset_edge_input_orig_compare, 0, EDGE_CASES_NUM);
    suite_add_tcase(s, tc_edge);


    return s;
}
