#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *match_result = NULL;
  while (*str1 != '\0' && match_result == NULL) {
    if (s21_strchr(str2, *str1) != NULL) {
      match_result = (char *)str1;
    }
    str1++;
  }

  return match_result;
}
