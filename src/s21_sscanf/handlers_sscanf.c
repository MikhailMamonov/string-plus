#include "s21_sscanf.h"

char to_lower(char ch);

const char *pass_spaces(const char *source) {
  while (isspace((unsigned char)*source)) {
    source++;
  }
  return source;
}

void sign_parser(const char **curr, int *width_counter, int *is_negative) {
  if (**curr == '-') {
    *is_negative = 1;
    (*curr)++;
    (*width_counter)++;
  } else if (**curr == '+') {
    (*curr)++;
    (*width_counter)++;
  }
}

void handle_scanf_special_floats(const char **curr, int *width_counter,
                                 formatSpec spec, long double *res) {
  int remaining_width = spec.width - *width_counter;
  if (remaining_width < 3 && spec.width > 0) {
    return;
  }
  if (to_lower(**curr) == 'n' && to_lower(*(*curr + 1)) == 'a' &&
      to_lower(*(*curr + 2)) == 'n') {
    *curr += 3;
    *res = NAN;
  }
  if (to_lower(**curr) == 'i' && to_lower(*(*curr + 1)) == 'n' &&
      to_lower(*(*curr + 2)) == 'f') {
    *curr += 3;
    *res = INFINITY;
    if (remaining_width >= 8 || spec.width < 0) {
      const char *probe = *curr;
      if (*probe != '\0' && to_lower(*probe) == 'i') {
        probe++;
        if (*probe != '\0' && to_lower(*probe) == 'n') {
          probe++;
          if (*probe != '\0' && to_lower(*probe) == 'i') {
            probe++;
            if (*probe != '\0' && to_lower(*probe) == 't') {
              probe++;
              if (*probe != '\0' && to_lower(*probe) == 'y') {
                *curr += 5;
              }
            }
          }
        }
      }
    }
  }
  return;
}

int handle_null_pointer(const char **curr, formatSpec spec) {
  if (spec.width > 0 && spec.width < 5) {
    return FAIL;
  }
  const char *probe = *curr;
  if (*probe != '\0' && *probe == '(') {
    probe++;
    if (*probe != '\0' && *probe == 'n') {
      probe++;
      if (*probe != '\0' && *probe == 'i') {
        probe++;
        if (*probe != '\0' && *probe == 'l') {
          probe++;
          if (*probe != '\0' && *probe == ')') {
            *curr += 5;
            return SUCCESS;
          }
        }
      }
    }
  }
  return FAIL;
}

char to_lower(char ch) {
  if (isupper(ch)) {
    ch = ch + ('a' - 'A');
  }
  return ch;
}