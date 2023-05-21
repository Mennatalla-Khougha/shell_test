#include "main.h"

/* int _strncmp(const char* str1, const char* str2, size_t n) 
{
    while (n > 0 && (*str1 != '\0' || *str2 != '\0')) {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
        n--;
    }
    return 0;
} */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	do {
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 - *(unsigned char *)--s2);
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return (0);
}

int main(void)
{
    printf("%ld\n", "menna" - "me");
}
