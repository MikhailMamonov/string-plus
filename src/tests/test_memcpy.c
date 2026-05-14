#include <check.h>
#include "../s21_string.h"
#include <string.h>
#include <stdio.h>

typedef struct {
    void * src;
    s21_size_t size;
    const char * test_name;
} MemCpyTestParams;

static const MemCpyTestParams test_inputs[] ={
    {"Hello, world.", 14, "basic_string"},
    {"Hello, world.", 5, "partial_5_bytes"},
    {"Hello, world.", 10, "partial_10_bytes" }
};

static const int num_tests = sizeof(test_inputs) / sizeof(test_inputs[0]);

void run_memcpy_test(void * dest_std, void * dest_test, void * src, s21_size_t size){
    s21_memcpy(dest_test, src , size);
    memcpy(dest_std, src , size);

    ck_assert_mem_eq(dest_test, dest_std, size);
}

START_TEST(test_memcpy_basic_string) {
    const MemCpyTestParams *params = &test_inputs[_i];
    char dest_std[20] = {0};
    char dest_test[20] = {0};

    run_memcpy_test(dest_std, dest_test, params->src, params->size);
}
END_TEST

START_TEST(test_memcpy_empty_string) {
    const MemCpyTestParams *params = &test_inputs[_i];
    char dest_std[20] = {0};
    char dest_test[20] = {0};

    run_memcpy_test(dest_std, dest_test, params->src, params->size);
}
END_TEST

START_TEST(test_memcpy_partial_copy) {
    printf("Running test_memcpy_basic_string with index: %d\n", _i);
    const MemCpyTestParams *params = &test_inputs[_i];
    char dest_std[20] = "XXXXXXXXXX";
    char dest_test[20] = "XXXXXXXXXX";
    run_memcpy_test(dest_std, dest_test, params->src, params->size);
}
END_TEST



// Функция, которую вызовет Runner
Suite *memcpy_suite_create(void) {
    Suite *s = suite_create("Memcpy");
    TCase *tc_positive = tcase_create("Positive");

    tcase_add_loop_test(tc_positive, test_memcpy_basic_string, 0, num_tests);
    tcase_add_loop_test(tc_positive, test_memcpy_empty_string, 0, num_tests);
    tcase_add_loop_test(tc_positive, test_memcpy_partial_copy, 0, num_tests);
    suite_add_tcase(s, tc_positive);
    return s;
}
