#include "main.h"


/**
 *check_command_in_current_path - check if command is current path
 *@command: command to be checked
 *
 *Return: duplicate of command if present else NULL
 */

char  *check_command_in_current_path(char *command)
{
	if (access(command, F_OK) == 0)
	{
		return (my_strdup(command));
	}
	else
		return (NULL);
}


/**
 *_getpath - function to get the environment variable PATH
 *@void: no argument expected
 *
 *Return: path if successful else null
 */
char *_getpath(void)
{
	char *path;

	path = getenv("PATH");
	if (path == NULL)
	{
		my_fprintf(stderr, "Trying to access PATH, but unable to get PATH environment variable.\n");
		return (NULL);
	}

	return (path);
}



/**
 *full_path_space - function to allocate space for full path
 *@path_copy: buffer to be freed if space allocation fails
 *
 *Return: allocated space if successful else null
 */

char *full_path_space(char *path_copy)
{
	char *full_path;

	full_path = (char *)malloc(MAX_PATH_LENGTH);
	if (full_path == NULL)
	{
		perror("Memory allocation failed");
		free(path_copy);
		return (NULL);
	}

	return (full_path);
}


/**
 *get_full_pathname - function to get full pathname
 *@command: process(command) to be executed
 *@count: number of processes attempted execution per session
 *
 *Return: full pathname if successful else null
 */


/* Function to get the full pathname of a command*/
char *get_full_pathname(char *command, int count)
{
	char *path;
	char *path_copy;
	char *token;
	char *full_path, *n_command;

	path = check_command_in_current_path(command);
	if (path != NULL)
	{
		return (path);
	}
	path = _getpath();
	if (path == NULL)
	{
		printf("path is NULL");
	}
	n_command = remove_path_prefix(command);
	path_copy = my_strdup(path);
	if (path_copy == NULL)
	{
		perror("Fail to duplicate path");
		return (NULL);
	}
	token = strtok(path_copy, ":");
	full_path = full_path_space(path_copy);
	while (token != NULL)
	{
		my_snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", token, n_command);
		if (access(full_path, X_OK) == 0)
		{
			if (n_command)
				free(n_command);
			free(path_copy);
			return (full_path);
		}
		token = strtok(NULL, ":");
	}
	if (n_command)
		free(n_command);
	free(full_path);
	free(path_copy);
	/* Command not found, print error and exit*/
	my_fprintf(stderr, "./hsh: %d: %s: not found\n", count, command);
	return (NULL);
}



