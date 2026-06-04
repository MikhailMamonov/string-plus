#include <math.h>

#include "s21_sprintf.h"

// Общая функция для преобразования беззнакового целого в строку
static char *uint_to_str_internal(char *buf, unsigned long long num,
                                  int precision, int add_sign, char sign_char) {
  char tmp[MAX_TMP_SIZE];
  int digit_count = 0;

  if (num == 0) {
    if (precision == 0) {
      if (add_sign) {
        *buf++ = sign_char;
      }
      return buf;
    }
    tmp[digit_count++] = '0';
  } else {
    while (num > 0 && digit_count < MAX_TMP_SIZE) {
      tmp[digit_count++] = (num % 10) + '0';
      num /= 10;
    }
  }

  if (add_sign) {
    *buf++ = sign_char;
  }

  int leading_zeros = precision - digit_count;
  while (leading_zeros-- > 0) {
    *buf++ = '0';
  }

  for (int i = digit_count - 1; i >= 0; i--) {
    *buf++ = tmp[i];
  }

  return buf;
}

// Простое преобразование для целых чисел (без форматирования)
char *simple_int_to_str(char *buf, long long num) {
  unsigned long long u_num;
  int is_negative = 0;

  if (num < 0) {
    is_negative = 1;
    u_num = (unsigned long long)(-num);
  } else {
    u_num = (unsigned long long)num;
  }

  return uint_to_str_internal(buf, u_num, 1, is_negative, '-');
}

// Форматированное преобразование для int
char *int_to_str(char *buf, long long num, int *len, formatSpec spec) {
  char *start = buf;
  unsigned long long u_num;
  int is_negative = 0;

  if (num == 0 && spec.precision == 0) {
    if (spec.show_sign)
      *buf++ = '+';
    else if (spec.space_sign)
      *buf++ = ' ';
    *len = buf - start;
    return buf;
  }

  if (num < 0) {
    is_negative = 1;
    u_num = (unsigned long long)(-num);
  } else {
    u_num = (unsigned long long)num;
  }

  int add_sign = 0;
  char sign_char = 0;
  if (is_negative) {
    add_sign = 1;
    sign_char = '-';
  } else if (spec.show_sign) {
    add_sign = 1;
    sign_char = '+';
  } else if (spec.space_sign) {
    add_sign = 1;
    sign_char = ' ';
  }

  int precision = (spec.precision < 0) ? 1 : spec.precision;

  buf = uint_to_str_internal(buf, u_num, precision, add_sign, sign_char);

  *len = buf - start;
  return buf;
}

// Улучшенная версия write_fractional_part без динамической памяти
static char *write_fractional_part(char *buf, unsigned long long final_frac,
                                   int prec, int calc_prec) {
  *buf++ = '.';
  if (prec > 0) {
    char frac_tmp[64];
    int frac_len = 0;
    unsigned long long u_frac = final_frac;

    if (u_frac == 0) {
      frac_tmp[frac_len++] = '0';
    } else {
      while (u_frac > 0 && frac_len < 64) {
        frac_tmp[frac_len++] = (u_frac % 10) + '0';
        u_frac /= 10;
      }
    }

    int leading_zeroes = calc_prec - frac_len;
    while (leading_zeroes-- > 0) {
      *buf++ = '0';
    }

    for (int i = frac_len - 1; i >= 0; i--) {
      *buf++ = frac_tmp[i];
    }

    int remaining_zeroes = prec - calc_prec;
    while (remaining_zeroes-- > 0) {
      *buf++ = '0';
    }
  }
  return buf;
}

// float_to_str остается практически без изменений
char *float_to_str(char *buf, long double num, formatSpec spec, int *len) {
  char *next_buf = handle_special_floats(buf, num, spec, len);
  if (next_buf != s21_NULL) {
    return next_buf;
  }

  int is_negative = signbit(num);
  if (is_negative) {
    num = -num;
  }

  int prec = (spec.precision < 0) ? 6 : spec.precision;
  int calc_prec = (prec > 17) ? 17 : prec;

  long double pow_10 = powl(10.0l, calc_prec);
  long double scaled_val = num * pow_10, integral, fractional;
  fractional = modfl(scaled_val, &integral);

  if (fabsl(fractional) == 0.5l) {
    scaled_val = (fmodl(integral, 2.0l) == 0.0l)
                     ? integral
                     : integral + (fractional > 0 ? 1.0l : -1.0l);
  } else {
    scaled_val = roundl(scaled_val);
  }

  unsigned long long u_scaled = (unsigned long long)scaled_val;
  unsigned long long u_pow_10 = (unsigned long long)pow_10;
  unsigned long long final_integral = u_scaled / u_pow_10;
  unsigned long long final_fractional = u_scaled % u_pow_10;

  char *start_buf = buf;
  if (is_negative) {
    *buf++ = '-';
  } else if (spec.show_sign) {
    *buf++ = '+';
  } else if (spec.space_sign) {
    *buf++ = ' ';
  }
  buf = simple_int_to_str(buf, (long long)final_integral);

  if (prec > 0 || spec.alt_format) {
    buf = write_fractional_part(buf, final_fractional, prec, calc_prec);
  }

  *len = buf - start_buf;
  return buf;
}