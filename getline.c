#include "main.h"

ssize_t _getline(char **line, size_t *n, int stream)
{
    ssize_t buffer_size = 8, new_size;
    ssize_t read_line, i = 0;
    char *buffer, *new_buffer;

    if (line == NULL || n == NULL)
        return (-1);
    buffer = malloc(buffer_size);
    if (buffer == NULL)
        return (-1);
    while ((read_line = read(stream, &buffer[i], 1)) > 0)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            break;
        }
        i++;
        if (i >= buffer_size)
        {
            new_size = buffer_size + 8;
            new_buffer = _realloc(buffer, buffer_size, new_size);
            if (new_buffer == NULL)
            {
                free(buffer);
                return (-1);
            }
            buffer = new_buffer;
            buffer_size = new_size;
        }
    }
    if (read_line < 0)
    {
        free (buffer);
        return (-1);
    }
    *line = buffer;
    *n = buffer_size;
    return (i);
}

int main(void)
{
    size_t n = 0;
    char *line, *ptr;
    ssize_t read;

    read = _getline(&line, &n, 0);
    printf("%s\n%ld\n", line, read);

    free(line);
    return (0);
}