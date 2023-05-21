#include "main.h"

/**
* input - determine if we start new line in the shell with an arrow.
* @line: buffer to read the line to.
* @n: size of buffer.
* @file: 0 stdin, -1 error accessing the file or nonnegative int file input .
* Return: 0, 1
*/

int input(char **line, size_t *n, int file)
{
	ssize_t read;

	read = _getline(line, n, file);
	if (read == -1)
	{
		close(file);
		exit(0);
	}
	if ((*line)[read - 1] == '\n')
	{
		(*line)[read - 1] = '\0';
	}
	if ((*line)[read - 1] == ';')
	{
		(*line)[read - 1] = '\0';
		return (0);
	}
	return (1);
}

/**
 * _getline - read an entire line from a stream.
 * @line: buffer to read the line into.
 * @n: size of buffer.
 * @stream: type of stream to read from.
 * Return: no of chars read from the stream.
*/

ssize_t _getline(char **line, size_t *n, int stream)
{
	size_t i = 0;
	ssize_t read_line;
	char *buffer;
	int buffer_size = 8;

	if (line == NULL || n == NULL)
		return (-1);
	buffer = malloc(buffer_size);
	if (buffer == NULL)
		return (-1);
	if (*line)
		free(*line);
	while ((read_line = read(stream, buffer + i, 1)) > 0)
	{
		i++;
		if (buffer[i - 1] == '\n' || buffer[i - 1] == ';')
			break;
		buffer = handle_realloc(buffer, &buffer_size, 8, i);
	}
	if (read_line < 0 || (!read_line && !i))
	{
		free(buffer);
		return (-1);
	}
	if (read_line != 8)
		buffer[i] = '\0';
	*line = buffer;
	*n = (size_t)buffer_size;
	return (i);
}

/**
 * handle_input - determine if line contain $ or # and act accordingly.
 * @line: input.
 * @status: status of the last command.
 * @pid: shell process id.
 * @envp: array of environmental variables.
*/

void handle_input(char **line, int status, int pid, char **envp)
{
	char *buffer, *dollar, *start, *hash = _strchr(*line, '#');
	int buffer_size = 1024;

	if (hash && ((hash != *line && *(hash - 1) == ' ') || hash == *line))
		*hash = '\0';
	buffer = malloc(buffer_size);
	if (buffer == NULL)
		return;
	dollar = _strchr(*line, '$');
	start = *line;
	buffer[0] = '\0';
	while (dollar)
	{
		buffer = handle_realloc(buffer, &buffer_size, 1024, _strlen(buffer) + dollar - start);
		_strncat(buffer, start, dollar - start);
		handle_dollar(buffer, &dollar, status, pid, envp);
		start = dollar;
		dollar = _strchr(start, '$');
	}
	buffer = handle_realloc(buffer, &buffer_size, 128, _strlen(buffer) + _strlen(start));
	_strcat(buffer, start);
	space(&buffer);
	free(*line);
	*line = buffer;
}

/**
 * handle_dollar - handle input containing $ sign.
 * @buffer: input containing $.
 * @dollar: input starting from $ sign.
 * @status: status of the last command.
 * @pid: shell process id.
 * @envp: array of environmental variables.
*/
void handle_dollar(char *buffer, char **dollar, int status, int pid,
		char **envp)
{
	char *num, *env;
	int i = 0;

	(*dollar)++;
	if ((*dollar)[0] == '$' || (*dollar)[0] == '?')
	{
		num = malloc(10);
		if (num == NULL)
			return;
		if ((*dollar)[0] == '$')
			tostring(num, pid);
		else
			tostring(num, status);
		_strcat(buffer, num);
		(*dollar)++;
		free(num);
	}
	else
	{
		while ((*dollar)[i] && (*dollar)[i] != ' ' && (*dollar)[i] != '#')
			i++;
		if (!i)
			_strcat(buffer, "$");
		else
		{
			env = _get_env(envp, *dollar, i);
			if (env)
				_strcat(buffer, env);
			*dollar += i;
		}
	}
}

/**
 * space - handle extra spaces in the input.
 * @line: input
*/

void space(char **line)
{
	int i = 0, j = 0;
	char *buffer = malloc(_strlen(*line));

	if (buffer == NULL)
		return;
	while ((*line)[i] && (*line)[i] == ' ')
		i++;
	while ((*line)[i])
	{
		if ((*line)[i] == ' ')
		{
			buffer[j] = ' ';
			j++;
			while ((*line)[i] == ' ')
				i++;
		}
		else
		{
			buffer[j] = (*line)[i];
			i++;
			j++;
		}
	}
	if (buffer[j - 1] == ' ')
		j--;
	buffer[j] = '\0';
	free(*line);
	*line = buffer;
}
