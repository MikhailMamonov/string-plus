#include "sprintf_utils.h"
#include <math.h>

char *remove_tail_zeroes(char *buf, char *buf_p);

char *g_spec(char *buf, long double val, formatSpec spec, int *len) {
  char *next_buf = handle_special_floats(buf, val, spec, len);
  if (next_buf != NULL) {
    return next_buf;
  }

  char *start = buf;
  int exponent = (val == 0.0) ? 0 : (int)floorl(log10l(fabsl(val)));
  if (spec.precision < 0)
    spec.precision = 6;
  if (spec.precision == 0)
    spec.precision = 1;
  if (exponent < -4 || exponent >= spec.precision) {
    spec.precision--;
    if (spec.precision < 0)
      spec.precision = 0;
    if (spec.specifier == 'g')
      spec.specifier = 'e';
    else
      spec.specifier = 'E';
    buf = double_to_exp_str(buf, val, spec, len);
    if (!spec.alt_format) {
      char *buf_p = buf;
      while (*buf_p != 'e' && *buf_p != 'E')
        buf_p--;
      buf_p--;
      buf = remove_tail_zeroes(buf, buf_p);
    }
  } else {
    spec.precision -= (exponent + 1);
    if (spec.precision < 0)
      spec.precision = 0;
    buf = float_to_str(buf, val, spec, len);
    if (!spec.alt_format) {
      char *buf_p = buf - 1;
      buf = remove_tail_zeroes(buf, buf_p);
    }
  }
  *len = buf - start;
  return buf;
}

char *remove_tail_zeroes(char *buf, char *buf_p) {
  while (*buf_p - '0' == 0) {
    for (char *i = buf_p; i < buf; i++) {
      *i = *(i + 1);
    }
    buf--;
    buf_p--;
  }
  if (*buf_p == '.') {
    for (char *i = buf_p; i < buf; i++) {
      *i = *(i + 1);
    }
    buf--;
  }
  return buf;
}