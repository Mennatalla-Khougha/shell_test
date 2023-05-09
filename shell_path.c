#include "main.h"

void _exceve(char *ptr, int arg_c, char *argv)
{
    int i = 0;
    char **arg_v; 
    char *env[] = {NULL};
    pid_t id;
    id = fork();
    
    if (!id)
    {
        arg_v = malloc(8 * (arg_c + 1));
        for (i = 0; i < arg_c; i++)
        {
            arg_v[i] = ptr;
            ptr += _strlen(ptr) + 1;
        }
        if (execve(arg_v[0], arg_v, env) == -1)
            perror(argv);
        free(arg_v);
        exit(-1);
    }
    wait(NULL);
}

char *get_path(char **envp)
{ 
    for (int i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], "PATH=", 5) == 0) {
          return (&envp[i][5]);
        }
    }
}
int main(int __attribute__ ((unused)) argc, char **argv, char **envp)
{
    size_t n = 0;
    ssize_t read;
    char *line = NULL, *ptr, *token, *env = strdup(get_path(envp)), *path_token, buffer[1024];
    int arg_c;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(1, "=> ", 3);
        read = getline(&line, &n, stdin);
        if (read == -1)
            return (-1);
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';
        ptr = line;
        token = strtok(line, " ");
        arg_c = 0;
        while (token)
        {
            token = strtok(NULL, " ");
            arg_c++;
        }
        path_token = strtok(env, ":");
        while (path_token)
        {
            
        }
        _exceve(ptr, arg_c, argv[0]);
    }
    free(line);
    return (0);
}