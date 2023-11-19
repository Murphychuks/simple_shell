#include "main.h"

/**
 * free_command - the function that frees command
 *
 * @command: command to be freed
 * Return: Nothing is to be returned
 */
void free_command(void *command)
{
	command_t *instruction;

	instruction = command;
	_free_split(&instruction->arguments);
	free(command);
}

/**
 * verify_command - function that search
 * for given command on the builtins
 * as well as in the path
 *
 * @command: command to be lookedup
 * @type: the type of the command
 * Return: proper path or command if it's builtin
 */
char *verify_command(char *command, command_type_t *type)
{

	if (_builtin_management(GET_BUILTIN, command, NULL))
	{
		*type = BUILTINS;
		return (_strdup(command));
	}

	return (_get_command_from_path(command));
}
/**
 * _init_the_command - function that initialize our
 * command
 *
 * @tokens: a 2d array holds all command arguments
 * and it contain command name in the first argument
 * Return: returns the allocated command
 */
command_t *_init_the_command(char **tokens)
{
	command_t *cmd;
	struct stat st;
	char *next;

	cmd = malloc(sizeof(command_t));
	if (!cmd)
		return (NULL);
	cmd->type = NOT_FOUND;
	next = verify_command(tokens[0], &cmd->type);
	free(tokens[0]);
	tokens[0] = next;
	if (cmd->type == NOT_FOUND &&
		(tokens[0][0] == '.' || tokens[0][0] == '/') &&
		!stat(tokens[0], &st))
		cmd->type = EXTERNAL;
	cmd->arguments = tokens;
	cmd->name = tokens[0];
	return (cmd);
}
/**
 * handle_cmds - function that takes line of commands
 * and turn into an easy command to work with
 *
 * @commandline: commands to be parsed
 * Return: returns a well strucered method
 */
command_t *handle_cmds(const char *commandline)
{
	char *trimmed_line, *command;
	char **tokens[2];
	int iterator;

	trimmed_line = _trim_white_space(commandline);
	tokens[0] = _split(trimmed_line, " ");
	free(trimmed_line);
	if (!tokens[0])
		return (NULL);
	iterator = 0;
	while (tokens[0][iterator])
	{
		if (tokens[0][iterator][0] == '$')
		{
			command = _evaluate_enviroment_variable(tokens[0][iterator] + 1);
			free(tokens[0][iterator]);
			if (command)
				tokens[0][iterator] = command;
			else
				tokens[0][iterator] = _strdup("");
		}
		iterator++;
	}
	tokens[1] = _trim_2darray(tokens[0]);
	_free_split(&tokens[0]);
	return (_init_the_command(tokens[1]));
}
