#include "../s21_string.h"

#define NEGATIVE_VALUE -1
#define POSITIVE_VALUE 1

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;
  int ret = 0;

  for (s21_size_t i = 0; i < n; i++) {
    // Если символы различаются или мы дошли до конца одной из строк
    if (s1[i] != s2[i] || s1[i] == '\0') {
      ret = s1[i] - s2[i];
      break;
    }
  }
  if (ret < 0)
    ret = NEGATIVE_VALUE;
  if (ret > 0)
    ret = POSITIVE_VALUE;
  return ret;
}
