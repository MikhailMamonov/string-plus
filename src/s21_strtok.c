#include "s21_string.h"

static char *saved_ptr = NULL;

char *s21_strtok(char *str, const char *delim) {

  char *result = NULL;

  if (delim != NULL) {
    if (str != NULL) {
      saved_ptr = str;
    }

    if (saved_ptr != NULL && *saved_ptr != '\0') {
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
          saved_ptr = NULL;
        }
      } else {
        saved_ptr = NULL;
      }
    }
  }
  return result;
}
