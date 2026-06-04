#include "../s21_string.h"


void *s21_memset(void *str, int c, s21_size_t n) {
  if (str == s21_NULL) {
	return s21_NULL;
  }	
  unsigned char *string = (unsigned char *)str;
  unsigned char target = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    string[i] = target;
  }
  return str;
}
