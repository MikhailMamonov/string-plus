#include "sprintf_utils.h"
#include <stdarg.h>


void formatWidth(formatSpec *spec, va_list *args, char **out){
    while(spec->width>strlen(str)){
        *(*out)++ = ' ';
    }
}

// Отдельная функция для форматирования
void formatBySpecifier(formatSpec *spec, va_list *args, char **out) {
    formatWidth
    switch (spec->specifier) {
        case 'c': {
            char c = (char)va_arg(*args, int);
            *(*out)++ = c;
            break;
        }
        case 's': {
            char *s = va_arg(*args, char*);
            while (*s) {
                *(*out)++ = *s++;
            }
            break;
        }
        case 'd': {
            int d = va_arg(*args, int);
            *out = int_to_str(*out, d);
            break;
        }
        case 'u': {
            unsigned int u = va_arg(*args, unsigned int);
            *out = uint_to_str(*out, u);
            break;
        }
        case 'x':
        case 'X': {
            unsigned int hex = va_arg(*args, unsigned int);
            *out = hex_to_str(*out, hex, spec->specifier == 'X');
            break;
        }
        case '%': {
            *(*out)++ = '%';
            break;
        }
        default: {
            *(*out)++ = '%';
            if (spec->specifier) {
                *(*out)++ = spec->specifier;
            }
            break;
        }
    }
}