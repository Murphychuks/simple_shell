#include "main.h"

/**
 *my_strncmp - custom function to compare n number of 2 strings
 *@str1: first string to be compared
 *@str2: second string to be compared against first string
 *
 *@n: number of string character to be compared
 *
 *Return: 0 always
 */

int my_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}

		if (*str1 == '\0')
		{
			/* checks if both str are equal until the '\0' or n characters reached?*/
			return (0);
		}

		str1++;
		str2++;
		n--;
	}

	/* Both strings are equal up to n characters*/
	return (0);
}



/**
 *remove_path_prefix - function to remove path prefix if any is passed
 *@str: command passed to be checked if prefix should be processed
 *
 *Return: a duplicate of the command passed
 */

char *remove_path_prefix(const char *str)
{
	const char *prefix = "/bin/";
	size_t prefix_len = strlen(prefix);

	if (my_strncmp(str, prefix, prefix_len) == 0)
	{
		return (my_strdup(str + prefix_len));
	}
	else if (my_strncmp(str, "/usr/bin/", strlen("/usr/bin/")) == 0)
	{
		return (my_strdup(str + strlen("/usr/bin/")));
	}
	else
		return (my_strdup(str));
}


/**
 *my_fprintf - custom function of std library fprintf
 *@stream: steam to print the string into
 *@format: formatted string to be printed
 *@...: other possible variable number of argument(s)
 *
 *Return: number of characters printed into the stream
 */

int my_fprintf(FILE *stream, const char *format, ...)
{
	int rv;
	va_list args;

	va_start(args, format);

	rv = vfprintf(stream, format, args);

	va_end(args);
	return (rv);
}



/**
 *my_snprintf - custom function of the std library snprintf
 *@str: buffer to hold a string
 *@size: size to be allocated to the buffer
 *@format: formatted string to be stored in the buffer
 *@*...: other possible variable number of arguments
 *
 *Return: number of characters writen into the buffer
 */

int my_snprintf(char *str, size_t size, const char *format, ...)
{
	int rv;
	va_list args;

	va_start(args, format);

	rv = vsnprintf(str, size, format, args);

	va_end(args);
	return (rv);
}
