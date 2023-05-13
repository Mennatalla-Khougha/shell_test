#include "main.h"

int _env(char **env, char *ptr) 
{
    int i;

	if (rev_cmp(ptr, "env"))
	{
    	for (i = 0; env[i] != NULL; i++) 
    	{
        	write(1, env[i], _strlen(env[i]));
			write(1, "\n", 1);
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

/**
 * _strspn - gets the length of a prefix substring.
 * @s: segment.
 * @accept: bytes.
 * Return: number of bytes in the initial segment s.
 */

unsigned int _strspn(char *s, char *accept)
{
	unsigned int length = 0;
	int s_len = 0;
	int accept_len = 0;
	int i, j, chr_yes;

	while (s[s_len] != 0)
		s_len++;

	while (accept[accept_len] != 0)
		accept_len++;

	for (i = 0; i < s_len; i++)
	{
		chr_yes = 0;
		for (j = 0; j < accept_len; j++)
		{
			if (accept[j] == s[i])
			{
				chr_yes = 1;
				length++;
				break;
			}
		}
		if (chr_yes == 0)
			break;
	}

	return (length);
}

/**
 * _strpbrk - search a string for any set of bytes.
 * @s: string to be searched for.
 * @accept: number of bytes.
 * Return: pointer to matched bytes in s, or NULL if none found.
 */

char *_strpbrk(char *s, char *accept)
{
	int i, j;
	int s_len = 0, accept_len = 0;

	while (s[s_len] != 0)
		s_len++;

	while (accept[accept_len] != 0)
		accept_len++;

	for (i = 0; i < s_len; i++)
	{
		for (j = 0; j < accept_len; j++)
		{
			if (accept[j] == s[i])
			{
				return (s + i);
			}
		}
	}

	return (NULL);
}