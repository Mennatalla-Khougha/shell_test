#include "main.h"

int _strlen(char *s)
{
	int i = 0;

	while (s[i] != 0)
	{
		i++;
	}

	return (i);
}

int main(){
    char *buff = malloc(1024);
    buff[0] = '\0';
    printf("%d\n", _strlen(buff));
}