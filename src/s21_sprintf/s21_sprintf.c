#include "../s21_string.h"
#include <ctype.h>
#include "sprintf_utils.h"
#include <stdarg.h>



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
            formatSpec spec = {0};
            format = parseFormat(format, &spec, &args, &str); 

        } else{
            *str++ = *format++;
        }
    }
    *str = '\0';
    return str - start_str;
}
