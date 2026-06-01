#include "s21_sscanf.h"

int process_char(const char **source, char *res, formatSpec spec) {
  const char *curr = *source;
  char c = *curr;
  int width = 0;
  if (spec.width > 0) {
    width = spec.width;
  } else {
    width = 1;
  }
  while (c != '\0' && width > 0) {
    if (!spec.use_suppress) {
      *res++ = c;
    }
    (curr)++;
    c = *curr;
    width--;
  }
  if (width != 0) {
    return 0;
  } else {
    *source = curr;
    return 1;
  }
}