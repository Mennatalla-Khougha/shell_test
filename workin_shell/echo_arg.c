#include "main.h"

void _echo(char **ptr, int val, int pid, char **envp)
{
    char *num;
    char *str = _strdup(*ptr);
    
    if (str[0] == '$')
    {
        ++str;
        if (!strcmp(str, "$"))
        {
            num = malloc(10);
            tostring(num, pid);
            *ptr = num;
        }
        else if (!strcmp(str, "?"))
        {
            num = malloc(4);
            tostring(num, val);
            *ptr = num;
        }
        else if ( _get_env(envp, str) != NULL)
        {
            *ptr = _get_env(envp, str);
        }
        else 
        {
            *ptr = "\0";
        }
    }   
}



void tostring(char *str, int num)
{
    int i, len = 0, n;
 
    n = num;
    if (!n)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    while (n)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        str[len - (i + 1)] = num % 10 + '0';
        num /= 10;
    }
    str[len] = '\0';
}

char *_get_env(char **envp, char *env)
{
    int i, len = _strlen(env);

    for (i = 0; envp[i] != NULL; i++) {
        if (_strncmp(envp[i], env, len) == 0) {
           return (&envp[i][len + 1]);
        }
    }
    return (NULL);
}