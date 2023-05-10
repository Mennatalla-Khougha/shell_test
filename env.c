#include "main.h"

int main(int __attribute__ ((unused)) argc, char __attribute__ ((unused))**argv, char **env) 
{
    int i;

    for (i = 0; env[i] != NULL; i++) 
    {
        printf("%s\n", env[i]);
    }
    return 0;
}

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	p = malloc(new_size);
	if (p == NULL)
		return (NULL);
	if (ptr == NULL)
	{
		return (p);
	}
	for (i = 0; i < old_size; i++)
	{
		p[i] = ((char *) ptr)[i];
	}

	free(ptr);
	return (p);
}


/**
 * _atoi - convert a string to an int.
 * @s: string.
 * Return: the numbers in string
 */

int _atoi(char *s)
{
	int i = 0;
	int j;
	int sign = -1;
	int n = 0;


	while (s[i] != 0)
		i++;

	for (j = 0; j < i; j++)
	{
		if (s[j] == '-')
			sign *= -1;
		if (s[j] > 47 && s[j] < 58)
		{
			if (n < 0)
				n = (n * 10) - (s[j] - 48);
			else
				n = (s[j] - 48) * -1;

			if (s[j + 1] < 48 || s[j + 1] > 57)
				break;
		}
	}
	if (sign < 0)
		n *= -1;

	return (n);
}