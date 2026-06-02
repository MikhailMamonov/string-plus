#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  unsigned char target = (unsigned char)c;
  char *ret = s21_NULL;
  while (*str != '\0') {
    if ((unsigned char)*str == target)
      ret = (char *)str;
    str++;
  }
  if (target == '\0')
    ret = (char *)str;
  return ret;
}
