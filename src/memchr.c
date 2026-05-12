#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
    const unsigned char *p = (const unsigned char *)str;
    unsigned char target = (unsigned char)c;

    for (s21_size_t i = 0; i < n; i++) {
        if (p[i] == target) {
            return (void *)(p + i);
        }
    }
    return s21_NULL;
}
