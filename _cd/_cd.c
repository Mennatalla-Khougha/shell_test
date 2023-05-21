#include "main.h"

int cd(char *line, char *shell_name, int n_token, int count, int index, char **envp, int *status, char **old_pwd)
{
    char *dest;

    if (!strcmp(line, "cd"))
    {
	    if (n_token == 1)
            dest = _get_env(envp, "HOME", 4);
        else
        {
            line += 3;
            if (!strcmp(line, "-"))
            {
               dest = *old_pwd;
               write(1, dest, _strlen(dest));
               write(1, "\n", 1);
            }
            else
                dest = line;
        }
        if(chdir(dest) == -1)
        {
            _printf("%s: %i: cd: an't cd to %s\n", shell_name, count, dest); 
            *status = 2;
        }
        else
        {
            free(*old_pwd);
            *old_pwd = malloc(256);
            if(!old_pwd)
                exit(-1);
            (*old_pwd)[0] = '\0';
            _strcat(*old_pwd, &envp[index][4]);
            change_pwd(envp, index);
            *status = 0;
        }
        return (1);
    }
    return (0);
}

void change_pwd(char **envp, int index)
{
    char buffer[250];
	char *pwd = malloc(256);
    if (!pwd){
        exit(-1);
    }
    getcwd(buffer, 250);
    pwd[0] = '\0';
    _strcat(pwd, "PWD=");
    _strcat(pwd, buffer);
    free(envp[index]);
    envp[index] = pwd;
}

int get_PWD(char **envp, char *path)
{
    int i;
    char *pwd;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (_strncmp(envp[i], "PWD", 3) == 0)
		{
            pwd = malloc(_strlen(envp[i]) + 1);
            if (!pwd)
            {
                if (path)
                    free(path);
                exit(255);
            }
            pwd[0] = '\0';
            _strcat(pwd, envp[i]);
            envp[i] = pwd;
            return (i);
        }
	}
	return (0);
}

void free_exit(char *line, char *path, char *pwd, char *old_pwd)
{
    if (line)
        free(line);
    if (path)
        free(path);
    if (pwd)
        free(pwd);
    if (old_pwd)
        free(old_pwd);
    exit(255);
}