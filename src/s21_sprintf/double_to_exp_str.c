#include "sprintf_utils.h"
#include <math.h>
#include <string.h> //strlen, strncat

char *write_exp(char *buf, formatSpec spec, long long mantissa_int, int exponent,
                int is_negative, int *len);

char *double_to_exp_str(char *buf, double val, formatSpec spec, int *len) {
  char *next_buf = handle_special_floats(buf, val, spec, len);

  if (next_buf != NULL) {
      return next_buf;
  }
  // 1. Сразу определяем и сохраняем знак
  int is_negative = signbit(val);
  val = fabs(val);

  int exponent = 0;
  if (val != 0.0) {
    exponent = (int)floor(log10(val));
    // Используем умножение для отрицательных степеней во избежание потери
    // точности
    val /= pow(10, exponent);
  }

  if (spec.precision < 0)
    spec.precision = 6;

  if (val >= 10.0) {
    val /= 10.0;
    exponent++;
  } else if (val < 1.0 && val > 0.0 && exponent != 0) { // Для редких пограничных случаев
    val *= 10.0;
    exponent--;
  }

  long long mantissa_int = llround(val * pow(10, spec.precision));

  return write_exp(buf, spec, mantissa_int, exponent, is_negative, len);
}

char *write_exp(char *buf, formatSpec spec, long long mantissa_int, int exponent,
                int is_negative, int *len) {
  char *start = buf;

  if (is_negative) *buf++ = '-';

  char digits[64];
  int num_digits = 1 + spec.precision;

  for (int i = num_digits - 1; i >= 0; i--) {
    digits[i] = (mantissa_int % 10) + '0';
    mantissa_int /= 10;
  }

  int current_digit = 0;

  *buf++ = digits[current_digit++];

  // Запись дробной части
  if (spec.precision > 0) {
    *buf++ = '.';
    for (int i = 0; i < spec.precision; i++) {
      *buf++ = digits[current_digit++];
    }
  }

  // Запись знака и порядка экспоненты
  *buf++ = spec.specifier ? spec.specifier : 'e';
  if (exponent >= 0) {
    *buf++ = '+';
  } else {
    *buf++ = '-';
    exponent = -exponent;
  }

  // Вывод порядка (минимум 2 цифры)
  if (exponent < 10) {
    *buf++ = '0';
    *buf++ = exponent + '0';
  } else {
    char temp_exp[8];
    int i = 0;
    while (exponent > 0) {
      temp_exp[i++] = (exponent % 10) + '0';
      exponent /= 10;
    }
    while (i > 0) {
      *buf++ = temp_exp[--i];
    }
  }

  *len = buf - start;
  return buf;
}

char *handle_special_floats(char *buf, double val, formatSpec spec, int *len) {
    int is_nan = isnan(val);
    int is_inf = isinf(val);

    // Если число обычное — выходим, управление передается основному коду %f / %e
    if (!is_nan && !is_inf) {
        return NULL;
    }

    char *start = buf;
    int is_upper = (spec.specifier == 'F' || spec.specifier == 'E' || spec.specifier == 'G');
    int is_negative = signbit(val);

    // 1. Обработка знака (+, -, пробел)
    if (is_negative) {
        *buf++ = '-';
    } else if (spec.show_sign) {
        *buf++ = '+';
    } else if (spec.space_sign) {
        *buf++ = ' ';
    }

    // 2. Запись самого значения с учетом регистра
    if (is_nan) {
        *buf++ = is_upper ? 'N' : 'n';
        *buf++ = is_upper ? 'A' : 'a';
        *buf++ = is_upper ? 'N' : 'n';
    } else { // is_inf
        *buf++ = is_upper ? 'I' : 'i';
        *buf++ = is_upper ? 'N' : 'n';
        *buf++ = is_upper ? 'F' : 'f';
    }

    *len = buf - start; // Записываем точную длину напечатанного (нужно для ширины поля)
    return buf;         // Возвращаем позицию для дальнейшей работы sprintf
}

