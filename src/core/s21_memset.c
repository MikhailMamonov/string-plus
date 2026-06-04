#include "../s21_string.h"

// TODO что будет если размер строки меньше n?
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *string = (unsigned char *)str;
  unsigned char target = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    string[i] = target;
  }
  return str;
}
