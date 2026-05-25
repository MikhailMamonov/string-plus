#include "../s21_string.h"
#include "sprintf_utils.h"
#include <math.h>
#include <string.h> //strstr

char *handle_width(char *buf, int length, formatSpec spec) {
  int spaces_to_add = 0;
  if (spec.width > length) {
    spaces_to_add = spec.width - length;
    if (spec.left_align) {
      // Левое выравнивание: добавляем пробелы справа
      for (int i = 0; i < spaces_to_add; i++) {
        *buf++ = ' ';
      }
    } else {
      char *from = buf - 1;
      char *to = buf + spaces_to_add - 1;
      char pad_char = ' ';
      if (spec.zero_padding &&
          (spec.precision < 0 ||
           s21_strchr("diouxX", spec.specifier) == s21_NULL) &&
          strstr(buf - length, "NAN") == s21_NULL &&
          strstr(buf - length, "nan") == NULL &&
          strstr(buf - length, "inf") == NULL &&
          strstr(buf - length, "INF") == NULL) {
        pad_char = '0';
      }
      int minus_zero = 0;
      if (*(buf - length) == '-' && pad_char == '0') {
        minus_zero = 1;
      }
      int plus_zero = 0;
      if (!minus_zero && *(buf - length) == '+' && pad_char == '0' &&
          s21_strchr("difeEgG", spec.specifier) != s21_NULL) {
        plus_zero = 1;
      }
      int space_zero = 0;
      if (!minus_zero && !plus_zero && spec.space_sign && pad_char == '0' &&
          s21_strchr("difeEgG", spec.specifier) != s21_NULL) {
        space_zero = 1;
      }
      int hex_zero = 0;
      if (s21_strchr("xX", spec.specifier) != s21_NULL && pad_char == '0' &&
          spec.alt_format) {
        hex_zero = 1;
      }
      for (int i = 0; i < length; i++) {
        if ((minus_zero || plus_zero || space_zero) && i == length - 1)
          *to-- = '0';
        else if (hex_zero && *from == spec.specifier)
          *to-- = '0';
        else
          *to-- = *from--;
      }

      for (int i = 0; i < spaces_to_add; i++) {
        if (minus_zero && i == spaces_to_add - 1)
          *to-- = '-';
        else if (plus_zero && i == spaces_to_add - 1)
          *to-- = '+';
        else if (space_zero && i == spaces_to_add - 1)
          *to-- = ' ';
        else if (hex_zero && i == spaces_to_add - 2)
          *to-- = spec.specifier;
        else {
          *to-- = pad_char;
        }
      }
      buf += spaces_to_add;
    }
  }
  return buf;
}

// char *handle_precision(char *buf, int length, char spec) {
// //   if (spec == 's') {

// //   }

//   return buf;
// }

char *handle_special_floats(char *buf, double val, formatSpec spec, int *len) {
  int is_nan = isnan(val);
  int is_inf = isinf(val);

  // Если число обычное — выходим, управление передается основному коду %f / %e
  if (!is_nan && !is_inf) {
    return s21_NULL;
  }

  char *start = buf;
  int is_upper =
      (spec.specifier == 'F' || spec.specifier == 'E' || spec.specifier == 'G');
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

  *len = buf -
         start; // Записываем точную длину напечатанного (нужно для ширины поля)
  return buf; // Возвращаем позицию для дальнейшей работы sprintf
}
