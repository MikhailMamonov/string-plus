#include "s21_sscanf.h"
#include <stdlib.h>

// Отдельная функция для форматирования
int formatScanfBySpecifier(formatSpec *spec, va_list *args, const char **source,
                           int *count) {
  int ret = 0;
  switch (spec->specifier) {
  case 'c': {
    char *pointer = s21_NULL;
    if (!spec->use_suppress) {
      pointer = va_arg(*args, char *);
    }
    if (process_char(source, pointer, *spec)) {
      if (!spec->use_suppress) {
        (*count)++;
      }
      ret = 1;
    } else {
      ret = 0;
    }
    break;
  }
  case 's': {
    char *pointer = s21_NULL;
    if (!spec->use_suppress) {
      pointer = va_arg(*args, char *);
    }
    *source = pass_spaces(*source);
    if (process_str(source, pointer, *spec)) {
      if (!spec->use_suppress) {
        (*count)++;
      }
      ret = 1;
    } else {
      ret = 0;
    }
    break;
  }
  case 'd':
  case 'i': {
    long long res = 0;
    *source = pass_spaces(*source);
    if (str_to_int(source, &res, *spec)) {
      ret = 1;
      if (!spec->use_suppress) {
        (*count)++;
        if (spec->length == 'l') {
          long *pointer = (long *)va_arg(*args, long *);
          *pointer = (long)res;
        } else if (spec->length == 'h') {
          short *pointer = (short *)va_arg(*args, short *);
          *pointer = (short)res;
        } else {
          int *pointer = (int *)va_arg(*args, int *);
          *pointer = (int)res;
        }
      }
    } else {
      ret = 0;
    }
    break;
  }
  case 'x':
  case 'X':
  case 'o':
  case 'u': {
    long long res = 0;
    *source = pass_spaces(*source);
    if (str_to_int(source, &res, *spec)) {
      ret = 1;
      if (!spec->use_suppress) {
        (*count)++;
        if (spec->length == 'l') {
          unsigned long *pointer =
              (unsigned long *)va_arg(*args, unsigned long *);
          *pointer = (unsigned long)res;
        } else if (spec->length == 'h') {
          unsigned short *pointer =
              (unsigned short *)va_arg(*args, unsigned short *);
          *pointer = (unsigned short)res;
        } else {
          unsigned int *pointer = (unsigned int *)va_arg(*args, unsigned int *);
          *pointer = (unsigned int)res;
        }
      }
    } else {
      ret = 0;
    }
    break;
  }
    /* case 'e':
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
     case 'u': {
       unsigned long long val = 0;

       // Считываем и сразу приводим к нужному беззнаковому типу
       if (spec->length == 'l') {
         val = (unsigned long)va_arg(*args, unsigned long);
       } else if (spec->length == 'h') {
         val = (unsigned short)va_arg(*args,
                                      int); // short в va_arg продвигается до
     int } else { val = va_arg(*args, unsigned int); // Обычный %o
       }
       *out = u_spec(*out, val, *spec, &len);
       break;
     }*/
  case '%': {
    *source = pass_spaces(*source);
    if (**source == '%') {
      (*source)++;
      ret = 1;
    } else {
      ret = 0;
    }
    break;
  } /*
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
   }*/
  }
  return ret;
}