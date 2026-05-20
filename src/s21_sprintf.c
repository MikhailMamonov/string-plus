#include "s21_string.h"
#include <ctype.h>


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

int parseSpecifier(char input){
    return (input && s21_strchr("diouxXeEfgGcspn%", input) != NULL);
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
            if(parseSpecifier(*format)){
                format++;
                len++;
            }
        } else{
            *str++ = *format++;
            len++;
        }
    }
    *str = '\0';
    return len;
}