#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int count = 0;
  const char *start = str;
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      formatSpec spec = {0};
      format = parseScanfFormat(format, &spec);
      if (!format || spec.width == 0) {
        break;
      }
      if (!formatScanfBySpecifier(&spec, &args, &str, &count, start)) {
        if (*str == '\0' && count == 0) {
          count = EOF;
        }
        break;
      }
    } else if (isspace((unsigned char)*format)) {
      str = pass_spaces(str);
      format = pass_spaces(format);
    } else if (*str == '\0') {
      if (count == 0) {
        count = EOF;
      }
      break;
    } else if (*str != *format) {
      break;
    } else {
      format++;
      str++;
    }
  }
  va_end(args);
  return count;
}
