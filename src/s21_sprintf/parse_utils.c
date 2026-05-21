#include "sprintf_utils.h"
#include <string.h>  // для memset
#include <ctype.h> 
#include <stdarg.h>

int parseFlag(char input){
    return (input == '+' || input == '-' || input == ' ' || input == '#' || input == '0');
}

char* parseWidth(char *input, formatSpec * spec, va_list* args){
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

char* parsePrecision(char *input, formatSpec * spec, va_list* args){
    if(*input == '.'){
        input++;
        if (*input == '*') {
        spec->precision = va_arg(*args, int);
        if (spec->precision < 0) {
                spec->precision = -1;  // Отрицательная точность игнорируется
        }
        input++;
    } else if (isdigit(*input)) {
        spec->precision = 0;
        while (isdigit(*input)) {
            spec->precision = spec->precision * 10 + (*input - '0');
            input++;
        }
    }
    } 
    return input;
}


char* parseLength(char *input, formatSpec * spec){
    if(*input == 'l' || *input == 'L' || *input == 'h'){
        spec->length = *input;
        input++;
        if (spec->length == 'l' && *input == 'l') {
            spec->length = 'L';  // или введите отдельный флаг
            input++;
        }
        // Поддержка short short (hh)
        if (spec->length == 'h' && *input == 'h') {
            spec->length = 'H';  // или введите отдельный флаг
            input++;
        }
    }

    return input;
}

int parseSpecifier(char input, formatSpec *spec) {
    if (input && s21_strchr("diouxXeEfgGcspn%", input) != NULL) {
        spec->specifier = input;
        return 1; 
    }
    return 0;
}

char* parseFormat(char *format, formatSpec * spec, va_list* args){
    memset(spec, 0, sizeof(formatSpec));
    spec->width = -1;
    spec->precision = -1;
    //Parse flags
    while(parseFlag(*format))
    {
        switch (*format) {
            case '-': spec->left_align = 1; break;
            case '+': spec->show_sign = 1; break;
            case ' ': spec->space_sign = 1; break;
            case '#': spec->alt_format = 1; break;
            case '0': spec->zero_padding = 1; break;
        }
        format++;
    } 
    // Parse width
    format = parseWidth(format, spec, args);

    //Parse precision
    format = parsePrecision(format, spec, args);

    //Parse length
    format = parseLength(format, spec);

    if (parseSpecifier(*format, spec)) {
        format++; 
    }

    return format;
}