#include "s21_string.h"
#include <stdlib.h>

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL || trim_chars == s21_NULL) {
    return s21_NULL;
  }

  const char *left = src;
  while (*left != '\0' && s21_strrchr(trim_chars, *left)) {
    left++;
  }

  if (*left == '\0') {
    char *empty = malloc(1);
    if (empty == s21_NULL) {
      return s21_NULL;
    }
    *empty = '\0';
    return empty;
  }

  const char *right = src;
  while (*right != '\0') {
    right++;
  }
  right--;

  while (right > left && s21_strrchr(trim_chars, *right)) {
    right--;
  }

  s21_size_t new_len = (s21_size_t)(right - left + 1);

  char *result = malloc(new_len + 1);
  if (result == s21_NULL) {
    return s21_NULL;
  }

  char *p_res = result;
  const char *p_src = left;
  while (p_src <= right) {
    *p_res++ = *p_src++;
  }
  *p_res = '\0';

  return result;
}
