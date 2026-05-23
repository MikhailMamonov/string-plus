#include "../s21_string.h"
#include "sprintf_utils.h"
#include <math.h>

char *handle_width(char *buf, int length, formatSpec spec) {
  if (spec.width <= length) {
    return buf;
  }
  
  int spaces_to_add = spec.width - length;
  
  if (spec.left_align) {
    for (int i = 0; i < spaces_to_add; i++) {
      *buf++ = ' ';
    }
    return buf;
  }
  
  // Правое выравнивание
  char *start = buf - length;
  char temp[spec.width + 1];
  int temp_pos = 0;
  
  // Анализируем входную строку
  int has_sign = (*start == '-' || *start == '+');
  char sign = has_sign ? *start : 0;
  int num_start = has_sign ? 1 : 0;
  int num_len = length - num_start;
  
  // Определяем символ для заполнения
  char pad_char = (spec.zero_padding && !spec.left_align) ? '0' : ' ';
  
  if (has_sign && spec.zero_padding && !spec.left_align) {
    // Случай: %+010d - знак в начало, потом нули, потом число
    temp[temp_pos++] = sign;
    for (int i = 0; i < spaces_to_add; i++) {
      temp[temp_pos++] = '0';
    }
    for (int i = 0; i < num_len; i++) {
      temp[temp_pos++] = start[num_start + i];
    }
  } else if (has_sign) {
    // Случай: %10d с отрицательным числом или %+10d
    // Сначала заполняем padding, потом знак, потом число
    for (int i = 0; i < spaces_to_add; i++) {
      temp[temp_pos++] = pad_char;
    }
    temp[temp_pos++] = sign;
    for (int i = 0; i < num_len; i++) {
      temp[temp_pos++] = start[num_start + i];
    }
  } else {
    // Нет знака - просто padding и число
    for (int i = 0; i < spaces_to_add; i++) {
      temp[temp_pos++] = pad_char;
    }
    for (int i = 0; i < num_len; i++) {
      temp[temp_pos++] = start[i];
    }
  }
  
  // Копируем обратно
  for (int i = 0; i < spec.width; i++) {
    start[i] = temp[i];
  }
  
  return start + spec.width;
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
