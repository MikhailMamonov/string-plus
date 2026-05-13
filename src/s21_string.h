#ifndef S21_STRING_H
#define S21_STRING_H

#include "types.h"
void *s21_memchr(const void *str, int c, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strerror(int errnum);
char *strrchr(const char *str, int c);

#endif

