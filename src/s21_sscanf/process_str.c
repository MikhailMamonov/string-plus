#include "s21_sscanf.h"
#include <ctype.h>

int process_str(const char **source, char *res, formatSpec spec) {
  const char *curr = *source;
  char c = *curr;
  int width = 0;
  int width_set = 0;
  if (spec.width > 0) {
    width = spec.width;
    width_set = 1;
  }
  while (c != '\0' && (!width_set || width > 0) && !isspace(c)) {
    if (!spec.use_suppress) {
      *res++ = c;
    }
    (curr)++;
    c = *curr;
    width--;
  }
  if (curr == *source) {
    return 0;
  } else {
    *source = curr;
    if (!spec.use_suppress) {
      *res = '\0';
    }
    return 1;
  }
}