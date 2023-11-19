#include "main.h"

/**
 * _evaluate_enviroment_variable - function
 * that takes key and return it's respective
 * value
 *
 * @env_key: key to retrieve it's value from enviroment
 * variables
 * Return: corresponding value to given key
 */
char *_evaluate_enviroment_variable(char *env_key)
{
	char *value;
	int number;

	if (_strcmp(env_key, "?"))
	{
		number = _status_management(GET_STATUS, 0);
		return (_itoa(number));
	}
	if (_strcmp(env_key, "$"))
		return (_itoa(getpid()));
	value = _enviroment_management(GET_VALUE, env_key, NULL);
	return (value);
}


/**
 * _unsetenv - function unset one entry from enviroment
 * variable
 *
 * @command: command that contains information about
 * entry that will be delete such as key of the entry
 * Return: status code
 */
int _unsetenv(command_t *command)
{
	int len;

	len = _str2dlen(command->arguments);
	if (len != 2)
	{
		_fprint(2, "%s: Invalid number of arguments\n",
				_global_states(GET_SHELL_NAME, NULL));
		return (1);
	}
	_enviroment_management(DELETE_ENTRY, command->arguments[1], NULL);
	return (0);
}


/**
 * _setenv - builtins that helps
 * add new entries to our envs
 * or update entries from it
 *
 * @command: struct that stores information
 * about current running command
 * Return: (0) success otherwise error
 */
int _setenv(command_t *command)
{
	int len;

	len = _str2dlen(command->arguments + 1);
	if (len != 2)
	{
		_fprint(2, "%s: Invalid number of arguments\n",
				_global_states(GET_SHELL_NAME, NULL));
		return (1);
	}
	_enviroment_management(
		SET_ENTRY,
		command->arguments[1],
		command->arguments[2]);
	return (0);
}


/**
 * _clear_map - frees the memory allocated for an entry in the hash table.
 *
 *@map: map to be freed
 * Return: nothing
 */
void _clear_map(map_t *map)
{
	int iterator;

	iterator = 0;
	while (iterator < BACKET_SIZE)
	{
		free_list(map->backets[iterator], _clear_entry);
		iterator++;
	}
	free(map);
}


/**
 * _clear_entry - frees the memory allocated for an entry in the hash table.
 *
 * @data :  entry data
 *
 * Return: nothing
 */
void _clear_entry(void *data)
{
	entry_t *entry;

	entry = data;
	free(entry->key);
	free(entry->value);
	free(data);
}
