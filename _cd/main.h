#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define STRING ((str) ? str : "(null)")

int _printf(const char *format, ...);
int p_char(char c);
int p_string(char *s);
void p_number(int n);
int num_len(int n);
int specifier(char c, va_list args);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strtok(char *str, const char *delim);
char *_strchr(char *s, char c);
char *_strncat(char *dest, char *src, int n);
int _strcmp(char *str1, char *str2);
void tostring(char *str, int num);
int _exceve(char *ptr, int arg_c, char *buff, int *status);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _atoi(char *s);
int _exit_(char *line, char *shell_name, int n_token, int count,
char *path, int status, char *pwd, char *old_pwd);
int _command_(char *ptr, char *argv, char *path, int argc,
int path_c, int count, char **envp, int *status);
int input(char **line, size_t *n, int file);
int token(char *line, char *delim);
int rev_cmp(char *s1, char *s2);
int _env(char **env, char *ptr);
ssize_t _getline(char **line, size_t *n, int stream);
unsigned int _strspn(char *s, char *accept);
void space(char **line);
char *_get_env(char **envp, char *env, int len);
void handle_input(char **line, int val, int pid, char **envp);
void handle_dollar(char *ptr, char **s, int val, int pid, char **envp);
char *handle_realloc(char *buffer, int *buffer_size, int extra, int max);
int get_PWD(char **envp, char *path);
int cd(char *line, char *shell_name, int n_token, int count, int index, char **envp, int *status, char **old_pwd);
void change_pwd(char **envp, int index);
void free_exit(char *line, char *path, char *pwd, char *old_pwd);
#endif
