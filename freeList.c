#include "main.h"

/**
 * free_list - Free memory allocated for the list.
 * @list: Ptr to head of list.
 * @free_content: Ptr to function for freeing node content.
 * Return: void
 */
void free_list(list_t *list, void (*free_content)(void *data))
{
	list_t *current = list;
	list_t *next;

	while (current != NULL)
	{
		next = current->next;
		if (free_content != NULL)
		{
			free_content(current->data);
		}
		free(current);
		current = next;
	}
}



/**
 * _free_split - function that frees the allocted backets
 *
 * @backets: backets to free
 * Return: void
 */
void _free_split(char ***backets)
{
	char **head;

	head = *backets;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(*backets);
	*backets = NULL;
}


/**
 * _delete_entry - function that removes
 * entry from hashmap by given key index
 *
 * @map: map to delete entry from
 * @key: string key of the entry
 * Return: (0) success, (1) error
 */
int _delete_entry(map_t *map, const char *key)
{
	list_t *list, *tmp;
	int backet_index;
	entry_t *entry;

	backet_index = _get_hash_code(key);
	list = map->backets[backet_index];
	if (!list)
		return (0);
	entry = list->data;
	if (_strcmp(entry->key, key))
	{
		map->backets[backet_index] = list->next;
		_clear_entry(list->data);
		free(list);
		return (0);
	}
	while (list->next)
	{
		entry = list->next->data;
		if (_strcmp(entry->key, key))
		{
			tmp = list->next;
			list->next = list->next->next;
			_clear_entry(tmp->data);
			free(tmp);
			break;
		}
		list = list->next;
	}
	return (0);
}


/**
 * __exit - function that exit
 * from the program
 *
 * @command: struct that holds data
 * about command
 * Return: 0 success, otherwise error
 */
int __exit(command_t *command)
{
	char **iterator;
	int len;

	iterator = command->arguments + 1;
	len = _str2dlen(iterator);
	if (len > 0 && !_isdigit(*iterator))
	{
		_fprint(2, "%s: %d: exit: Illegal number: %s\n",
				_global_states(GET_SHELL_NAME, NULL),
				*((int *)_global_states(GET_LINE_NUMBER, NULL)),
				command->arguments[1]);
		return (2);
	}
	else
	{
		_enviroment_management(CLEAR_ENV, NULL, NULL);
		free(_global_states(GET_LINE, NULL));
		iterator = _global_states(GET_2D, NULL);
		_free_split(&iterator);
		if (!len)
		{
			free_command(command);
			_exit(_status_management(GET_STATUS, 0));
		}
		len = _atoi(command->arguments[1]);
		free_command(command);
		_exit(len);
	}
	return (0);
}


/**
 * _env - builtin function that print whatever
 * inside our enviroment variables
 *
 * @command: command_t contains informations
 * about the user command
 * Return: 0 success, 1 error
 */
int _env(command_t *command)
{
	char **iterator;

	(void)command;

	iterator = __environ;
	if (!iterator)
		return (1);
	while (*iterator)
	{
		_fprint(1, "%s\n", *iterator);
		iterator++;
	}
	return (0);
}
