#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t read;
    char *token;
    char *p;
    int argc, i;
    char **argv;
    char *env[] = {NULL};
    pid_t id;

    while (1)
    {
	    if (isatty(STDIN_FILENO))
            	printf("=> ");
            read = getline(&line, &n, stdin);
        if (read == -1) {
            break;
        }
	if (line[read - 1] == '\n')
		line[read - 1] = '\0';
        p = line;
        token = strtok(line, " ");
        argc = 0;
        while(token){
            token = strtok(NULL, " ");
            argc++;
        }
        id = fork();
        if (!id) {
            argv = malloc(8 * (argc + 1));
            for(i=0; i<argc; i++){
                argv[i] = p;
                p += strlen(p) + 1;
            }
            argv[i] = NULL;
            if (execve(argv[0], argv, env) == -1) {
                printf("error, unknown command.\n");
            }
        } else {
            wait(NULL);
        }
    }
    return 0;
}
