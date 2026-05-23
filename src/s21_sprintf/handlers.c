#include "../s21_string.h"
#include "sprintf_utils.h"
#include <math.h>


char *handle_width(char *buf, int length, formatSpec spec) {
  int spaces_to_add = 0;
  if (spec.width > length) {
    spaces_to_add = spec.width - length;
    if (spec.left_align) {
            // Левое выравнивание: добавляем пробелы справа
            for (int i = 0; i < spaces_to_add; i++) {
                *buf++ = ' ';
            }
    } else{
        char *from = buf - 1;
        char *to = buf + spaces_to_add - 1;
        int minus_zero = 0;
        if (*(buf - length) == '-' && spec.zero_padding) {
            minus_zero = 1;
        }
        for (int i = 0; i < length; i++) {
            if (minus_zero && i == length - 1) *to-- = '0';
            else *to-- = *from--;
        }
        
        for (int i = 0; i < spaces_to_add; i++) {
            if (minus_zero && i == spaces_to_add - 1) *to-- = '-';
            else {
                if (spec.zero_padding) *to-- = '0';
                else *to-- = ' ';
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



