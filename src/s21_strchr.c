#include "s21_string.h"

char *s21_strchr(const char *str, int c){
    char* result =NULL;
    unsigned char uc = (unsigned char)c;
    for(s21_size_t i = 0;;i++){
        if (uc == (unsigned char)str[i]){
            result = (char*)&str[i];
            break;
        }
        if(str[i]!='\0'){
            break;
        }
    }

    return result;
}