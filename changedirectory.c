#include "main.h"

/**
 * _cd_helper - function helper of cd
 * that takes key and look it up
 * in enviroments variable and change
 * directory to it
 *
 * @key: envs keys
 * Return: 0 success otherwise error
 */
int _cd_helper(const char *key)
{
	char *s, buffer[200];

	getcwd(buffer, 200);
	s = _enviroment_management(GET_VALUE, key, NULL);
	if (chdir(s) == -1)
	{
		free(s);
		return (errno);
	}
	_enviroment_management(SET_ENTRY, "OLDPWD", buffer);
	free(s);
	return (0);
}

/**
 * _cd_helper2 - function that takes
 * path as parameter and change
 * directory to it
 *
 * @path: path to change directory to it
 * Return: 0 on success ortherwise error
 */
int _cd_helper2(const char *path)
{
	char buffer[200];

	getcwd(buffer, 200);
	if (chdir(path) == -1)
	{
		perror(_global_states(GET_SHELL_NAME, NULL));
		return (errno);
	}
	_enviroment_management(SET_ENTRY, "OLDPWD", buffer);
	return (0);
}

/**
 * _cd - builtin function cd
 *  is a function that allows as
 * to navigate through out different
 * folders (directories) in our operating
 * system
 *
 * @command: struct the stores information
 * about passed commands
 * Return: (0) success otherwise errors
 */
int _cd(command_t *command)
{
	int len;

	len = _str2dlen(command->arguments + 1);

	if (len >= 1)
	{
		if (_strcmp("-", command->arguments[1]))
			return (_cd_helper("OLDPWD"));
		else if (_strcmp("~", command->arguments[1]))
			return (_cd_helper("HOME"));
		else
			return (_cd_helper2(command->arguments[1]));
	}
	else if (!len)
		return (_cd_helper("HOME"));
	return (0);
}


/**
 * _set_value - adds or updates a new entry
 * to the hash table with the given key and value.
 *
 *@map: map to add new entry to it
 *@key: string implies to key of the entry
 *@value: string implies to value of the entry
 *Return: 0 on error, 1 success
 */
int _set_value(map_t *map, const char *key, const char *value)
{
	int backet_index;
	list_t *iterator;
	entry_t *entry;

	backet_index = _get_hash_code(key);
	iterator = map->backets[backet_index];
	while (iterator)
	{
		entry = iterator->data;
		if (_strcmp(entry->key, key))
		{
			free(entry->value);
			entry->value = _strdup(value);
			return (1);
		}
		iterator = iterator->next;
	}
	entry = malloc(sizeof(entry_t));
	if (!entry)
		return (0);
	entry->key = _strdup(key);
	entry->value = _strdup(value);
	add_to_list(&map->backets[backet_index], entry);
	return (1);
}


/**
 * _prompt - function that asks
 * a user to enter a command
 *
 * Return: Nothing (void)
 */
void _prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		_fprint(1, "%s> ",
				_global_states(GET_SHELL_NAME, NULL));
	}
}
