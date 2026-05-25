#include "sprintf_utils.h"
#include "../s21_string.h"

char *pointer_to_str(char *buf, void *pointer, formatSpec spec, int *len) {

    if (pointer == s21_NULL) {
        *buf++ = '(';
        *buf++ = 'n';
        *buf++ = 'i';
        *buf++ = 'l';
        *buf++ = ')';
        *len = 5;
        return buf;
    }

    unsigned long long p = (unsigned long long) pointer;
    spec.alt_format = 1;
    spec.precision = -1;
    spec.specifier = 'x';
    return hex_spec(buf, p, spec, len);
}