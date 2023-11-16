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
	}
	else
	{
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
			return (exit_status);
	}

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

	args = parse_command_arguments(command);
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

		free_command_arguments(args);
		return (exit_status);
	}
}
