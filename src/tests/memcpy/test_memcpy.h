#ifndef TEST_MEMCPY_H
#define TEST_MEMCPY_H

#include <check.h>
#include "../../s21_string.h"

// Структура параметров теста
typedef struct {
    const void *src;
    s21_size_t size;
    const char *test_name;
} MemCpyTestParams;

// Основная функция запуска теста
void run_memcpy_test(MemCpyTestParams *params);

// Функция создания suite (объявление)
Suite *memcpy_suite_create(void);

// Макрос для создания тестовых наборов
#define TEST_CASES(name, ...) \
    static MemCpyTestParams name[] = {__VA_ARGS__}; \
    START_TEST(test_##name) { \
        for (s21_size_t i = 0; i < sizeof(name)/sizeof(MemCpyTestParams); i++) { \
            run_memcpy_test(&name[i]); \
        } \
    } \
    END_TEST

#endif // TEST_MEMCPY_H