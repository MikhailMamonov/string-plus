#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *d = dest;
  while (*dest != '\0')
    dest++;

  for (s21_size_t i = 0; i < n && *src != '\0'; i++)
    *dest++ = *src++;
  *dest = '\0';
  return d;
}
