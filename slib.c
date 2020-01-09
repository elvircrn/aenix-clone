#include "include/slib.h"

unsigned int __strlen(const char *data) {
  const char *ptr = data;
  if (!ptr) {
    return 0;
  }
  while (*(ptr++)) {
  }
  return ptr - data - 1;
}

void __itoa(int n, char *s) {
  int i, sign;

  if ((sign = n) < 0)        /* record sign */
    n = -n;                /* make n positive */
  i = 0;

  do {                       /* generate digits in reverse order */
    s[i++] = (n % 10) + '0'; /* get next digit */
  } while ((n /= 10) > 0);   /* delete it */

  if (sign < 0)
    s[i++] = '-';

  __reverse(s);
  s[i] = '\0';
}

char *__reverse(char *str) {
  char tmp, *src, *dst;
  unsigned int len;
  if (str) {
    len = __strlen(str);
    if (len > 1) {
      src = str;
      dst = src + len - 1;
      while (src < dst) {
        tmp = *src;
        *src++ = *dst;
        *dst-- = tmp;
      }
    }
  }
  return str;
}

void *__memset(void *dest, int val, unsigned int len) {
  unsigned char *ptr = dest;
  while (len-- > 0) {
    *ptr++ = val;
  }
  return dest;
}
