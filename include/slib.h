#ifndef OS_INCLUDE_SLIB_H
#define OS_INCLUDE_SLIB_H

unsigned int __strlen(const char *data);
char *__reverse(char *str);
void __itoa(int n, char s[]);
void* __memset(void *dest, int val, unsigned int len);

#endif //OS_INCLUDE_SLIB_H
