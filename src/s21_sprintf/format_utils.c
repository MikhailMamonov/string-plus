#include "sprintf_utils.h"
#include <string.h> //for strlen()



// Отдельная функция для форматирования
void formatBySpecifier(formatSpec *spec, va_list *args, char **out) {
  switch (spec->specifier) {
  case 'c': {
    char c = (char)va_arg(*args, int);
    printf("DEBUG: left_align = %d, width = %d\n", spec->left_align, spec->width);
    *(*out)++ = c;
    *out = handle_width(*out, 1, *spec);
    break;
  }
  case 's': {
    char *s = va_arg(*args, char *);
    int len = strlen(s);

    while (*s) {
      *(*out)++ = *s++;
    }
    *out = handle_width(*out, len, *spec);
    break;
  }
  case 'd':
  case 'i': {
    int d = va_arg(*args, int);
    int len = 0;
        
    *out = int_to_str(*out, d, &len);   
    *out = handle_width(*out, len, *spec);
    break;
  }
  case 'e':
  case 'E': {
    double exp = va_arg(*args, double);
    int len = 0;
    *out = double_to_exp_str(*out, exp, *spec, &len);
    *out = handle_width(*out, len, *spec);
    break;
  }
  // TODO: need implementation
  //  case 'u': {
  //    unsigned int u = va_arg(*args, unsigned int);
  //    *out = uint_to_str(*out, u);
  //    break;
  //  }
  // TODO: need implementation
  //  case 'x':
  //  case 'X': {
  //    unsigned int hex = va_arg(*args, unsigned int);
  //    *out = hex_to_str(*out, hex, spec->specifier == 'X');
  //    break;
  //  }
  case '%': {
    *(*out)++ = '%';
    break;
  }
  default: {
    *(*out)++ = '%';
    if (spec->specifier) {
      *(*out)++ = spec->specifier;
    }
    break;
  }
  }
}