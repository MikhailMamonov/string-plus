#include "s21_sscanf.h"
#include <math.h>
#define MAX 9223372036854775807

int str_to_int(const char **source, long long *res, formatSpec spec) {
    int len = 0;
    int is_negative = 0;
    if (spec.width == 0) {
        return 0;
    }
    int width_defined = 0;
    if (spec.width > 0) {
        width_defined = 1;
    }
    int width_counter = 0;
    const char *curr = *source;
    unsigned long long max = MAX;
    if (*curr == '-') {
        is_negative = 1;
        max++;
        (curr)++;
        width_counter++;
    } else if (*curr == '+')
    {
        (curr)++;
        width_counter++;
    }
    unsigned long long res_l = 0;
    while (*curr >= '0' && *curr <= '9' && (!width_defined || width_counter < spec.width)) {
        if (res_l != max) {
            if (res_l == 0 || max / res_l >= 10) {
                if (res_l != 0 && max / res_l == 10) {
                    if ((unsigned int)*curr - '0' <= max % 10) {
                        res_l = res_l * 10 + (*curr - '0');
                    }
                    else {
                        res_l = max;
                    }
                }
                else {
                    res_l = res_l * 10 + (*curr - '0');
                }
            }
            else {
                res_l = max;
            }
            len++;
        }
        width_counter++;
        (curr)++;
    }
    if (len == 0) {
        return 0;
    }
    if (is_negative) {
        *res = (long long)(-res_l);
    }
    else {
        *res = res_l;
    }
    *source = curr;
    return 1;
}