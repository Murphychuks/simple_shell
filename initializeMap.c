#include "main.h"

/**
 * _init_map - initializes a new hash table and returns a pointer to it.
 *
 * Return: a pointer two inititialized map
 */
map_t *_init_map(void)
{
	map_t *map = (map_t *)malloc(sizeof(map_t));
	int    iterator;

	iterator = 0;
	while (iterator < BACKET_SIZE)
	{
		map->backets[iterator] = NULL;
		iterator++;
	}
	return (map);
}


/**
 * _get_hash_code - calculates the hash code for a given key.
 *
 * @key: key to be hash
 *
 * Return: return an integer signify hashed code of the given key
 */
int _get_hash_code(const char *key)
{
	int hash = 0;
	int i;

	for (i = 0; key[i] != '\0'; i++)
	{
		hash += key[i];
	}

	return (hash % BACKET_SIZE);
}


/**
 * _get_keys - retrieves a linked list of all the keys in the hash table.
 *
 *@map: map to retrieve
 * Return: list of keys
 */
list_t    *_get_keys(const map_t *map)
{
	list_t    *list, *iterator;
	entry_t  *entry;
	int      iter;

	list = NULL;
	iter = 0;
	while (iter < BACKET_SIZE)
	{
		iterator = map->backets[iter];
		while (iterator)
		{
			entry = iterator->data;
			add_to_list(&list, _strdup(entry->key));
			iterator = iterator->next;
		}
		iter++;
	}
	return (list);
}


/**
 * _get_value - retrieves the value associated
 * with the given key from the hash table.
 *
 *@map: map to get the value from
 *@key: key to retieve the associated value
 * Return: pointer to the value or NULL in error
 */
char  *_get_value(const map_t *map, const char *key)
{
	int    backet_index;
	list_t  *backet;
	entry_t  *entry;

	backet_index = _get_hash_code(key);
	backet = map->backets[backet_index];
	while (backet)
	{
		entry = backet->data;
		if (_strcmp(entry->key, key))
			return (entry->value);
		backet = backet->next;
	}
	return (NULL);
}


/**
 * _listlen - function that calculate the
 * length of the given linkedlist
 *
 * @list: to calculate it's length
 * Return: length of list
 */
size_t _listlen(const list_t *list)
{
	size_t len;

	len = 0;
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}
