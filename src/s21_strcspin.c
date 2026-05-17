#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2){
    unsigned char * dest_char = dest;
    const unsigned char * src_char= src;

    for(s21_size_t i = 0;i<n;i++){
        dest_char[i] = src_char[i];
    }

    return dest;
}
