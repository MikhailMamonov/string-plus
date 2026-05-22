#include <stdarg.h>
#ifndef SPRINTF_UTILS_H
#define SPRINTF_UTILS_H

typedef struct {
    unsigned int left_align : 1; // флаг '-'
    unsigned int show_sign : 1;// флаг '+'
    unsigned int space_sign : 1; // флаг ' ' 
    unsigned int alt_format : 1;  // флаг '#'
    unsigned int zero_padding : 1;   // флаг '0'
    int width; // ширина '-'
    int precision; // точность
    char length;// длина
    char specifier; // спецификатор
} formatSpec;


char *int_to_str(char *buf, int num, int *len);
char *double_to_exp_str(char *buf, double val, formatSpec spec, int *len);
int parseFlag(char input);
const char* parseWidth(const char *input, formatSpec * spec, va_list* args);
const char* parsePrecision(const char* input, formatSpec * spec, va_list* args);
const char* parseLength(const char *format, formatSpec * spec);
int parseSpecifier(char input, formatSpec *spec); 
const char* parseFormat(const char *format, formatSpec * spec, va_list* args);
void formatBySpecifier(formatSpec *spec, va_list *args, char **out);
//char *handle_precision(char *buf, int length, char spec);
char *handle_width(char *buf, int length, formatSpec spec);
char *handle_special_floats(char *buf, double val, formatSpec spec, int *len);


#endif
