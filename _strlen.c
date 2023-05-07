#include "main.h"

/**
 * _strlen - determine the length of a string.
 * @s: a string of char.
 * Return: the length of a string.
 */

int _strlen(char *s)
{
	int i = 0;

	while (s[i] != 0)
	{
		i++;
	}

	return (i);
}