#include "s21_sscanf.h"

const char *parseScanfWidth(const char *input, formatSpec *spec) {
  if (*input == '*') {
    spec->use_suppress = 1;
    input++;
  }

  if (isdigit((unsigned char)*input)) {
    int parsed_width = 0;
    while (isdigit((unsigned char)*input)) {
      parsed_width = parsed_width * 10 + (*input - '0');
      input++;
    }

    if (parsed_width > 0) {
      spec->width = parsed_width;
    } else {
      spec->width = -1;
    }
  }
  return input;
}

const char *parseScanfLength(const char *input, formatSpec *spec) {
  if (*input == 'l' || *input == 'L' || *input == 'h') {
    spec->length = *input;
    input++;
    if (spec->length == 'l' && *input == 'l') {
      spec->length = 'L';
      input++;
    }
  }

  return input;
}

const char *parseScanfSpecifier(const char *format, formatSpec *spec) {
  static const char *specifiers = "diouxXeEfgGcspn%";

  if (format && s21_strchr(specifiers, *format)) {
    spec->specifier = *format;

    return format + 1;
  }
  return format;
}

const char *parseScanfFormat(const char *format, formatSpec *spec) {
  s21_memset(spec, 0, sizeof(formatSpec));
  spec->width = -1;
  format = parseScanfWidth(format, spec);
  if (!format) {
    return s21_NULL;
  }
  format = parseScanfLength(format, spec);
  if (!format) {
    return s21_NULL;
  }

  format = parseScanfSpecifier(format, spec);
  if (!format) {
    return s21_NULL;
  }

  if (!spec->specifier && !spec->use_suppress) {
    return s21_NULL;
  }

  return format;
}