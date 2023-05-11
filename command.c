#include "main.h"

void _command_(char *ptr, char *argv, char *path, int argc, int path_c, int count)
{
    int i;

    if(ptr[0] == '/')
    {
        if (access(ptr, X_OK) == 0)
            _exceve(ptr, argc, ptr);
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