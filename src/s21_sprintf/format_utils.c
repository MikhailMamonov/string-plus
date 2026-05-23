#include "sprintf_utils.h"
#include <string.h> //for strlen()



// Отдельная функция для форматирования
void formatBySpecifier(formatSpec *spec, va_list *args, char **out) {
  int len = 0;
  switch (spec->specifier) {
  case 'c': {
    char c = (char)va_arg(*args, int);
    *(*out)++ = c;
    len = 1;
    break;
  }
  case 's': {
    char *s = va_arg(*args, char *);
    len = strlen(s);

    while (*s) {
      *(*out)++ = *s++;
    }
    break;
  }
  case 'd':
  case 'i': {
    long long d = 0;
    if (spec->length == 'l') {
        d = (long)va_arg(*args, long);
    } else if (spec->length == 'h') {
        d = (short)va_arg(*args, int); // short в va_arg продвигается до int
    } else {
        d = va_arg(*args, int); // Обычный %o
    }
        
    *out = int_to_str(*out, d, &len, *spec);   
    break;
  }
  case 'e':
  case 'E': {
    double exp = va_arg(*args, double);
    *out = double_to_exp_str(*out, exp, *spec, &len);
    break;
  }
  case 'f': {
    double num = va_arg(*args, double);
    *out = float_to_str(*out, num, *spec, &len);
    break;
  }
  case 'g':
  case 'G': {
    double num = va_arg(*args, double);
    *out = g_spec(*out, num, *spec, &len);
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
    *out = o_spec(*out, val, *spec, &len);
    break;
  }
  case 'x':
  case 'X': {
    unsigned long long val = 0;
    
    // Считываем и сразу приводим к нужному беззнаковому типу
    if (spec->length == 'l') {
        val = (unsigned long)va_arg(*args, unsigned long);
    } else if (spec->length == 'h') {
        val = (unsigned short)va_arg(*args, int); // short в va_arg продвигается до int
    } else {
        val = va_arg(*args, unsigned int); // Обычный %o
    }
    *out = hex_spec(*out, val, *spec, &len);
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
  *out = handle_width(*out, len, *spec);
}