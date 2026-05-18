
#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#ifndef INT_MAX
    #define INT_MAX 2147483647
#endif

#ifndef INT_MIN
    #define INT_MIN (-INT_MAX - 1)
#endif

typedef struct {
    const void *src;
    s21_size_t size;
    const char *test_name;
} MemCpyTestParams;

typedef struct {
    const char *str;
    int c;
    const char *test_name;
} StrChrTestParams;

typedef struct {
    const char *str1;
    const char *str2;
    const char *test_name;
} StrCSpnTestParams;


// Макрос определения правильный формат для s21_size_t
#if defined(__APPLE__) || defined(__linux__)
    #define S21_SIZE_T_FMT "%zu"
#elif defined(_WIN32) || defined(_WIN64)
    #ifdef __MINGW64__
        #define S21_SIZE_T_FMT "%I64u"
    #else
        #define S21_SIZE_T_FMT "%llu"
    #endif
#else
    #define S21_SIZE_T_FMT "%lu"
#endif

// Макрос для проверки s21_size_t
#define ck_assert_s21_size_t_eq(actual, expected) \
    ck_assert_msg((actual) == (expected), \
                  "Expected " S21_SIZE_T_FMT ", got " S21_SIZE_T_FMT, \
                  (actual), (expected))

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

#define STRCSPN_TEST_CASES(name, ...) \
    TEST_CASES(name, StrCSpnTestParams, run_strcspn_test, __VA_ARGS__)

#endif