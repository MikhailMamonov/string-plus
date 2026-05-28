#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src,s21_size_t n){
    char *d = dest;
    s21_size_t i = 0;
    for (; i < n && *src != '\0' ; i++)
        *dest++ = *src++;
    for (; i < n; i++)
        *dest++ = '\0';
    return d;
}
