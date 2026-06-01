#include "s21_sscanf.h"
#include <stdlib.h>

// Отдельная функция для форматирования
int formatScanfBySpecifier(formatSpec *spec, va_list *args, const char **source, int *count, const char *start) {
  int ret = FAIL;
  switch (spec->specifier) {
  case 'c': {
    char *pointer = s21_NULL;
    if (!spec->use_suppress) {
        pointer = va_arg(*args, char *);
    }
    if (process_char(source, pointer, *spec)) {
      ret = SUCCESS;
    } else {
      ret = FAIL;
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
      ret = SUCCESS;
    } else {
      ret = FAIL;
    }
    break;
  }
  case 'd':
  case 'i': {
    long long res = 0;
    *source = pass_spaces(*source);
    if (process_int(source, &res, *spec)) {
      ret = SUCCESS;
      if (!spec->use_suppress) {
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
    }
    else {
      ret = FAIL;
    }
    break;
  }
  case 'x':
  case 'X':
  case 'o': 
  case 'u': {
    long long res = 0;
    *source = pass_spaces(*source);
    if (process_int(source, &res, *spec)) {
      ret = SUCCESS;
      if (!spec->use_suppress) {
        if (spec->length == 'l') {
            unsigned long *pointer = (unsigned long *)va_arg(*args, unsigned long *);
            *pointer = (unsigned long)res;
        } else if (spec->length == 'h') {
            unsigned short *pointer = (unsigned short *)va_arg(*args, unsigned short *);
            *pointer = (unsigned short)res;
        } else {
            unsigned int *pointer = (unsigned int *)va_arg(*args, unsigned int *); 
            *pointer = (unsigned int)res;
        }
      }
    }
    else {
      ret = FAIL;
    }
    break;
  }
  case 'f':
  case 'e':
  case 'E':
  case 'g':
  case 'G': {
    long double res = 0;
    *source = pass_spaces(*source);
    if (process_float(source, &res, *spec)) {
      ret = SUCCESS;
      if (!spec->use_suppress) {
        if (spec->length == 'L') {
            long double *pointer = (long double *)va_arg(*args, long double *);
            *pointer = res;
        } else if (spec->length == 'l') {
            double *pointer = (double *)va_arg(*args, double *); 
            *pointer = (double)res;
        } else {
            float *pointer = (float *)va_arg(*args, float *); 
            *pointer = (float)res;
        }
      }
    }
    else {
      ret = FAIL;
    }
    break;
  }
  case '%': {
    *source = pass_spaces(*source);
    if (**source == '%') {
      (*source)++;
      ret = SUCCESS;
    } else {
      ret = FAIL;
    }
    break;
  }
  case 'p': {
    *source = pass_spaces(*source);
    if (handle_null_pointer(source, *spec)) {
      ret = SUCCESS;
      if (!spec->use_suppress) {
        void **pointer = va_arg(*args, void **); 
        *pointer = s21_NULL;
      }
    } else {
      long long res = 0;
      spec->specifier = 'x';
      if (process_int(source, &res, *spec)) {
        ret = SUCCESS;
        if (!spec->use_suppress) {
          void **pointer = va_arg(*args, void **); 
          *pointer = (void *)res;
        }
      } else {
        ret = FAIL;
      }
    }
    break;
  }
  case 'n': {
    ret = SUCCESS;
    if (!spec->use_suppress) {
      if (spec->length == 'l') {
          long *pointer = (long *)va_arg(*args, long *);
          *pointer = *source - start;
      } else if (spec->length == 'h') {
          short *pointer = (short *)va_arg(*args, short *); 
          *pointer = *source - start;
      } else {
          int *pointer = va_arg(*args, int *); 
          *pointer = *source - start;
      }
    }
    break;
  }
  default: {
    ret = FAIL;
    break;
  }
  }
  if (ret == SUCCESS && !spec->use_suppress && spec->specifier != '%' && spec->specifier != 'n') {
    (*count)++;
  } 
  return ret;
}
