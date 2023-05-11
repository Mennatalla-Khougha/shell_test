#include "main.h"

int _env(char **env, char *ptr) 
{
    int i;

	if (rev_cmp(ptr, "env"))
	{
    	for (i = 0; env[i] != NULL; i++) 
    	{
        	printf("%s\n", env[i]);
    	}
		return (1);
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
	int n = 0;
	int power = 1;


	while (s[i])
		i++;
	i--;
	for (j = 0; j <= i; j++)
	{
		if (s[i-j] > 47 && s[i-j] < 58)
		{
			n += (s[i-j] - 48) * power;
			power *= 10;
		}
		else
			return (-1);
	}
	return (n);
}