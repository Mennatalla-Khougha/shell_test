 #include "main.h"

/**
 * _command_ - handle the path of the command passed.
 * @line: input
 * @shell_name: the name of the shell
 * @path: the path
 * @n_token: number of token in command
 * @n_path: number of token in path
 * @count: number of command
 * @envp: array of environment variable
 * @status: status of last command.
 * Return: 0 or 127
 */

int _command_(char *line, char *shell_name, char *path, int n_token,
int n_path, int count, char **envp, int *status)
{
	int i;

	if (line[0] == '/')
	{
		if (access(line, X_OK) == 0)
		{
			if (!_env(envp, line))
				return (_exceve(line, n_token, line, status));
			return (0);
		}
		_printf("%s: %i: %s: not found\n", shell_name, count, line);
	}
	else
	{
		for (i = 0; i < n_path; i++)
		{
			char buffer[500] = "";

			_strcat(buffer, path);
			_strcat(buffer, "/");
			_strcat(buffer, line);
			if (access(buffer, X_OK) == 0)
			{
				if (!_env(envp, line))
					return (_exceve(line, n_token, buffer, status));
				return (0);
			}
			path += _strlen(path) + 1;
		}
		_printf("%s: %i: %s: not found\n", shell_name, count, line);
	}
	return (127);
}

/**
* _exceve - function executing the command
* @line: input
* @n_token: number of token
* @buff: input buffer
* @status: status of last command.
* Return: the exit status.
*/

int _exceve(char *line, int n_token, char *buff, int *status)
{
	int i;
	char **arg_v, *env[] = {NULL};
	pid_t id = fork();

	if (!id)
	{
		if (rev_cmp(line, "pwd"))
		{
			arg_v = malloc(16);
			if (arg_v == NULL)
				exit(255);
			arg_v[0] = line;
			arg_v[1] = NULL;
		}
		else
		{
			arg_v = malloc(8 * (n_token + 1));
			if (arg_v == NULL)
				exit(255);
			for (i = 0; i < n_token; i++)
			{
				arg_v[i] = line;
				line += _strlen(line) + 1;
			}
			arg_v[i] = NULL;
		}
		execve(buff, arg_v, env);
	}
	wait(status);
	return (WEXITSTATUS(*status));
}

/**
 * _exit_ - handle if exit the shell and the exit status.
 * @line: input
 * @shell_name: name of shell
 * @n_token: number of token
 * @count: number of command
 * @path: the path to be freed in success case.
 * @status: the status of the last command
 * Return: 0 success, 1 failure
*/
int _exit_(char *line, char *shell_name, int n_token, int count,
char *path, int status, char *pwd, char *old_pwd)
{
int len;

if (!strcmp(line, "exit"))
{
	if (n_token > 1)
	{
	len = _strlen(line) + 1;
	status = _atoi(line + len);
	}
	if (status != -1)
	{
	free(path);
	free(line);
	free(pwd);
	free(old_pwd);
	exit(status);
	}
	else
	_printf("%s: %i: exit: Illegal number: %s\n", shell_name, count, line + len);
		return (1);
}
if (status == 255)
	free_exit(line, path, pwd, old_pwd);
return (0);
}

/**
* token - function to return the splitted number of token
* @line: the string to be splitted
* @delim: the delim used to split the string
* Return:number of token splitted
*/

int token(char *line, char *delim)
{
	int n_token = 0;
	char *str_token = _strtok(line, delim);

	while (str_token)
	{
		str_token = _strtok(NULL, delim);
		n_token++;
	}
	return (n_token);
}

/**
* main - The entry point of the program
* @argc: number of argument to the program
* @argv: array of argument to the program
* @envp: array of environmental variable
* Return: 0;
*/

int main(int argc, char **argv, char **envp)
{
size_t n = 0;
char *line = NULL, *old_pwd, *path = _strdup(_get_env(envp, "PATH", 4));
int n_token, n_path, count = 0, status = 0, arrow = 1, file = 0;
int pid = (int)getpid(), cd_index = get_PWD(envp, path);

if (argc > 1)
{
	file = open(argv[1], O_RDONLY);
	if (file == -1)
	{
		_printf("%s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
		exit(2);
	}
}
old_pwd = malloc(256);
if(!old_pwd)
	free_exit(line, path, NULL, old_pwd);
old_pwd[0] = '\0';
_strcat(old_pwd, _get_env(envp, "PWD", 3));
n_path = token(path, ":");
while (1)
{
	count++;
	if (isatty(STDIN_FILENO) && arrow && !file)
		write(1, "=> ", 3);
	arrow = input(&line, &n, file);
	handle_input(&line, status, pid, envp);
	n_token = token(line, " ");
	if (cd(line, argv[0],  n_token, count, cd_index, envp, &status, &old_pwd))
		continue;
	if (_exit_(line, argv[0], n_token, count, path, status, envp[cd_index], old_pwd))
	{
		status = 2;
		continue;
	}
status = _command_(line, argv[0], path, n_token, n_path, count, envp, &status);
}
return (0);
}
