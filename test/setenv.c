#include "main.h"

int _setenv(char *ptr, char *argv, char **envp, int argc, int count)
{
    char *name, *value, *env;
    if(strcmp(ptr, "setenv"))
        return 0;
    if(argc != 3){
        _printf("%s: %i: Usage: setenv VARIABLE VALUE\n", argv, count);
    }
    ptr += _strlen(ptr) + 1;
    name = ptr;
    ptr += _strlen(ptr) + 1;
    value = ptr;
    change_env(envp, name, value);
}

char *change_env(char **envp, char *name, char *value)
{
    int i, n_len = _strlen(name), v_len = _strlen(value);

    for (i = 0; envp[i] != NULL; i++) {
        if (_strncmp(envp[i], name, n_len) == 0) {
           envp[i];
           break;
        }
    }
    return (NULL);
}