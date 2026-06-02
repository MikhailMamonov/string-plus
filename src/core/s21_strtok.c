#include "../s21_string.h"

static char *saved_ptr = s21_NULL;

char *s21_strtok(char *str, const char *delim) {

  char *result = s21_NULL;

  if (delim != s21_NULL) {
    if (str != s21_NULL) {
      saved_ptr = str;
    }

    if (saved_ptr != s21_NULL && *saved_ptr != '\0') {
      while (*saved_ptr != '\0' && s21_strchr(delim, *saved_ptr)) {
        saved_ptr++;
      }

      if (*saved_ptr != '\0') {
        result = saved_ptr;
        while (*saved_ptr != '\0' && !s21_strchr(delim, *saved_ptr)) {
          saved_ptr++;
        }

        if (*saved_ptr != '\0') {
          *saved_ptr = '\0';
          saved_ptr++;
        } else {
          saved_ptr = s21_NULL;
        }
      } else {
        saved_ptr = s21_NULL;
      }
    }
  }
  return result;
}
