#include "../s21_string.h"
#include "sprintf_utils.h"
#include <math.h>

char *simple_int_to_str(char *buf, long long num);

static char *write_fractional_part(char *buf, unsigned long long final_frac,
                                   int prec, int calc_prec) {
  *buf++ = '.';
  if (prec > 0) {
    char frac_tmp[64] = {0};
    int frac_len = 0;
    unsigned long long u_frac = final_frac;

    if (u_frac == 0) {
      frac_tmp[frac_len++] = '0';
    } else {
      while (u_frac > 0) {
        frac_tmp[frac_len++] = (u_frac % 10) + '0';
        u_frac /= 10;
      }
    }

    int leading_zeroes = calc_prec - frac_len;
    while (leading_zeroes-- > 0) *buf++ = '0';
    while (frac_len > 0) *buf++ = frac_tmp[--frac_len];

    // Если запрошенная точность больше 17, просто добиваем строку нулями.
    // Без BigInt и тяжелых циклов — быстро и безопасно для памяти.
    int remaining_zeroes = prec - calc_prec;
    while (remaining_zeroes-- > 0) *buf++ = '0';
  }
  return buf;
}

char *float_to_str(char *buf, long double num, formatSpec spec, int *len) {
  char *next_buf = handle_special_floats(buf, num, spec, len);
  if (next_buf != s21_NULL) return next_buf;

  int is_negative = signbit(num);
  if (is_negative) num = -num;

  int prec = (spec.precision < 0) ? 6 : spec.precision;
  int calc_prec = (prec > 17) ? 17 : prec;

  long double pow_10 = powl(10.0l, calc_prec);
  long double scaled_val = num * pow_10, integral, fractional;
  fractional = modfl(scaled_val, &integral);

  // Банковское округление до ближайшего чётного
  if (fabsl(fractional) == 0.5l) {
    scaled_val = (fmodl(integral, 2.0l) == 0.0l) ? integral : integral + (fractional > 0 ? 1.0l : -1.0l);
  } else {
    scaled_val = roundl(scaled_val);
  }

  unsigned long long u_scaled = (unsigned long long)scaled_val;
  unsigned long long u_pow_10 = (unsigned long long)pow_10;
  unsigned long long final_integral = u_scaled / u_pow_10;
  unsigned long long final_fractional = u_scaled % u_pow_10;

  char *start_buf = buf;
  if (is_negative) *buf++ = '-';
  else if (spec.show_sign) *buf++ = '+';
  else if (spec.space_sign) *buf++ = ' ';

  buf = simple_int_to_str(buf, (long long)final_integral);

  if (prec > 0 || spec.alt_format) {
    buf = write_fractional_part(buf, final_fractional, prec, calc_prec);
  }

  *len = buf - start_buf;
  return buf;
}


char *simple_int_to_str(char *buf, long long num) {
  char tmp[64]; 
  int i = 0;
  int is_negative = 0;

  if (num == 0) {
    *buf++ = '0';
    return buf;
  }
  unsigned long long u_num;
  if (num < 0) {
    is_negative = 1;
    u_num = (unsigned long long)(-num);
  } else {
    u_num = (unsigned long long)num;
  }
  while (u_num > 0) {
    tmp[i++] = (u_num % 10) + '0';
    u_num /= 10;
  }
  if (is_negative) {
    *buf++ = '-';
  }
  while (i > 0) {
    *buf++ = tmp[--i];
  }
  return buf;
}