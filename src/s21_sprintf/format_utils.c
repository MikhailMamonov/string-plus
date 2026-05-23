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
    long long d = 0;
    if (spec->length == 'l') {
        d = (long)va_arg(*args, long);
    } else if (spec->length == 'h') {
        d = (short)va_arg(*args, int); // short в va_arg продвигается до int
    } else if (spec->length == 'H') { // например, для ll
        d = va_arg(*args, long long);
    } else {
        d = va_arg(*args, int); // Обычный %o
    }
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
  case 'f': {
    double num = va_arg(*args, double);
    int len = 0;
    *out = float_to_str(*out, num, *spec, &len);
    *out = handle_width(*out, len, *spec);
    break;
  }
  case 'g':
  case 'G': {
    double num = va_arg(*args, double);
    int len = 0;
    *out = g_spec(*out, num, *spec, &len);
    *out = handle_width(*out, len, *spec);
    break;
  }
  case 'o': {
    unsigned long long val = 0;
    
    // Считываем и сразу приводим к нужному беззнаковому типу
    if (spec->length == 'l') {
        val = (unsigned long)va_arg(*args, unsigned long);
    } else if (spec->length == 'h') {
        val = (unsigned short)va_arg(*args, int); // short в va_arg продвигается до int
    } else if (spec->length == 'H') { // например, для ll
        val = va_arg(*args, unsigned long long);
    } else {
        val = va_arg(*args, unsigned int); // Обычный %o
    }
    int len = 0;
    *out = o_spec(*out, val, *spec, &len);
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
