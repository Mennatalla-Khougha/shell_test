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

typedef struct para
{
    char **envp;
    char **pwd;
    char *line;
    char *shell_name;
    char *path;
    char *old_pwd;
    int n_token;
    int n_path;
    int status;
    int count;
    int file;
    int pid;
} para;

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
int _exceve(para *args, char *buff);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _atoi(char *s);
int _exit_(para *args);
int _command_(para *args);
int input(para *args);
int token(char *line, char *delim);
int rev_cmp(char *s1, char *s2);
int _env(para *args);
ssize_t _getline(para *args);
unsigned int _strspn(char *s, char *accept);
void space(char **line, para *args);
char *_get_env(char **envp, char *env, int len);
void handle_input(para *args);
void handle_dollar(char *buffer, char **dollar, para *args);
char *handle_realloc(para *agrs, char *buffer, int *buffer_size, int extra, int max);
char **get_PWD(para *args);
int cd(para *args);
void change_pwd(para *args);
void free_exit(para *args);
char *_malloc(para *args, int size);

#endif
