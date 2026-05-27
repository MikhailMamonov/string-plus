#include "s21_sprintf.h"
#include <math.h>

char *remove_tail_zeroes(char *buf, char *buf_p, char *start);
long double round_banking(long double val, int precision);

char *g_spec(char *buf, long double val, formatSpec spec, int *len,
             char *start) {
  char *next_buf = handle_special_floats(buf, val, spec, len);
  if (next_buf != NULL) {
    return next_buf;
  }

  char *start_len = buf;

  // 1. Определяем реальную рабочую точность (значащие цифры)
  int prec = spec.precision;
  if (prec < 0)
    prec = 6;
  if (prec == 0)
    prec = 1;

  // 2. Делаем предварительный расчет экспоненты, чтобы понять, до какого знака
  // округлять
  int is_negative = signbit(val);
  long double abs_val = is_negative ? -val : val;
  int temp_exponent = (abs_val == 0.0l) ? 0 : (int)floorl(log10l(abs_val));

  // 3. КРИТИЧЕСКИЙ ФИКС: Округляем число ДО расчета финальной экспоненты
  // Если число уйдет в %e, округляем до (prec - 1) знака относительно
  // экспоненты. Если в %f, то до (prec - 1 - temp_exponent) знаков.
  int round_prec = prec - 1 - temp_exponent;
  if (temp_exponent < -4 || temp_exponent >= prec) {
    round_prec = prec - 1;
    // Если число мелкое (например, 0.000095), сдвигаем округление под его
    // масштаб
    if (temp_exponent < 0) {
      round_prec = prec - 1 - temp_exponent;
    }
  }

  // Применяем округление к копии числа для точного вычисления экспоненты
  long double rounded_val = val;
  if (round_prec >= 0 && round_prec < 30) {
    rounded_val = round_banking(abs_val, round_prec);
    if (is_negative)
      rounded_val = -rounded_val;
  }

  // 4. Считаем ФИНАЛЬНУЮ экспоненту по уже округленному числу
  int exponent =
      (rounded_val == 0.0l) ? 0 : (int)floorl(log10l(fabsl(rounded_val)));

  // Обновляем spec.precision согласно стандарту
  spec.precision = prec;

  // 5. Переключаемся на %e или %f на основе финальной экспоненты
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
      buf = remove_tail_zeroes(buf, buf_p, start);
    }
  } else {
    spec.precision -= (exponent + 1);
    if (spec.precision < 0)
      spec.precision = 0;
    buf = float_to_str(buf, val, spec, len);
    if (!spec.alt_format) {
      char *buf_p = buf - 1;
      buf = remove_tail_zeroes(buf, buf_p, start);
    }
  }
  *len = buf - start_len;
  return buf;
}

// Безопасная функция удаления нулей без затирания памяти
char *remove_tail_zeroes(char *buf, char *buf_p, char *start) {
  char *dot = s21_strchr(start, '.');
  if (dot != s21_NULL) {
    // Проверяем, что мы находимся строго правее точки
    while (buf_p > dot && buf_p >= start && *buf_p == '0') {
      for (char *i = buf_p; i < buf; i++) {
        *i = *(i + 1);
      }
      buf--;
      buf_p--;
    }
    // Если уперлись в точку, удаляем и её
    if (buf_p == dot) {
      for (char *i = buf_p; i < buf; i++) {
        *i = *(i + 1);
      }
      buf--;
    }
  }
  return buf;
}

long double round_banking(long double val, int precision) {
  // 1. Считаем множитель 10 в степени precision
  long double pow_10 = powl(10.0l, precision);
  long double scaled_val = val * pow_10;

  // 2. Отделяем целую и дробную части сдвинутого числа
  long double integral;
  long double fractional = modfl(scaled_val, &integral);

  // 3. Задаем эпсилон для компенсации погрешностей типа данных
  long double epsilon = 1e-11l;

  // 4. Проверяем, является ли остаток в точности половиной (0.5)
  if (fabsl(fabsl(fractional) - 0.5l) < epsilon) {
    // Если целая часть чётная — отбрасываем половинку (округляем вниз по
    // модулю)
    if (fmodl(integral, 2.0l) == 0.0l) {
      scaled_val = integral;
    } else {
      // Если нечётная — округляем к ближайшему чётному (вверх по модулю)
      scaled_val = integral + (fractional > 0 ? 1.0l : -1.0l);
    }
  } else {
    // Для всех остальных случаев используем стандартное округление
    scaled_val = roundl(scaled_val);
  }

  // 5. Возвращаем запятую на место
  return scaled_val / pow_10;
}