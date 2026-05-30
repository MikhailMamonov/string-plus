#include "s21_sscanf.h"
#include <ctype.h>

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  const char *check = str;
  check = pass_spaces(check);
  if (*check == '\0') {
    return -1;
  }
  int count = 0;
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      formatSpec spec = {0};
      format = parseFormat(format, &spec);
      if (!format) {
         break;
      }
      if (!formatBySpecifier(&spec, &args, &str, &count)) {
        break;
      }
    } else {
      if (isspace(*format)) {
        str = pass_spaces(str);
        format = pass_spaces(format);
      } else if (*str != *format) {
        break;
      } else {
        format++;
        str++;
      }
    }
  }
    return count;
}
