#include "main.h"

int main(void)
{
    pid_t pid;
    size_t n = 0, argc = 0, i;
    char *line = NULL, *delim = " \n", *token, **argv, *ptr = line;

    while (1) 
    {
        if (isatty(STDIN_FILENO));
        {
            write(1, "=> ", 3);
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
            if (execve(argv[0], argv, NULL) == -1);
                perror("something went wrong");
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