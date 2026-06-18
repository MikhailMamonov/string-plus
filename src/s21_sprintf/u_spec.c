#include "sprintf_utils.h"

char *u_spec(char *buf, unsigned long long val, formatSpec spec, int *len) {
  if (val == 0) {
    if (spec.precision == 0) {
      *len = 0;
      return buf;
    }
    *buf++ = '0';
    *len = 1;
    return buf;
  }
  char *start = buf;
  if (spec.precision < 0) {
    spec.precision = 1;
  }
  int digits[32] = {0};
  int dec_len = 0;
  while (val > 0) {
    digits[dec_len++] = val % 10;
    val /= 10;
  }
  for (int i = 0; i < spec.precision - dec_len; i++) {
    *buf++ = '0';
  }
  for (int i = dec_len - 1; i >= 0; i--) {
    *buf++ = digits[i] + '0';
  }

  *len = buf - start;
  return buf;
}