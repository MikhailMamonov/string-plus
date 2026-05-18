#include "s21_string.h"

char *s21_strchr(const char *str, int c){
    char* result =s21_NULL;
    if(str != s21_NULL){
        unsigned char search_char = (unsigned char)c;
        while (*str != '\0') {
            if ((unsigned char)*str == search_char) {
                result = (char *)str;
                break;
            }
            str++;
        }
        if (search_char == '\0') {
            result = (char *)str;
        }
    }
    
    return result;
}