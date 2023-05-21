#include "main.h"

/**
 * _realloc - change buffer size and copy the content of the buffer.
 * @ptr: old buffer.
 * @old_size: the buffer old size.
 * @new_size: the buffer new size.
 * Return: the new buffer.
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *buffer;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	buffer = malloc(new_size);
	if (buffer == NULL)
		return (NULL);
	if (ptr == NULL)
		return (buffer);
	for (i = 0; i < old_size && i < new_size; i++)
	{
		buffer[i] = ((char *) ptr)[i];
	}

	free(ptr);
	return (buffer);
}

/**
 * _atoi - convert a string to an int.
 * @str: string.
 * Return: the numbers in string
 */

int _atoi(char *str)
{
	int i = (_strlen(str) - 1), j, num = 0, power = 1;

	for (j = 0; j <= i; j++)
	{
		if (str[i - j] > 47 && str[i - j] < 58)
		{
			num += (str[i - j] - 48) * power;
			power *= 10;
		}
		else
			return (-1);
	}
	return (num);
}

/**
 * _get_env - get specific environmental variable.
 * @envp: array of environmental variable.
 * @env: the variable to search for.
 * @len: length of the variable to search for.
 * Return: the variable or NULL if not found.
*/

char *_get_env(char **envp, char *env, int len)
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (_strncmp(envp[i], env, len) == 0)
			return (&envp[i][len + 1]);
	}
	return (NULL);
}

/**
 * _env - check if the input is env and provide it if it is.
 * @envp: array of environmental variables
 * @line: input
 * Return: 1 input = env, 0 input != env.
*/
int _env(char **envp, char *line)
{
	int i;

	if (rev_cmp(line, "env"))
	{
		for (i = 0; envp[i] != NULL; i++)
		{
			write(1, envp[i], _strlen(envp[i]));
			write(1, "\n", 1);
		}
		return (1);
	}
	return (0);
}
