
#ifndef TEST_COMMON_H
#define TEST_COMMON_H

// Структура параметров теста
typedef struct {
    const void *src;
    s21_size_t size;
    const char *test_name;
} MemCpyTestParams;


// Структура параметров теста
typedef struct {
    const char *str;
    int c;
    const char *test_name;
} StrChrTestParams;

// Структура параметров теста
typedef struct {
    const void *data;
    int chr;
    s21_size_t num;
    s21_size_t data_size;
} memsetParams;

typedef struct {
    const void *str;
    int c;
    s21_size_t n;
} memchrParams;

// Структура параметров теста
typedef struct {
    int errnum;
} strerrorParams;

// Структура параметров теста
typedef struct {
    const char *str1;
    const char *str2;
    s21_size_t n;
} strncmpParams;

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

#define MEMSET_TEST_CASES(name, ...) \
    TEST_CASES(name, memsetParams, run_memset_test, __VA_ARGS__)

#define MEMCHR_TEST_CASES(name, ...) \
    TEST_CASES(name, memchrParams, run_memchr_test, __VA_ARGS__)

#define STRERROR_TEST_CASES(name, ...) \
    TEST_CASES(name, strerrorParams, run_strerror_test, __VA_ARGS__)

#define STRNCMP_TEST_CASES(name, ...) \
    TEST_CASES(name, strncmpParams, run_strncmp_test, __VA_ARGS__)

#endif
