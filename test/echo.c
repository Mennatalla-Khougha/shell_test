#include "main.h"

void _echo(char **ptr, int val, int pid)
{
    char *num;
    if(!strcmp(*ptr, "$$"))
    {
        num = malloc(10);
        tostring(num, pid);
        *ptr = num;
    }
    if(!strcmp(*ptr, "$?"))
    {
        num = malloc(4);
        tostring(num, val);
        *ptr = num;
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
          break;
        }
    }
    return (&envp[i][len]);
}