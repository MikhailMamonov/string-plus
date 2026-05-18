
#ifndef TEST_COMMON_H
#define TEST_COMMON_H

<<<<<<< Updated upstream
=======
#ifndef INT_MAX
    #define INT_MAX 2147483647
#endif

#ifndef INT_MIN
    #define INT_MIN (-INT_MAX - 1)
#endif

>>>>>>> Stashed changes
// Структура параметров теста
typedef struct {
    const void *src;
    s21_size_t size;
    const char *test_name;
} MemCpyTestParams;


// Структура параметров теста
typedef struct {
    const void *src;
    s21_size_t size;
    const char *test_name;
} StrChrTestParams;


// Макрос для создания тестовых наборов
#define TEST_CASES(name,param_type ,run_func, ...) \
    static param_type name[] = {__VA_ARGS__}; \
    START_TEST(test_##name) { \
        for (s21_size_t i = 0; i < sizeof(name)/sizeof(param_type); i++) { \
            run_func(&name[i]); \
        } \
    } \
    END_TEST

#define MEMCPY_TEST_CASES(name, ...) \
    TEST_CASES(name, MemCpyTestParams, run_memcpy_test, __VA_ARGS__)

#define STRCHR_TEST_CASES(name, ...) \
    TEST_CASES(name, StrChrTestParams, run_strchr_test, __VA_ARGS__)

#endif