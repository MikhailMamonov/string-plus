#include "../s21_string.h"
#include <ctype.h>
#include "sprintf_utils.h"
#include <stdarg.h>

typedef struct {
    int flags;
    int width;
    int precision;
    char length;
    char specifier;
} formatSpec;

int parseFlag(char input){
    return (input == '+' || input == '-' || input == ' ' || input == '#' || input == '0');
}

int parseWidth(char input){
     return (input == '*' || isdigit(input));
}

void parseAccuracy(char **input){
    if(**input == '.' ){
        (*input)++;
        while(isdigit(**input))
        {
            (*input)++;
        }
    }
}

int parseLength(char input){
    return (input == 'l' || input == 'L' || input == 'h');
}

void parseSpecifier(char input, va_list *args, char **out) {
    if (input && s21_strchr("diouxXeEfgGcspn%", input) != NULL) {
        switch (input) {
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
            case '%': {
                *(*out)++ = '%';
                break;
            }
            default: {
                *(*out)++ = '%';
                *(*out)++ = input;
                break;
            }
        }
    }
}

int s21_sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *start_str = str; // Запоминаем начало для подсчета длины
    while(*format!='\0'){
        if(*format=='%'){
            format++;
            if(*format=='%'){
                *str++ = *format;
                format++;
                continue;
            }
            //Parse flags
            while(parseFlag(*format)){
                format++;
            } 
            // Parse width
            while(parseWidth(*format)){
                format++;
            }
            //Parse accuracy
            parseAccuracy(&format);

            if(parseLength(*format)){
                format++;
            }

            //Parse specifier
            parseSpecifier(*format, &args, &str);
            if (*format != '\0') {
                format++;
            }


        } else{
            *str++ = *format++;
        }
    }
    *str = '\0';
    return str - start_str; // ИСПРАВЛЕНО: надежный подсчет длины строки
}
