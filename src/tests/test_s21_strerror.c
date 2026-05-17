#include <string.h>
#include <stdlib.h>
#include <check.h>
#include <errno.h>
#include "../s21_string.h"

// Структура параметров теста
typedef struct {
    int errnum;
} strerrorParams;

// Вспомогательная функция проверки (сравниваем строки через стандартную strcmp)
void run_strerror_test(strerrorParams *params) {
    char *orig_res = strerror(params->errnum);
    char *s21_res = s21_strerror(params->errnum);

    // Проверяем, что строки идентичны
    ck_assert_str_eq(s21_res, orig_res);
}

// Макрос для автоматического создания цикла проверок
#define TEST_CASES(name, ...) \
    static strerrorParams name[] = {__VA_ARGS__}; \
    START_TEST(test_##name) { \
        for (size_t i = 0; i < sizeof(name)/sizeof(name[0]); i++) { \
            run_strerror_test(&name[i]); \
        } \
    } \
    END_TEST

// 1. Стандартные распространенные ошибки
TEST_CASES(standard_errors,
    {0},            // No error
    {EPERM},        // Operation not permitted (1)
    {ENOENT},       // No such file or directory (2)
    {ESRCH},        // No such process (3)
    {EINTR},        // Interrupted system call (4)
    {EACCES},       // Permission denied (13)
    {ENOMEM},       // Cannot allocate memory (12)
    {EINVAL}        // Invalid argument (22)
)

// 2. Граничные значения кодов операционной системы
TEST_CASES(edge_errors,
    {1},            // Минимальная стандартная ошибка
    {106},          // Системная ошибка из конца списка glibc/macOS
    {133}           // Последняя доступная ошибка на некоторых ОС
)

// 3. Невалидные и критические пограничные случаи (проверка "Unknown error")
TEST_CASES(invalid_errors,
    {-1},           // Отрицательный код ошибки
    {150},          // Несуществующая ошибка (в glibc/macOS их около 133)
    {1000},         // Большое невалидное число
    {2147483647}    // Максимальное значение int (INT_MAX)
)

// Функция сборки Suite для Runner
Suite *strerror_suite_create(void) {
    Suite *s = suite_create("strerror");

    TCase *tc_standard = tcase_create("Standard Errors");
    tcase_add_test(tc_standard, test_standard_errors);
    suite_add_tcase(s, tc_standard);

    TCase *tc_edge = tcase_create("Edge Errors");
    tcase_add_test(tc_edge, test_edge_errors);
    suite_add_tcase(s, tc_edge);

    TCase *tc_invalid = tcase_create("Invalid Errors");
    tcase_add_test(tc_invalid, test_invalid_errors);
    suite_add_tcase(s, tc_invalid);

    return s;
}
