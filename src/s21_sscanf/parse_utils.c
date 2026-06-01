#include "s21_sscanf.h"
#include <ctype.h>

const char *parseScanSet(const char *input, formatSpec *spec) {
  input++;

  // Обработка инвертированного набора %[^...]
  if (*input == '^') {
    spec->inverted = 1;
    input++;
  }

  // Чтение паттерна до ']'
  s21_size_t pos = 0;

  if (*input == ']') {
    if (pos < MAX_PATTERN_LEN - 1) {
      spec->scan_set[pos++] = ']';
      input++;
    } else {
      return s21_NULL; // Буфер слишком мал
    }
  }

  while (*input && *input != ']' && pos < MAX_PATTERN_LEN - 1) {
    spec->scan_set[pos++] = *input;
    input++;
  }

  if (*input == ']') {
    spec->scan_set[pos] = '\0';
    input++;
  } else {
    // Ошибка: нет закрывающей ']'
    spec->scan_set[0] = '\0';
    return s21_NULL;
  }

  return input;
}

const char *parseScanfWidth(const char *input, formatSpec *spec) {
  if (isdigit(*input)) {
    while (isdigit(*input)) {
      spec->width = spec->width * 10 + (*input - '0');
      input++;
    }
  }

  if (*input == '*') {
    spec->use_suppress = 1;
    input++;
    // Если ширина еще не установлена, устанавливаем ее
    if (spec->width == -1) {
      spec->width = 0;
      while (isdigit(*input)) {
        spec->width = spec->width * 10 + (*input - '0');
        input++;
      }
      if (spec->width == 0) {
        spec->width = -1;
      }
    } else {
      // Ширина уже есть до *, пропускаем цифры после * (нестандартно)
      // Лучше считать это ошибкой формата
      while (isdigit(*input)) {
        input++;
      }
    }
  }

  return input;
}

const char *parseScanfLength(const char *input, formatSpec *spec) {
  if (*input == 'l' || *input == 'L' || *input == 'h') {
    spec->length = *input;
    input++;
    if (spec->length == 'l' && *input == 'l') {
      spec->length = 'L'; // или введите отдельный флаг
      input++;
    }
    // Поддержка short short (hh)
    if (spec->length == 'h' && *input == 'h') {
      spec->length = 'H'; // или введите отдельный флаг
      input++;
    }
  }

  return input;
}

const char *parseScanfSpecifier(const char *format, formatSpec *spec) {
  static const char *specifiers = "diouxXeEfgGcspn%[";

  if (format && s21_strchr(specifiers, *format)) {
    spec->specifier = *format;

    return format + 1;
  }
  return format;
}

const char *parseScanfFormat(const char *format, formatSpec *spec) {
  s21_memset(spec, 0, sizeof(formatSpec));
  spec->width= -1;
  format = parseScanfWidth(format, spec);
  if (!format) {
    return s21_NULL;
  }
  if (*format == '[') {
    spec->specifier = '[';
    format = parseScanSet(format, spec);
    if (!format) {
      return s21_NULL;
    }
  } else {
    format = parseScanfLength(format, spec);
    if (!format) {
      return s21_NULL;
    }

    format = parseScanfSpecifier(format, spec);
    if (!format) {
      return s21_NULL;
    }
  }

  if (!spec->specifier && !spec->use_suppress) {
    return s21_NULL;
  }

  return format;
}