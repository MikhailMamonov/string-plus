#include "sprintf_utils.h"
#include <string.h> //for strlen()
#include "../s21_string.h"

// Отдельная функция для форматирования
void formatBySpecifier(formatSpec *spec, va_list *args, char **out, char *start) {
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
    if (s == s21_NULL) s = "(null)";
    len = strlen(s);
    if (spec->precision >= 0 && len > spec->precision) len = spec->precision;
    char *str_end = s + len;
    while (s < str_end) {
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
    long double exp = 0;
    if (spec->length == 'L') exp = va_arg(*args, long double);
    else exp = va_arg(*args, double);
    *out = double_to_exp_str(*out, exp, *spec, &len);
    break;
  }
  case 'f': {
    long double num = 0;
    if (spec->length == 'L') num = va_arg(*args, long double);
    else num = va_arg(*args, double);
    *out = float_to_str(*out, num, *spec, &len);
    break;
  }
  case 'g':
  case 'G': {
    long double num = 0;
    if (spec->length == 'L') num = va_arg(*args, long double);
    else num = va_arg(*args, double);
    *out = g_spec(*out, num, *spec, &len, start);
    break;
  }
  case 'o': {
    unsigned long long val = 0;

    // Считываем и сразу приводим к нужному беззнаковому типу
    if (spec->length == 'l') {
      val = (unsigned long)va_arg(*args, unsigned long);
    } else if (spec->length == 'h') {
      val = (unsigned short)va_arg(*args,
                                   int); // short в va_arg продвигается до int
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
      val = (unsigned short)va_arg(*args,
                                   int); // short в va_arg продвигается до int
    } else {
      val = va_arg(*args, unsigned int); // Обычный %o
    }
    *out = hex_spec(*out, val, *spec, &len);
    break;
  }
  case 'u': {
    unsigned long long val = 0;

    // Считываем и сразу приводим к нужному беззнаковому типу
    if (spec->length == 'l') {
      val = (unsigned long)va_arg(*args, unsigned long);
    } else if (spec->length == 'h') {
      val = (unsigned short)va_arg(*args,
                                   int); // short в va_arg продвигается до int
    } else {
      val = va_arg(*args, unsigned int); // Обычный %o
    }
    *out = u_spec(*out, val, *spec, &len);
    break;
  }
  case '%': {
    *(*out)++ = '%';
    break;
  }
  case 'p': {
    void *pointer = va_arg(*args, void*);
    *out = pointer_to_str(*out, pointer, *spec, &len);
    break;
  }
  case 'n': {
    if (spec->length == 'l') {
        long *pointer = (long *)va_arg(*args, long *);
        *pointer = *out - start;
    } else if (spec->length == 'h') {
        short *pointer = (short *)va_arg(*args, short *); 
        *pointer = *out - start;
    } else {
        int *pointer = va_arg(*args, int *); 
        *pointer = *out - start;
    }
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