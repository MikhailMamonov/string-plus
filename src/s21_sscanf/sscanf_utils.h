#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#ifndef SPRINTF_UTILS_H
#define SPRINTF_UTILS_H

#define MAX_TMP_SIZE 64
#define MAX_EXP_DIGITS 512  // Максимальная разумная точность
#define MAX_PATTERN_LEN 256

typedef struct {
  unsigned int use_suppress : 1;  // используется подавление
  int width;                      // ширина '-'
  char length;                    // длина
  char specifier;                 // спецификатор
} formatSpec;

int process_int(const char **source, long long *res, formatSpec spec);
const char *pass_spaces(const char *source);
int formatScanfBySpecifier(formatSpec *spec, va_list *args, const char **source,
                           int *count, const char *start);
const char *parseScanfFormat(const char *format, formatSpec *spec);
int process_char(const char **source, char *res, formatSpec spec);
int process_str(const char **source, char *res, formatSpec spec);
void sign_parser(const char **curr, int *width_counter, int *is_negative);
void handle_scanf_special_floats(const char **curr, int *width_counter,
                                 formatSpec spec, long double *res);
int process_float(const char **source, long double *res, formatSpec spec);
int handle_null_pointer(const char **curr, formatSpec spec);
#endif
