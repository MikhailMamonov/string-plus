#include "s21_string.h"
#include <ctype.h>


typedef struct {
    unsigned int left_align : 0; // флаг '-'
    unsigned int show_sign : 0;// флаг '+'
    unsigned int space_sign : 1; // флаг ' ' 
    unsigned int alt_format : 1;  // флаг '#'
    unsigned int zero_padding : 1;   // флаг '0'
    int width; // ширина '-'
    int precision; // точность
    char length;// длина
    char specifier; // спецификатор
} formatSpec;


int parseFlag(char input){
    return (input == '+' || input == '-' || input == ' ' || input == '#' || input == '0');
}

char* parseWidth(char *input, formatSpec * spec, va_list* args){
     if (*input == '*') {
        spec->width = va_arg(*args, int);
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
        input++;
    } else if (isdigit(*input)) {
        spec->precision = 0;
        while (isdigit(*input)) {
            spec->precision = spec->precision * 10 + (*input - '0');
            input++;
        }
    }
    else{
        spec->precision = 0;
    }
    } 
    return input;
}


char* parseLength(char *format, formatSpec * spec){
    if(input == 'l' || input == 'L' || input == 'h'){
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

int parseSpecifier(char input){
    return (input && s21_strchr("diouxXeEfgGcspn%", input) != NULL);
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

     if (parseSpecifier(*format)) {
        spec->specifier = *format;
        format++;
    }

} 

int s21_sprintf(char *str, const char *format, ...) {
    int len = 0;
    while(*format!='\0'){
        if(*format=='%'){
            format++;
            if(*format=='%'){
                *str++ = *format;
                format++;
                len++;  
                continue;
            }
            formatSpec spec = {0};
            format = parseFormat(format, &spec); 

            // Форматируем на основе spec
            // format_specifier(&str, &spec, &args);
        } else{
            *str++ = *format++;
            len++;
        }
    }
    *str = '\0';
    return len;
}