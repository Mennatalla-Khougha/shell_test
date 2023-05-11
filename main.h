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

#define STRING ((str) ? str : "(null)")

int _printf(const char *format, ...);
int p_char(char c);
int p_string(char *s);
void p_number(int n);
int num_len(int n);
int specifier(char c, va_list args);
int p_base(unsigned int n, int base, int cap, int len);
void p_u_number(unsigned int n);
int num_u_len(unsigned int n);
int p_address(unsigned long n, int len);
int h_address(unsigned long p);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
void _exceve(char *ptr, int arg_c, char *buff);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _atoi(char *s);
int _exit_(char *ptr, char *line, char *argv, int argc, int count);
void _command_(char *ptr, char *argv, char *path, int argc, int path_c, int count);
char *input(char **line, size_t *n);
int token(char *line, char *delim);
int rev_cmp(char *s1, char *s2);

#endif