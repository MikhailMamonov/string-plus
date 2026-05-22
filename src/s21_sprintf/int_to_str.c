#include "sprintf_utils.h"

char *int_to_str(char *buf, long long num, int *len) {
  char tmp[12]; // Временный буфер для разворота числа
  int i = 0;
  int is_negative = 0;

  if (num == 0) {
    *buf++ = '0';
    *len = 1;
    return buf;
  }

  if (num < 0) {
    is_negative = 1;
    num = -num; // Делаем число положительным для деления
  }

  // Разбираем число на цифры с конца
  while (num > 0) {
    tmp[i++] = (num % 10) + '0';
    (*len)++;
    num /= 10;
  }

  if (is_negative) {
    *buf++ = '-';
  }

  // Записываем цифры в правильном порядке в основной буфер
  while (i > 0) {
    *buf++ = tmp[--i];
  }

  return buf; // Возвращаем указатель на текущую позицию в буфере
}
