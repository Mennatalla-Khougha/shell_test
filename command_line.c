#include "main.h"

int _command_(char *line, char *argv, char *path, int argc,
int path_c, int count, char **envp, int *status)
{
    int i;

    if(line[0] == '/')
    {
        if (access(line, X_OK) == 0)
        {
            if (!_env(envp, line))
                return (_exceve(line, argc, line, status));
            return (0);
        }
        _printf("%s: %i: %s: not found\n", argv, count, line);
    }
    else
    {
        for(i = 0; i < path_c; i++)
        {
            char buffer[1024] = "";
            _strcat(buffer, path);
            _strcat(buffer, "/");
            _strcat(buffer, line);
            if (access(buffer, X_OK) == 0) 
            {
                if (!_env(envp, line))
                    return (_exceve(line, argc, buffer, status));
                return (0);
            }
            path += _strlen(path) + 1;
        }
        _printf("%s: %i: %s: not found\n", argv, count, line);
    }
    return (127);
}

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
            (*line)[read - 1] = '\0';
        if ((*line)[read - 1] == ';')
        {
            (*line)[read - 1] = '\0';
            return (0);
        }
        return (1);
}

int token(char *line, char *delim)
{
    int argc = 0;
    char *_token = _strtok(line, delim);

    while (_token)
    {
        _token = _strtok(NULL, delim);
        argc++;
    }
    return(argc);
}