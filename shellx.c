#include "main.h"

void _exceve(char *ptr, int arg_c, char *buff)
{
    int i;
    char **arg_v; 
    char *env[] = {NULL};
    pid_t id;
    id = fork();
    
    if (!id)
    {
        if(rev_cmp(ptr, "pwd")){
            arg_v = malloc(16);
            arg_v[0] = ptr;
            arg_v[1] = NULL;
        }
        else
        {
            arg_v = malloc(8 * (arg_c + 1));
            for (i = 0; i < arg_c; i++)
            {
                arg_v[i] = ptr;
                ptr += _strlen(ptr) + 1;
            }
            arg_v[i] = NULL;
        }
        execve(buff, arg_v, env);
        free(arg_v);
        exit(-1);
    }
    wait(NULL);
}

char *get_path(char **envp)
{
    int i;

    for (i = 0; envp[i] != NULL; i++) {
        if (_strncmp(envp[i], "PATH=", 5) == 0) {
          break;
        }
    }
    return (&envp[i][5]);
}
int main(int __attribute__ ((unused)) argc, char **argv, char **envp)
{
    size_t n = 0;
    char *line = NULL, *ptr, *env = _strdup(get_path(envp));
    int arg_c, path_c = 0, count = 0;

    path_c = token(env, ":");

    while (1)
    {
        count++;
        if (isatty(STDIN_FILENO))
            write(1, "=> ", 3);
        ptr = input(&line, &n);
        arg_c = token(line, " ");
        if(_exit_(ptr, line, argv[0], arg_c, count))
            continue;
        _command_(ptr, argv[0], env, arg_c, path_c, count, envp);
    }
    return (0);
}