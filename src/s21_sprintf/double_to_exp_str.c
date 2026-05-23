#include "sprintf_utils.h"
#include <math.h>

char *write_exp(char *buf, formatSpec spec, long long mantissa_int,
                int exponent, int is_negative, int *len);

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
  } else if (val < 1.0 && val > 0.0 &&
             exponent != 0) { // Для редких пограничных случаев
    val *= 10.0;
    exponent--;
  }

  long long mantissa_int = llround(val * pow(10, spec.precision));

  // Защита от переполнения порядка (например, когда 9.999999 округлилось до 10000000)
  long long limit = llround(pow(10, spec.precision + 1));
  
  if (mantissa_int >= limit) {
    mantissa_int /= 10; // Убираем лишний разряд
    exponent++;         // Сдвигаем экспоненту вверх
  }

  return write_exp(buf, spec, mantissa_int, exponent, is_negative, len);
}

char *write_exp(char *buf, formatSpec spec, long long mantissa_int,
                int exponent, int is_negative, int *len) {
  char *start = buf;

  if (is_negative)
    *buf++ = '-';

    // 1. Создаем буфер для цифр и гарантированно заполняем его символами '0'
  char digits[64];
  for (int i = 0; i < 64; i++) {
    digits[i] = '0';
  }

  // 2. Считаем, сколько всего цифр нам нужно получить (1 целая + precision дробных)
  int num_digits = 1 + spec.precision;

  // 3. Заполняем массив цифрами СПРАВА НАЛЕВО, начиная с конца нужной точности
  long long temp_mantissa = mantissa_int;
  for (int i = num_digits - 1; i >= 0; i--) {
    digits[i] = (temp_mantissa % 10) + '0';
    temp_mantissa /= 10;
  }

  int current_digit = 0;

  *buf++ = digits[current_digit++];

  // Запись дробной части
  if (spec.precision > 0 || spec.alt_format) {
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
