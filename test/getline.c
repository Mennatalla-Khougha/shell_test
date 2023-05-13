#include "main.h"

ssize_t _getline(char **line, size_t *n, int stream)
{
    ssize_t read_line, total = 0;
    char *buffer;

    if (line == NULL || n == NULL)
        return (-1);
    buffer = malloc(8);
    if (buffer == NULL)
        return (-1);
    *n = 8;
    if(*line)
        free(*line);
    do{
        while ((read_line = read(stream, buffer + total, 8)) > 0)
        {
            total += read_line;
            if (buffer[total - 1] == '\n' || (size_t)total > *n)
                break;
        }
        if (read_line > 0 && buffer[total - 1] != '\n')
        {
            buffer = _realloc(buffer, total, total + 120);
            *n += 120;
            if (buffer == NULL)
            {
                free(buffer);
                return (-1);
            }
        }
    } while (read_line > 0 && buffer[total - 1] != '\n');
    if (read_line < 0)
    {
        free (buffer);
        return (-1);
    }
    if (!read_line && !total)
        return (-1);
    *line = buffer;
    return (total);
}

/* int main(void)
{
    size_t n = 0;
    char *line, *ptr;
    ssize_t read;

    read = _getline(&line, &n, 0);
    printf("%s\n%ld\n%ld\n", line, read, n);

    free(line);
    return (0);
} */