#include <stdarg.h>
#include <stdio.h>
#ifndef SPRINTF_UTILS_H
#define SPRINTF_UTILS_H

#define MAX_TMP_SIZE 64 
#define MAX_EXP_DIGITS 512  // Максимальная разумная точность
#define MAX_PATTERN_LEN 256

typedef struct {
    unsigned int use_suppress : 1; //используется подавление 
    char scan_set[MAX_PATTERN_LEN]; // для  %*[...] 
    int inverted; //будем ли инвертировать набор 
    int width; // ширина '-'
    char length;// длина
    char specifier; // спецификатор
} formatSpec;


int str_to_int(const char **source, long long *res, formatSpec spec);
const char *pass_spaces(const char *source);
int formatScanfBySpecifier(formatSpec *spec, va_list *args, const char **source, int *count);
const char *parseScanfFormat(const char *format, formatSpec *spec);
int process_char(const char **source, char *res, formatSpec spec);
/*char *double_to_exp_str(char *buf, long double val, formatSpec spec, int *len);
int parseFlag(char input);
const char* parseFlags(const char *format, formatSpec *spec);
const char* parseWidth(const char *input, formatSpec * spec);
const char* parseLength(const char *format, formatSpec * spec);
const char* parseSpecifier(const char *format, formatSpec *spec); 
const char* parseFormat(const char *format, formatSpec * spec);
void formatBySpecifier(formatSpec *spec, va_list *args, char **out, char *start);
//char *handle_precision(char *buf, int length, char spec);
char *handle_width(char *buf, int length, formatSpec spec);
char *handle_special_floats(char *buf, long double val, formatSpec spec, int *len);
char *float_to_str(char *buf, long double num, formatSpec spec, int *len);
char *g_spec(char *buf, long double val, formatSpec spec, int *len, char *start);
char *o_spec(char *buf, unsigned long long val, formatSpec spec, int *len);
char *hex_spec(char *buf, unsigned long long val, formatSpec spec, int *len);
char *u_spec(char *buf, unsigned long long val, formatSpec spec, int *len);
char *pointer_to_str(char *buf, void *pointer, formatSpec spec, int *len);*/

#endif
