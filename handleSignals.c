#include "main.h"

/**
 * _handle_sigint - function that
 * will be called when control-c(SIGINT)
 * triggred
 *
 * @sig: Integer signifying the signal number
 * Return: void
 */
void _handle_sigint(int sig)
{
	(void)sig;
	fflush(stdin);
	if (isatty(STDIN_FILENO))
	{
		_fprint(1, "\n%s> ",
				_global_states(GET_SHELL_NAME, NULL));
	}
}


/**
 * handles_execution - function that take command
 * and execute it if command is file otherwise
 * persmission and status is been set to (126)
 *
 * @cmd: command to be executed
 * Return: returns nothing
 */
void handles_execution(command_t *cmd)
{
	if (access(cmd->name, F_OK | X_OK) != -1)
		_excute(cmd);
	else
	{
		_fprint(2, "%s: %d: %s: Permission denied\n",
				(char *)_global_states(GET_SHELL_NAME, NULL),
				*((int *)_global_states(GET_LINE_NUMBER, NULL)),
				cmd->name);
		_status_management(UPDATE_STATUS, 126);
	}
}


/**
 * _semicolon_handler - function that splits given
 * line bu semicolon and pass the result to be
 * handled by other functions
 *
 * @line: command line to be parsed and executed
 * Return: 1 on success or 0 signifying error
 */
int _semicolon_handler(const char *line)
{
	char **semi_commands, **iterator;
	command_t *command;
	int argument_length;

	iterator = semi_commands = _split(line, ";");
	if (!iterator)
		return (1);
	while (*iterator)
	{
		command = handle_cmds(*iterator);
		if (command->type == NOT_FOUND)
		{
			_fprint(2, "%s: %d: %s: not found\n",
					(char *)_global_states(GET_SHELL_NAME, NULL),
					*((int *)_global_states(GET_LINE_NUMBER, NULL)),
					command->name);
			_status_management(UPDATE_STATUS, 127);
		}
		else if (command->type == EXTERNAL)
			handles_execution(command);
		else
		{
			_global_states(SET_2D, semi_commands);
			_status_management(UPDATE_STATUS,
							   _builtin_management(
								   GET_BUILTIN,
								   command->name, NULL)(command));
		}
		argument_length = _str2dlen(command->arguments);
		_enviroment_management(SET_ENTRY, "_",
							   command->arguments[argument_length - 1]);
		free_command(command);
		iterator++;
	}
	_free_split(&semi_commands);
	return (0);
}


/**
 * _excute - function that excute commands
 * that's not part of builtins
 *
 * @command: command to be executed
 * Return: Nothing(void)
 */
void _excute(command_t *command)
{
	int pid, status, err;

	pid = fork();
	if (pid < 0)
	{
		perror((char *)_global_states(GET_SHELL_NAME, NULL));
		_status_management(UPDATE_STATUS, 1);
		return;
	}
	if (!pid)
	{
		execve(command->name, command->arguments, __environ);
		err = errno;
		if (errno == EACCES)
		{
			_fprint(2, "%s: %d: %s: Permission denied\n",
					(char *)_global_states(GET_SHELL_NAME, NULL),
					*((int *)_global_states(GET_LINE_NUMBER, NULL)),
					command->name);
			err = 126;
		}
		else
			perror(_global_states(GET_SHELL_NAME, NULL));
		free_command(command);
		free(_global_states(GET_LINE, NULL));
		_enviroment_management(CLEAR_ENV, NULL, NULL);
		_exit(err);
	}
	else
	{
		waitpid(pid, &status, 0);
		_status_management(UPDATE_STATUS, WEXITSTATUS(status));
	}
}


/**
 * _exclude_comment - remove comment from
 * line
 *
 * @line: full line that user entered
 * Return: new_line without comment
 */
char *_exclude_comment(const char *line)
{
	int comment_position;

	comment_position = _get_comment_position(line);
	return (_strslice(line, 0, comment_position));
}
