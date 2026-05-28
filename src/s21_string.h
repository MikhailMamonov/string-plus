#ifndef S21_STRING_H
#define S21_STRING_H

#include "types.h"

// Строковые функции
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_memchr(const void *str, int c, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void function_1();
void function_1();
void function_1();
void function_1();
void function_1();


// Функции памяти
void *s21_memchr(const void *str, int c, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

// Функции форматирования
int s21_sprintf(char *str, const char *format, ...);

#endif
