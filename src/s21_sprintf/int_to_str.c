#include "sprintf_utils.h"

char *int_to_str(char *buf, long long num, int *len) {
  char tmp[64]; // Временный буфер для разворота числа
  int i = 0;
  int is_negative = 0;

  if (num == 0) {
    *buf++ = '0';
    *len = 1;
    return buf;
  }
  char *start = buf;
  unsigned long long u_num; 
  if (num < 0) {
    is_negative = 1;
    u_num = (unsigned long long)(-num);
  }
  else {
    u_num = (unsigned long long)num;
  }

  // Разбираем число на цифры с конца
  while (u_num > 0) {
    tmp[i++] = (u_num % 10) + '0';
    u_num /= 10;
  }

  if (is_negative) {
        *buf++ = '-';
  }


  // Записываем цифры в правильном порядке в основной буфер
  while (i > 0) {
    *buf++ = tmp[--i];
  }
  *len = buf - start;
  return buf; // Возвращаем указатель на текущую позицию в буфере
}
