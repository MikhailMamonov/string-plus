#include "../s21_string.h"
#include <stdlib.h>

void *s21_to_upper(const char *str){
    if(str == s21_NULL) return s21_NULL;

    s21_size_t len = s21_strlen(str);
    char *result = malloc(len + 1);
    char *p_res = result;
    if (result == s21_NULL) return s21_NULL;
    s21_size_t CASE = 'a' - 'A';
    for(s21_size_t i = 0; i < len; i++)
    {
        if(*str >= 'a' && *str <= 'z')
            *p_res++ = *str++ - CASE;
        else *p_res++ = *str++;
    }
    *p_res = '\0';

    return result;
}
