#include "s21_sprintf.h"
#include <ctype.h>

int parseFlag(char input) {
  static const char *flags = "+- #0";
  return (s21_strchr(flags, input) != s21_NULL);
}

const char *parseFlags(const char *format, formatSpec *spec) {
  while (*format && parseFlag(*format)) {
    switch (*format) {
    case '-':
      spec->left_align = 1;
      break;
    case '+':
      spec->show_sign = 1;
      break;
    case ' ':
      spec->space_sign = 1;
      break;
    case '#':
      spec->alt_format = 1;
      break;
    case '0':
      spec->zero_padding = 1;
      break;
    }
    format++;
  }
  return format;
}

const char *parseWidth(const char *input, formatSpec *spec, va_list *args) {
  if (*input == '*') {
    spec->width = va_arg(*args, int);
    if (spec->width < 0) {
      spec->left_align = 1;
      spec->width = -spec->width;
    }
    input++;
  } else if (isdigit(*input)) {
    spec->width = 0;
    while (isdigit(*input)) {
      spec->width = spec->width * 10 + (*input - '0');
      input++;
    }
  }

  return input;
}

const char *parsePrecision(const char *input, formatSpec *spec, va_list *args) {
  if (*input == '.') {
    input++;
    if (*input == '*') {
      spec->precision = va_arg(*args, int);
      if (spec->precision < 0) {
        spec->precision = -1;
      }
      input++;
    } else if (isdigit(*input)) {
      spec->precision = 0;
      while (isdigit(*input)) {
        spec->precision = spec->precision * 10 + (*input - '0');
        input++;
      }
    }
  } else
    spec->precision = -1;
  return input;
}

const char *parseLength(const char *input, formatSpec *spec) {
  if (*input == 'l' || *input == 'L' || *input == 'h') {
    spec->length = *input;
    input++;
    if (spec->length == 'l' && *input == 'l') {
      spec->length = 'L'; // или введите отдельный флаг
      input++;
    }
  }

  return input;
}

const char *parseSpecifier(const char *format, formatSpec *spec) {
  static const char *specifiers = "diouxXeEfgGcspn%";

  if (format && s21_strchr(specifiers, *format)) {
    spec->specifier = *format;
    return format + 1;
  }
  return format;
}

const char *parseFormat(const char *format, formatSpec *spec, va_list *args) {
  s21_memset(spec, 0, sizeof(formatSpec));
  spec->precision = -1;

  format = parseFlags(format, spec);
  format = parseWidth(format, spec, args);
  format = parsePrecision(format, spec, args);
  format = parseLength(format, spec);
  format = parseSpecifier(format, spec);

  return format;
}