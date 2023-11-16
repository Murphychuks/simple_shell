#include "main.h"

/**
 *exec_child - function to executed a program at child process
 *@full_path: full pathname of the program to be executed
 *@args: 2d array containing each command tokenized
 *
 *Return: no value is returned
 */

int exec_child(char *full_path, char **args)
{
	int stat;

	if (full_path != NULL)
	{
		/* Execute the command with execve*/
		stat = execve(full_path, args, environ);
		if (stat == -1)
		{
			my_fprintf(stderr, "hsh: count:%s: Permission denied\n", args[0]);
			free(full_path);
			free_command_arguments(args);
			return (errno);
		}
/*		else
		{
			printf("exit status should be 127 + 2");
			exit(EXIT_SUCCESS);
			}*/
	}
	else
	{
		/*free all allocated memory*/
/*		free(full_path);*/
		free_command_arguments(args);
		return (127);
	}
}


/**
 *process_status - function to get the process status of an exited process
 *@p_status: an integer value representing the exit status of a process
 *
 *Return: no value is returned
 *
 */

int process_status(int p_status)
{
	int exit_status;

	if (WIFEXITED(p_status))
	{
		exit_status = WEXITSTATUS(p_status);
/*		if (exit_status == 0)
		{
			my_fprintf(stdout, "Environment:\n");*/
			return (exit_status);
	}
/*	else
	{
		my_fprintf(stderr, "Command execution failed.\n");
		return (exit_status);
		}
	printf("process status = %d\n", WIFEXITED(p_status));
	return (p_status);*/
}



/**
 *execute_command - function to execute a process(command)
 *@command: the command to be executed
 *@count: number of times process(es) has attempted execution per session
 *
 *Return: no value is returned
 */


/* Function to execute a command*/
int execute_command(char *command, int count)
{
	char **args;
	pid_t pid;
	char *full_path;
	int status, exit_status;
/*	char *variables[] = {"PWD", "HOME", "LANG", "LESSCLOSE",
		"TERM", "LESSOPEN", "SHLVL", "DEBUGINFOD_URLS",
		"PATH", "games", "OLDPWD", "_"};*/

	args = parse_command_arguments(command);
/*	if (args == NULL)
	{
		/*status = 0;
		return;
	}*/
	pid = fork();

	if (pid < 0)
	{
		perror("Fork failed");
		free_command_arguments(args);
		return (-1);
	}
	else if (pid == 0)
	{
		/* Child process*/
		full_path = get_full_pathname(args[0], count);

		/* Execute the command witth execve*/
		exit_status = exec_child(full_path, args);
	}
	else
	{
		/* Parent process*/
		waitpid(pid, &status, 0);

		/* Check if the child process exited successfully*/
		if (!exit_status)
			exit_status = process_status(status);

/*		my_fprintf(stdin, "\n\nEnvironments:\n");
		exec_env(variables);*/
		/* Free the memory allocated for parsed command arguments*/
		free_command_arguments(args);
		return (exit_status);
	}
}
