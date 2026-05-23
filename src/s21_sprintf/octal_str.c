#include "sprintf_utils.h"

char *o_spec(char *buf, unsigned long long val, formatSpec spec, int *len) {
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
  if (spec.precision < 0)
    spec.precision = 1;
  int digits[32] = {0};
  int oct_len = 0;
  while (val > 0) {
    digits[oct_len++] = val % 8;
    val /= 8;
  }
  if (spec.precision <= oct_len && spec.alt_format) {
    spec.precision = oct_len + 1;
  }
  for (int i = 0; i < spec.precision - oct_len; i++) {
    *buf++ = '0';
  }
  for (int i = oct_len - 1; i >= 0; i--) {
    *buf++ = digits[i] + '0';
  }

  *len = buf - start;
  return buf;
}