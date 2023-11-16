#include "main.h"

/**
 *print_prompt - function to print a prompt to stdout/console/terminal
 *@void: doesn't taken any argument
 *
 *Return: no value is returned
 */

/* Function to print prompt*/
void print_prompt(void)
{
	fprintf(stdout, "$ ");
}


/**
 *read_command - function to read command using getline
 *@void: no commands expected
 *
 *Return:The read command excluding the new line character inserted by getline
 */

/* Function to read command*/
char *read_command(void)
{
	char *command = NULL;
	size_t n = 0;
	int len;

	if (getline(&command, &n, stdin) == -1)
	{
		free(command);
		return (NULL);
	}

	/* Remove the trailing newline character*/
	len = strlen(command);
	if (len > 0 && command[len - 1] == '\n')
	{
		command[len - 1] = '\0';
	}

	return (command);
}

/**
 *free_command - function to free the buffer used to hold input read by getline
 *@command: the buffer holding the input read by getline
 *
 *Return: no value is returned
 */

void free_command(char *command)
{
	free(command);
}


/**
 *my_strdup - custom function that behaves like std library strdup
 *@str: the string to be duplicated
 *
 *Return: the duplicated string
 */


char *my_strdup(const char *str)
{
	size_t  length;
	char *new_str;

	if (str == NULL)
	{
		return (NULL);
	}

	length = my_strlen(str);
	new_str = malloc(length + 1);

	if (new_str != NULL)
	{
		strcpy(new_str, str);
	}

	return (new_str);
}
