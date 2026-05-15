#ifndef S21_STRING_H
#define S21_STRING_H

#include "type.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strncat(char *dest, const char *src, size_t n);
char *s21_strncpy(char *dest, const char *src,s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strstr(const char *haystack, const char *needle);

#endif
