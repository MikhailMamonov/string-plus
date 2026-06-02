
#ifndef TEST_COMMON_H
#define TEST_COMMON_H

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

typedef struct {
  int errnum;
} strerrorParams;

typedef struct {
  const char *str;
  int c;
} strrchrParams;

typedef struct {
  const char *str1;
  const char *str2;
  const char *test_name;
} StrCSpnTestParams;

typedef struct {
  const char *str1;
  const char *str2;
  const char *test_name;
} strpbrkParams;

typedef struct {
  char *str;
  const char *delim;
  const char *test_name;
} strtokParams;

typedef struct {
  const char *str1;
  const char *str2;
  s21_size_t n;
} strncmpParams;

typedef struct {
  const char *haystack;
  const char *needle;
  const char *test_name;
} strstrParams;

typedef struct {
  const char *dest_init;
  const char *src;
  s21_size_t n;
  const char *test_name;
  const char *format;
  const char *expected;
} sprintfParams;

typedef struct {
  const char *str;
  s21_size_t expected;
  const char *test_name;
} strlenParams;

typedef struct {
  const char *dest_init;
  const char *src;
  s21_size_t n;
  const char *test_name;
} strncatParams;

typedef struct {
  const void *str1;
  const void *str2;
  s21_size_t n;
  const char *test_name;
} memcmpParams;

typedef struct {
  const char *src;
  s21_size_t n;
  const char *test_name;
} strncpyParams;

typedef struct {
  const char *src;
  const char *str;
  s21_size_t start_index;
  const char *expected;
  const char *test_name;
} insertParams;

typedef struct {
  const char *src;
  const char *trim_chars;
  const char *expected;
  const char *test_name;
} trimParams;

#define TEST_CASES(name, param_type, run_func, ...)                            \
  static param_type name[] = {__VA_ARGS__};                                    \
  START_TEST(test_##name) {                                                    \
    for (s21_size_t i = 0; i < sizeof(name) / sizeof(param_type); i++) {       \
      run_func(&name[i]);                                                      \
    }                                                                          \
  }                                                                            \
  END_TEST

// Новый макрос для тестов sprintf с переменным количеством аргументов
#define RUN_SPRINTF_TEST(test_name, format, ...)                               \
  START_TEST(test_##test_name) {                                               \
    char std_buf[8000] = {0};                                                  \
    char test_buf[8000] = {0};                                                 \
    int std_len;                                                               \
    int test_len;                                                              \
    std_len = sprintf(std_buf, format, ##__VA_ARGS__);                         \
    test_len = s21_sprintf(test_buf, format, ##__VA_ARGS__);                   \
    ck_assert_str_eq(std_buf, test_buf);                                       \
    ck_assert_int_eq(std_len, test_len);                                       \
    printf("[PASS] %s: \"%s\" -> \"%s\"\n", #test_name, format, std_buf);      \
  }                                                                            \
  END_TEST

#define MEMCPY_TEST_CASES(name, ...)                                           \
  TEST_CASES(name, MemCpyTestParams, run_memcpy_test, __VA_ARGS__)

#define STRCHR_TEST_CASES(name, ...)                                           \
  TEST_CASES(name, StrChrTestParams, run_strchr_test, __VA_ARGS__)

#define MEMSET_TEST_CASES(name, ...)                                           \
  TEST_CASES(name, memsetParams, run_memset_test, __VA_ARGS__)

#define MEMCHR_TEST_CASES(name, ...)                                           \
  TEST_CASES(name, memchrParams, run_memchr_test, __VA_ARGS__)

#define STRERROR_TEST_CASES(name, ...)                                         \
  TEST_CASES(name, strerrorParams, run_strerror_test, __VA_ARGS__)

#define STRRCHR_TEST_CASES(name, ...)                                          \
  TEST_CASES(name, strrchrParams, run_strrchr_test, __VA_ARGS__)

#define STRCSPN_TEST_CASES(name, ...)                                          \
  TEST_CASES(name, StrCSpnTestParams, run_strcspn_test, __VA_ARGS__)

#define STRTOK_TEST_CASES(name, ...)                                           \
  TEST_CASES(name, strtokParams, run_strtok_test, __VA_ARGS__)

#define STRNCMP_TEST_CASES(name, ...)                                          \
  TEST_CASES(name, strncmpParams, run_strncmp_test, __VA_ARGS__)

#define SPRINTF_TEST_CASES(name, ...)                                          \
  TEST_CASES(name, sprintfParams, run_sprintf_test, __VA_ARGS__)

#define STRPBRK_TEST_CASES(name, ...)                                          \
  TEST_CASES(name, strpbrkParams, run_strpbrk_test, __VA_ARGS__)

#define STRSTR_TEST_CASES(name, ...)                                           \
  TEST_CASES(name, strstrParams, run_strstr_test, __VA_ARGS__)

#define STRNCAT_TEST_CASES(name, ...)                                          \
  TEST_CASES(name, strncatParams, run_strncat_test, __VA_ARGS__)

#define STRLEN_TEST_CASES(name, ...)                                           \
  TEST_CASES(name, strlenParams, run_strlen_test, __VA_ARGS__)

#define MEMCMP_TEST_CASES(name, ...)                                           \
  TEST_CASES(name, memcmpParams, run_memcmp_test, __VA_ARGS__)

#define STRNCPY_TEST_CASES(name, ...)                                          \
  TEST_CASES(name, strncpyParams, run_strncpy_test, __VA_ARGS__)

#define INSERT_TEST_CASES(name, ...)                                           \
  TEST_CASES(name, insertParams, run_insert_test, __VA_ARGS__)

#define TRIM_TEST_CASES(name, ...)                                             \
  TEST_CASES(name, trimParams, run_trim_test, __VA_ARGS__)

#endif
