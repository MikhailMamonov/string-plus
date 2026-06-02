#include "s21_string.h"
#include <stdlib.h>
#include <stdio.h>

void *s21_to_upper(const char *str){
    if(str == s21_NULL) return s21_NULL;

    s21_size_t len = s21_strlen(str);
    char *result = malloc(len + 1);
    if (result == s21_NULL) return s21_NULL;
    s21_size_t CASE = 'a' - 'A';
    for(s21_size_t i = 0; i < len; i++)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
            result[i] = str[i] - CASE;
        else result[i] = str[i];
    }
    result[len] = '\0';

    return result;
}
