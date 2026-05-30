#include "s21_sscanf.h"
#include <math.h>
#define MAX 9223372036854775807

int base_determinator(formatSpec spec, const char **curr, int *width_counter, int *is_hex_prefix);
void sign_parser(const char **curr, int *width_counter, int *is_negative);
int get_digit(char c);

int str_to_int(const char **source, long long *res, formatSpec spec) {
    int len = 0;
    int is_negative = 0;
    int width_defined = 0;
    if (spec.width > 0) {
        width_defined = 1;
    }
    int width_counter = 0;
    const char *curr = *source;
    unsigned long long max = MAX;
    sign_parser(&curr, &width_counter, &is_negative);
    if (is_negative) {
        max++;
    }
    int is_hex_prefix = 0;
    int base = base_determinator(spec, &curr, &width_counter, &is_hex_prefix);
    unsigned long long res_l = 0;
    int digit = get_digit(*curr);
    while (digit != -1 && digit < base && (!width_defined || width_counter < spec.width)) {
        if (res_l != max) {
            if (res_l == 0 || max / res_l > (unsigned int)base) {
                // Гарантированный успех: мы еще очень далеко от предела
                res_l = res_l * base + digit;
            } 
            else if (max / res_l == (unsigned int)base) {
                // Мы на критической черте: нужно точечно проверить последнюю цифру
                if ((unsigned int)digit <= max % base) {
                    res_l = res_l * base + digit;
                } else {
                    res_l = max; // Переполнение на последней цифре
                }
            } 
            else {
                // Гарантированное переполнение: max / res_l < base
                res_l = max;
            }
            len++;
        }
        width_counter++;
        (curr)++;
        digit = get_digit(*curr);
    }
    if (len == 0) {
        if (is_hex_prefix) {
            curr--;
            res_l = 0;
        } else {
            return 0;
        }
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

int base_determinator(formatSpec spec, const char **curr, int *width_counter, int *is_hex_prefix) {
    int base = 0;
    int remaining_width = spec.width - *width_counter;
    if (spec.specifier == 'd') {
        base = 10;
    }
    if (spec.specifier == 'x' || spec.specifier == 'X') {
        if (**curr != '\0' && **curr == '0' && (*(*curr + 1) == 'x' || *(*curr + 1) == 'X') && (spec.width <= 0 || remaining_width >= 2)) {
            *width_counter += 2;
            (*curr) += 2;
            *is_hex_prefix = 1;
        }
        base = 16;
    }
    if (spec.specifier == 'o') {
        base = 8;
    }
    if (spec.specifier == 'i') {
        if (**curr != '\0' && **curr == '0' && (*(*curr + 1) == 'x' || *(*curr + 1) == 'X') && (spec.width <= 0 || remaining_width >= 2)) {
            (*curr) += 2;
            *width_counter += 2;
            *is_hex_prefix = 1;
            base = 16;
        } else
        if (**curr != '\0' && **curr == '0') {
            base = 8;
        }
        else {
            base = 10;
        }
    }
    return base;
}

void sign_parser(const char **curr, int *width_counter, int *is_negative) {
    if (**curr == '-') {
        *is_negative = 1;
        (*curr)++;
        (*width_counter)++;
    } else if (**curr == '+')
    {
        (*curr)++;
        (*width_counter)++;
    }
}

int get_digit(char c) {
    int digit = -1;
    if (c >= '0' && c <= '9') {
        digit = c - '0';
    } else if (c >= 'A' && c <= 'F') {
        digit = c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        digit = c - 'a' + 10;
    }
    return digit;
}