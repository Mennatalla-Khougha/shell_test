#include "main.h"

void handle_input(char **line, int val, int pid, char **envp)
{
    char *ptr = malloc(1024);
    char *dollar;
    char *start;
    char *hash = strchr(*line, '#');

    if(hash && ((hash != *line && *(hash - 1) == ' ') || hash == *line))
        *hash = '\0';


    dollar = strchr(*line, '$');
    start = *line;
    ptr[0] = '\0';
    while(dollar)
    {
        strncat(ptr, start, dollar - start);
        handle_dollar(ptr, &dollar, val, pid, envp);
        start = dollar;
        dollar = strchr(start, '$');
    }
    strcat(ptr, start);
    space(&ptr);
    free(*line);
    *line = ptr;
}

void handle_dollar(char *ptr, char **s, int val, int pid, char **envp)
{
    char *num;
    char *env;
    int n = 0;

    (*s)++;
    if ((*s)[0] == '$')
    {
        num = malloc(10);
        tostring(num, pid);
        strcat(ptr, num);
        (*s)++;
        free(num);
    }
    else if ((*s)[0] == '?')
    {
        num = malloc(4);
        tostring(num, val);
        strcat(ptr, num);
        (*s)++;
        free(num);
    }
    else{
        while((*s)[n] && (*s)[n] != ' ' && (*s)[n] != '#')
            n++;
        if(!n)
            strcat(ptr, "$");
        
        else{
            env = _get_env(envp, *s, n) ;
            if(env)
                strcat(ptr, env);
            *s += n;
        }

    }
}

