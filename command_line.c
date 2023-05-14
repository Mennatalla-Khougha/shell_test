#include "main.h"

void _command_(char *ptr, char *argv, char *path, int argc, int path_c, int count, char **envp)
{
    int i;

    if(ptr[0] == '/')
    {
        if (access(ptr, X_OK) == 0)
        {
            if (!_env(envp, ptr))
                _exceve(ptr, argc, ptr);
        }
        else
            _printf("%s: %i: %s: not found\n", argv, count, ptr);
    }
    else
    {
        for(i = 0; i < path_c; i++)
        {
            char buffer[1024] = "";
            _strcat(buffer, path);
            _strcat(buffer, "/");
            _strcat(buffer, ptr);
            if (access(buffer, X_OK) == 0) 
            {
                if (!_env(envp, ptr))
                    _exceve(ptr, argc, buffer);
                break;
            }
            path += _strlen(path) + 1;
        }
        if(i == path_c){
            _printf("%s: %i: %s: not found\n", argv, count, ptr);
        }
    }
}

void input(char **line, size_t *n)
{
    ssize_t read;

    read = _getline(line, n, 0);
        if (read == -1)
            exit(0);
        if ((*line)[read - 1] == '\n')
            (*line)[read - 1] = '\0';
}

int token(char *line, char *delim)
{
    int argc = 0;
    char *_token = strtok(line, delim);

    while (_token)
    {
        _token = strtok(NULL, delim);
        argc++;
    }
    return(argc);
}