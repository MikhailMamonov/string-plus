#include <math.h> // Понадобятся функции log10, pow, floor

void double_to_exp_str(char *buf, double val, int precision, char specifier) {
    // 1. Обработка знака
    if (signbit(val)) {
        *buf++ = '-';
        val = -val;
    }

    // 2. Вычисление экспоненты (порядка)
    int exponent = 0;
    if (val != 0.0) {
        exponent = (int)floor(log10(val));
        // Приводим число к диапазону [1.0, 10.0)
        val /= pow(10, exponent);
    }

    // 3. Округление мантиссы до нужной точности
    if (precision < 0) precision = 6; // Точность по умолчанию
    double round_offset = 0.5 / pow(10, precision);
    val += round_offset;

    // Если после окружения получилось 10.0 (например, было 9.999), корректируем
    if (val >= 10.0) {
        val /= 10.0;
        exponent++;
    }

    // 4. Запись целой части (одна цифра)
    int digit = (int)val;
    *buf++ = digit + '0';
    val -= digit;

    // 5. Запись дробной части
    if (precision > 0) {
        *buf++ = '.';
        for (int i = 0; i < precision; i++) {
            val *= 10.0;
            digit = (int)val;
            *buf++ = digit + '0';
            val -= digit;
        }
    }

    // 6. Запись экспоненты
    *buf++ = specifier; // 'e' или 'E'
    if (exponent >= 0) {
        *buf++ = '+';
    } else {
        *buf++ = '-';
        exponent = -exponent;
    }

    // Универсальный вывод порядка (минимум 2 цифры)
    if (exponent < 10) {
        *buf++ = '0';            // Ведущий ноль для чисел 0-9
        *buf++ = exponent + '0';
    } else {
        // Если цифр 2 или 3 (максимум 308 для double)
        char temp_exp[4];
        int i = 0;
        while (exponent > 0) {
            temp_exp[i++] = (exponent % 10) + '0';
            exponent /= 10;
        }
        // Записываем цифры в правильном порядке
        while (i > 0) {
            *buf++ = temp_exp[--i];
        }
    }
    *buf = '\0';
}
