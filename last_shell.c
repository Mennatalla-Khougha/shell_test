#include "main.h"

int _exceve(char *ptr, int arg_c, char *buff, int *status)
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
    wait(status);
    return (WEXITSTATUS(*status));
}

int main(int argc, char **argv, char **envp)
{
    size_t n = 0;
    char *line = NULL, *ptr, *env = _strdup(_get_env(envp, "PATH", 4));
    int arg_c, path_c = 0, count = 0, status = 0, arrow = 1, pid = (int)getpid();
    int file = 0;
    if(argc > 1)
    {
        file = open(argv[1], O_RDONLY);
        if (file == -1) {
        _printf("%s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
        exit(2);
        }
    }

    path_c = token(env, ":");

    while (1)
    {
        count++;
        if (isatty(STDIN_FILENO) && arrow && !file)
            write(1, "=> ", 3);
        arrow = input(&line, &n, file);
        ptr = handle_input(&line, status, pid, envp);
        arg_c = token(line, " ");
        if(_exit_(ptr, line, argv[0], arg_c, count, env))
        {
            status = 2;
            continue;
        }
        status = _command_(ptr, argv[0], env, arg_c, path_c, count, envp, &status);
    }
    return (0);
}