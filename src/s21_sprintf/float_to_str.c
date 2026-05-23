#include "../s21_string.h"
#include "sprintf_utils.h"
#include <math.h>

char *float_to_str(char *buf, double num, formatSpec spec, int *len) {
  char *next_buf = handle_special_floats(buf, num, spec, len);
  if (next_buf != s21_NULL) {
    return next_buf;
  }
  int is_negative = signbit(num);
  if (is_negative) {
    num = -num;
  }
  int prec = spec.precision;
  if (prec < 0)
    prec = 6;
  double round_offset = 0.5 / pow(10, prec);
  num += round_offset;

  char *start_buf = buf;
  if (is_negative) {
    *buf++ = '-';
  }

  buf = int_to_str(buf, (long long)num, len, spec);
  num -= (long long)num;
  if (prec > 0 || spec.alt_format) {
    *buf++ = '.';
    while (prec > 0) {
      num *= 10;

      long long current_digit = (long long)num;

      // Защита от микропогрешностей double округления (9.99999... -> 10)
      if (current_digit > 9)
        current_digit = 9;
      if (current_digit < 0)
        current_digit = 0;

      *buf++ = current_digit + '0';
      num -= current_digit;
      prec--;
    }
  }
  *len = buf - start_buf;
  return buf;
}
