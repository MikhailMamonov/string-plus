#include "s21_sscanf.h"
#include <ctype.h>

const char *parseScanSet(const char *input, formatSpec *spec)
{
  input++;

  // Обработка инвертированного набора %[^...]
  if (*input == '^')
  {
    spec->inverted = 1;
    input++;
  }

  // Чтение паттерна до ']'
  s21_size_t pos = 0;

  if (*input == ']')
  {
    if (pos < MAX_PATTERN_LEN - 1)
    {
      spec->scan_set[pos++] = ']';
      input++;
    }
  }

  while (*input && *input != ']' && pos < MAX_PATTERN_LEN - 1)
  {
    spec->scan_set[pos++] = *input;
    input++;
  }

  if (*input == ']')
  {
    spec->scan_set[pos] = '\0';
    input++;
  }
  else
  {
    // Ошибка: нет закрывающей ']'
    spec->scan_set[0] = '\0';
    return s21_NULL;
  }

  return input;
}

const char *parseWidth(const char *input, formatSpec *spec)
{
  // Сброс состояния
  spec->use_suppress = 0;
  spec->width = 0;
  spec->length = 0;
  spec->scan_set[0] = '\0';
  spec->inverted = 0;

  if (isdigit(*input))
  {
    spec->width = 0;
    while (isdigit(*input))
    {
      spec->width = spec->width * 10 + (*input - '0');
      input++;
    }
  }

  if (*input == '*')
  {
    spec->use_suppress = 1;
    input++;
    if (isdigit(*input))
    {
      // Не обнуляем! width уже может быть установле
      unsigned int w = 0;
      while (isdigit(*input))
      {
        w = w * 10 + (*input - '0');
        input++;
      }
      if (!spec->width)
      {
        spec->width = w;
      }
    }
  }

  if (*input == '[')
  {
    const char *next = parseScanSet(input, spec);
    if (!next)
    {                  // Проверка на ошибку
      return s21_NULL; // или input, в зависимости от дизайна
    }
    input = next;
  }

  return input;
}

const char *parseLength(const char *input, formatSpec *spec)
{
  if (*input == 'l' || *input == 'L' || *input == 'h')
  {
    spec->length = *input;
    input++;
    if (spec->length == 'l' && *input == 'l')
    {
      spec->length = 'L'; // или введите отдельный флаг
      input++;
    }
    // Поддержка short short (hh)
    if (spec->length == 'h' && *input == 'h')
    {
      spec->length = 'H'; // или введите отдельный флаг
      input++;
    }
  }

  return input;
}

const char *parseSpecifier(const char *format, formatSpec *spec)
{
  static const char *specifiers = "diouxXeEfgGcspn%";

  if (format && s21_strchr(specifiers, *format))
  {
    spec->specifier = *format;
    return format + 1;
  }
  return format;
}

const char *parseFormat(const char *format, formatSpec *spec)
{
  s21_memset(spec, 0, sizeof(formatSpec));

  format = parseWidth(format, spec);
  if (!format)
  {
    return s21_NULL;
  }
  format = parseLength(format, spec);

  if (!format)
  {
    return s21_NULL;
  }
  format = parseSpecifier(format, spec);
  if (!format)
  {
    return s21_NULL;
  }
  return format;
}