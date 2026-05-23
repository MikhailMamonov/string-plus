#include "sprintf_utils.h"

char *hex_spec(char *buf, unsigned long long val, formatSpec spec, int *len) {
    if (val == 0) {
        if (spec.precision == 0) {
            *len = 0;
            return buf;
        }
        *buf++ = '0';
        *len = 1;
        return buf;
    }
    char *start = buf;
    if (spec.precision < 0) spec.precision = 1;
    int digits[32] = {0};
    int hex_len = 0;
    while (val > 0)
    {
        digits[hex_len++] = val % 16;
        val /= 16;
    }
    if (spec.alt_format) {
        *buf++ = '0';
        *buf++ = spec.specifier;
    }
    for (int i = 0; i < spec.precision - hex_len; i++) {
        *buf++ = '0';
    }
    for (int i = hex_len - 1; i >= 0; i--) {
        if (digits[i] < 10) *buf++ = digits[i] + '0';
        else if (spec.specifier == 'x') *buf++ = digits[i] - 10 + 'a';
         else if (spec.specifier == 'X') *buf++ = digits[i] - 10 + 'A';
    }

    *len = buf - start;
    return buf;
}