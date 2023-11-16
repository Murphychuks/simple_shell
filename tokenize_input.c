#include "main.h"


/**
 *parse_commands - function to tokenize commands into individual commands
 *@commands: commands read,each command terminated by ";"
 *
 *Return: a 2d array containning  separated commands
 *
 */

/* Function to parse commands separated by semi-colon */
char **parse_commands(char *commands)
{
	char **parsed_commands;
	char *token;
	int count = 0, len;
	char *trimmed_command;
	char *delimeters = ";";/*\'&&'\t\n";*/

	parsed_commands = malloc(MAX_COMMANDS * sizeof(char *));
	if (parsed_commands == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	/* Tokenize the commands using delimeters*/
	token = strtok(commands, delimeters);
/*	if (token == NULL)
	{
		/*check and handle, if no more commands to be tokenized
		if (commands != NULL)
		{
			token = strtok(NULL, delimeters);
		}
		else
			token = NULL;
	}*/
	while (token != NULL && count < MAX_COMMANDS - 1)
	{
	    /* Trim leading and trailing whitespaces*/
		trimmed_command = token;
		while (*trimmed_command == ' ')
			trimmed_command++;
		len = my_strlen(trimmed_command);
		while (len > 0 && trimmed_command[len - 1] == ' ')
			trimmed_command[--len] = '\0';
		parsed_commands[count++] = strdup(trimmed_command);
		token = strtok(NULL, delimeters);
	}

    /* Set the last element of the array to NULL to indicate the end*/
	parsed_commands[count] = NULL;

	return (parsed_commands);
}


/**
 *free_commands - free the 2d array holding content from parsed_commands func
 *@parsed_commands: 2d array holding the tokenized commands
 *
 *Return: no value is returned
 */

/* Function to free the memory allocated for parsed commands*/
void free_commands(char **parsed_commands)
{
	int i;

	if (parsed_commands == NULL)
		return;

	for (i = 0; parsed_commands[i] != NULL; i++)
	{
		free(parsed_commands[i]);
	}
	free(parsed_commands);
}


/**
 *parse_command_arguments - function to tokenize each command using " "
 *@command: each command to be tokenized
 *
 *Return: 2d array representing the newly tokenized array of each command
 */


/* Func to parse a single command into arguments based on space separation*/
char **parse_command_arguments(char *command)
{
	char **args;
	int count = 0;
	char *token;
	char *delimeter = " \n\t";

	args = malloc(MAX_ARGS * sizeof(char *));
	if (args == NULL)
	{
		perror("Not enough space for arguments ");
		exit(EXIT_FAILURE);
	}


	/* Tokenize the command using " "*/
	token = strtok(command, delimeter);
	if (token == NULL)
		return (NULL);
	while (token != NULL && count < MAX_ARGS - 1)
	{
		args[count++] = my_strdup(token);
		token = strtok(NULL, delimeter);
	}

	/* Set the last element of the array to NULL to indicate the end*/
	args[count] = NULL;

	return (args);
}


/**
 *free_command_arguments - free the 2d array holding content of each commands
 *@args: 2d array holding the tokenized commands
 *
 *Return: no value is returned
 */


/* Function to free the memory allocated for parsed command arguments*/
void free_command_arguments(char **args)
{
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}


/**
 *my_strlen - function to get the length of a given string
 *@str: the given str whose length is to be determined
 *
 *Return: the gotten length of the string
 */

size_t my_strlen(const char *str)
{
	const char *ptr = str;

	while (*ptr != '\0')
	{
		ptr++;
	}
	return (ptr - str);
}
