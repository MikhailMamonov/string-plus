#include <math.h> 
#include "sprintf_utils.h"

char *write_exp(char *buf, formatSpec spec, double val, int exponent, int is_negative, int *len);

char *double_to_exp_str(char *buf, double val, formatSpec spec, int *len) {
    // 1. Сразу определяем и сохраняем знак
    int is_negative = signbit(val);
    val = fabs(val);

    int exponent = 0;
    if (val != 0.0) {
        exponent = (int)floor(log10(val));
        // Используем умножение для отрицательных степеней во избежание потери точности
        val *= pow(10, -exponent);
    }

    if (spec.precision < 0) spec.precision = 6;

    // 2. Округление мантиссы
    double round_offset = 0.5 / pow(10, spec.precision);
    val += round_offset;

    if (val >= 10.0) {
        val /= 10.0;
        exponent++;
    }

    // 3. Отсекаем лишний «хвост», который остался после round_offset
    // Например, если было 1.234 + 0.005 = 1.239, делаем из него строго 1.230
    double factor = pow(10, spec.precision);
    val = floor(val * factor) / factor;

    return write_exp(buf, spec, val, exponent, is_negative, len);
}

char *write_exp(char *buf, formatSpec spec, double val, int exponent, int is_negative, int *len) {
    char *start = buf;
    // Выводим сохраненный знак
    if (is_negative) {
        *buf++ = '-';
    }

    // Запись целой части
    int digit = (int)val;
    *buf++ = digit + '0';
    val -= digit;

    // Запись дробной части
    if (spec.precision > 0) {
        *buf++ = '.';
        for (int i = 0; i < spec.precision; i++) {
            val *= 10.0;
            digit = (int)val;
            *buf++ = digit + '0';
            val -= digit;
        }
    }

    // Запись экспоненты
    *buf++ = spec.specifier; // 'e' или 'E'
    if (exponent >= 0) {
        *buf++ = '+';
    } else {
        *buf++ = '-';
        exponent = -exponent;
    }

    // Вывод порядка (минимум 2 цифры)
    if (exponent < 10) {
        *buf++ = '0';            
        *buf++ = exponent + '0';
    } else {
        char temp_exp[4];
        int i = 0;
        while (exponent > 0) {
            temp_exp[i++] = (exponent % 10) + '0';
            exponent /= 10;
        }
        while (i > 0) {
            *buf++ = temp_exp[--i];
        }
    }
    *len = buf - start;
    return buf; 
}


