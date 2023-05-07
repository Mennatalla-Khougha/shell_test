#include "main.h"

/**
 * h_address - handle printing the address.
 * @p: the address
 *
 * Return: the len.
 */

int h_address(unsigned long p)
{
	int len = 0;

	if (!p)
		return (p_string("(nil)"));
	len += p_char('0');
	len += p_char('x');
	len += p_address(p, 0);
	return (len);
}


/**
 * _printf - print.
 * @format: the format
 *
 * Return: the number of chars
 */

int _printf(const char *format, ...)
{
	unsigned int i, len = 0;
	va_list args;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	for (i = 0; format[i]; i++)
	{
		if (format[i] != '%')
		{
			len += p_char(format[i]);
			continue;
		}
		if (i++ == strlen(format) - 1)
			return (-1);
		len += specifier(format[i], args);
	}
	va_end(args);
	return (len);
}
