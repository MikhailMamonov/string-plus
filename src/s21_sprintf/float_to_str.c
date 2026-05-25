#include "../s21_string.h"
#include "sprintf_utils.h"
#include <math.h>

char *simple_int_to_str(char *buf, long long num);

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
  } else if (spec.show_sign) {
    *buf++ = '+';
  } else if (spec.space_sign) {
    *buf++ = ' ';
  }
  buf = simple_int_to_str(buf, (long long)num);
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

char *simple_int_to_str(char *buf, long long num) {
  char tmp[64]; // Временный буфер для разворота числа
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
  // Разбираем число на цифры с конца
  while (u_num > 0) {
    tmp[i++] = (u_num % 10) + '0';
    u_num /= 10;
  }

  if (is_negative) {
    *buf++ = '-';
  }

  // Записываем цифры в правильном порядке в основной буфер
  while (i > 0) {
    *buf++ = tmp[--i];
  }
  return buf; // Возвращаем указатель на текущую позицию в буфере
}
