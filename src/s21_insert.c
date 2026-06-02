#include "s21_string.h"
#include <stdlib.h>

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == s21_NULL || str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  if (start_index > src_len) {
    return s21_NULL;
  }

  s21_size_t str_len = s21_strlen(str);
  char *result = malloc(src_len + str_len + 1);
  if (result == s21_NULL) {
    return s21_NULL;
  }

  char *p_res = result;
  const char *p_src = src;
  const char *p_str = str;

  for (s21_size_t i = 0; i < start_index; i++) {
    *p_res++ = *p_src++;
  }

  while (*p_str != '\0') {
    *p_res++ = *p_str++;
  }

  while (*p_src != '\0') {
    *p_res++ = *p_src++;
  }

  *p_res = '\0';

  return result;
}
