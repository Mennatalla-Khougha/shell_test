#include "main.h"

/**
 * p_base - print a number
 * @n: the num
 * @base: the base
 * @len: the len
 * @cap: the capitalization
 *
 * Return: len.
 */

int p_base(unsigned int n, int base, int cap, int len)
{
	unsigned int m = n;

	m /= base;
	if (m)
		len = p_base(m, base, cap, len);
	if (n % base < 10)
		len += p_char('0' + n % base);
	else
		len += p_char(cap + n % base);
	return (len);
}

/**
 * p_u_number - print unsigned number
 * @n: number to be printed
 *
 */

void p_u_number(unsigned int n)
{
	if (n / 10)
		p_number(n / 10);

	p_char((n % 10) + '0');
}

/**
 * num_u_len - return the number len
 * @n: number to be printed
 *
 * Return: len.
 */

int num_u_len(unsigned int n)
{
	int len = 1;

	p_u_number(n);
	while (n /= 10)
		len++;

	return (len);
}


/**
 * p_address - print address
 * @n: the addres
 * @len: len
 *
 * Return: len.
 */

int p_address(unsigned long n, int len)
{
	unsigned long m = n;

	m /= 16;
	if (m)
		len = p_address(m, len);
	if (n % 16 < 10)
		len += p_char('0' + n % 16);
	else
		len += p_char(87 + n % 16);
	return (len);
}