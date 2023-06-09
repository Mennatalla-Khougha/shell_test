#include "main.h"

/**
* input - determine if we start new line in the shell with an arrow.
* @line: buffer to read the line to.
* @n: size of buffer.
* @file: 0 stdin, -1 error accessing the file or nonnegative int file input .
* Return: 0, 1
*/

int input(para *args)
{
	ssize_t read;

	read = _getline(args);
	if (read == -1)
	{
		close(args->file);
		free(args->line);
		free(args->path);
		free(*(args->pwd));
		free(args->old_pwd);
		exit(args->status);
	}
	if (args->line[read - 1] == '\n')
	{
		args->line[read - 1] = '\0';
	}
	if (args->line[read - 1] == ';')
	{
		args->line[read - 1] = '\0';
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

ssize_t _getline(para *args)
{
	size_t i = 0;
	ssize_t read_line;
	char *buffer;
	int buffer_size = 8;

	if (&(args->line) == NULL)
		return (-1);
	buffer = _malloc(args, buffer_size);
	if (args->line)
	{
		free(args->line);
		args->line = NULL;
	}
	while ((read_line = read(args->file, buffer + i, 1)) > 0)
	{
		i++;
		if (buffer[i - 1] == '\n' || buffer[i - 1] == ';')
			break;
		buffer = handle_realloc(args, buffer, &buffer_size, 8, i);
	}
	if (read_line < 0 || (!read_line && !i))
	{
		free(buffer);
		return (-1);
	}
	if (read_line != 8)
		buffer[i] = '\0';
	args->line = buffer;
	return (i);
}

/**
 * handle_input - determine if line contain $ or # and act accordingly.
 * @line: input.
 * @status: status of the last command.
 * @pid: shell process id.
 * @envp: array of environmental variables.
*/

void handle_input(para *args)
{
	char *buffer, *dollar, *start, *hash = _strchr(args->line, '#');
	int buffer_size = 1024;

	if (hash && ((hash != args->line && *(hash - 1) == ' ') || hash == args->line))
		*hash = '\0';
	buffer = _malloc(args ,buffer_size);
	if (buffer == NULL)
		return;
	dollar = _strchr(args->line, '$');
	start = args->line;
	buffer[0] = '\0';
	while (dollar)
	{
		buffer = handle_realloc(args, buffer, &buffer_size, 1024, _strlen(buffer) + dollar - start);
		_strncat(buffer, start, dollar - start);
		handle_dollar(buffer, &dollar, args);
		start = dollar;
		dollar = _strchr(start, '$');
	}
	buffer = handle_realloc(args, buffer, &buffer_size, 128, _strlen(buffer) + _strlen(start));
	_strcat(buffer, start);
	space(&buffer, args);
	free(args->line);
	args->line = buffer;
}

/**
 * handle_dollar - handle input containing $ sign.
 * @buffer: input containing $.
 * @dollar: input starting from $ sign.
 * @status: status of the last command.
 * @pid: shell process id.
 * @envp: array of environmental variables.
*/
void handle_dollar(char *buffer, char **dollar, para *args)
{
	char num[10], *env;
	int i = 0;

	(*dollar)++;
	if ((*dollar)[0] == '$' || (*dollar)[0] == '?')
	{
		if ((*dollar)[0] == '$')
			tostring(num, args->pid);
		else
			tostring(num, args->status);
		_strcat(buffer, num);
		(*dollar)++;
	}
	else
	{
		while ((*dollar)[i] && (*dollar)[i] != ' ' && (*dollar)[i] != '#' && (*dollar)[i] != '$' && (*dollar)[i] != '/')
			i++;
		if (!i)
			_strcat(buffer, "$");
		else
		{
			env = _get_env(args->envp, *dollar, i);
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

void space(char **line, para *args)
{
	int i = 0, j = 0;
	char *buffer = malloc(_strlen(*line));

	if (buffer == NULL)
	{
		free(line);
		free_exit(args);
	}
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
