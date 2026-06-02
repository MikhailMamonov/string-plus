#include "s21_sscanf.h"
#include <math.h>

int process_float(const char **source, long double *res, formatSpec spec) {
  const char *curr = *source;
  int is_negative = 0;
  int width_defined = 0;
  if (spec.width > 0) {
    width_defined = 1;
  }
  int width_counter = 0, digits_found = 0;
  sign_parser(&curr, &width_counter, &is_negative);
  handle_scanf_special_floats(&curr, &width_counter, spec, res);
  if (isinf(*res) && is_negative) {
    *res = -INFINITY;
    *source = curr;
    return SUCCESS;
  } else if (isinf(*res) || isnan(*res)) {
    *source = curr;
    return SUCCESS;
  }
  long double temp = 0;
  while (*curr >= '0' && *curr <= '9' &&
         (!width_defined || width_counter < spec.width)) {
    temp *= 10.0;
    temp += *curr - '0';
    width_counter++;
    digits_found++;
    curr++;
  }
  if (*curr == '.' && (!width_defined || width_counter < spec.width)) {
    curr++;
    width_counter++;
  }
  long double divisor = 10.0;
  while (*curr >= '0' && *curr <= '9' &&
         (!width_defined || width_counter < spec.width)) {
    temp += (*curr - '0') / divisor;
    divisor *= 10.0;
    width_counter++;
    digits_found++;
    curr++;
  }
  if (digits_found && (*curr == 'e' || *curr == 'E') &&
      (!width_defined || width_counter + 1 < spec.width)) {
    curr++;
    width_counter++;
    long long exp_val = 0;
    spec.specifier = 'd';
    spec.width -= width_counter;
    if (process_int(&curr, &exp_val, spec)) {
      temp *= pow(10, exp_val);
    }
  }
  if (!digits_found) {
    return FAIL;
  } else {
    if (is_negative) {
      temp = -temp;
    }
    *res = temp;
    *source = curr;
    return SUCCESS;
  }
}
