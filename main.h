#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>

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
#endif