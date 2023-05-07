#include "main.h"

int main(void)
{
    pid_t pid;
    size_t n = 0, argc = 0, i;
    char *line = NULL, *delim = " \n", *token, **argv, *ptr = line;

    while (1) 
    {
        if (isatty(fileno(stdin)))
        {
            _printf("=>");
        }
            if (getline(&line, &n, stdin) == -1);
               break;
        token = strtok(line, delim);

        while (token)
        {
            token = (NULL, delim);
            argc++;
        }
        argv = malloc(8 * (argc + 1));
        for (i = 0; i < argc; i++)
        {
            argv[i] = ptr;
            ptr += strlen(ptr) + 1;
        }
        argv[i] = NULL;


        pid = fork();
        if (pid == -1)
        {
            perror("something went wrong");
            return 1;
        }
        else if (pid == 0)
        {
            printf("child\n");
            int exc = execve(token, argv, NULL);
        }
        else
        {
            wait(NULL);
            printf("after fork: parent\n");
        }
        free(line);
        free(argv);
        return (0);
    }
}