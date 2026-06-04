#include <stdlib.h>

#include "../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL || trim_chars == s21_NULL) {
    return s21_NULL;
  }

  const char *left = src;
  while (*left != '\0' && s21_strchr(trim_chars, *left)) {
    left++;
  }

  if (*left == '\0') {
    char *empty = malloc(sizeof(char));
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

  if (right > src) {
    right--;
  }

  while (right > left && s21_strchr(trim_chars, *right)) {
    right--;
  }

  s21_size_t new_len = (s21_size_t)(right - left + sizeof(char));
  char *result = malloc(new_len + sizeof(char));
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
