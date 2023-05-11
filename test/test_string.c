#include "main.h"

int main(){
    char *argv[] = {"ls", "jhfjh", NULL};
    char *envp[] = {NULL};
    execve("/bin/ls", argv, envp);
}