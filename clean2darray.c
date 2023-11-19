#include "main.h"

/**
 * _count_non_empty_string - function that counts
 * number of non empty string inside of 2d array
 *
 * @arr: 2d array to lookup for number of non empty
 * string
 * Return: number of non empty strings
 */
int _count_non_empty_string(char **arr)
{
	int len;

	len = 0;
	while (*arr)
	{
		len += (**arr != '\0');
		arr++;
	}
	return (len);
}

/**
 * _trim_2darray - function takes an array
 * and return new one with no empty string
 *
 * @arr: 2d array to remove non empty strings
 * from it
 * Return: 2d array without empty strings
 */
char **_trim_2darray(char **arr)
{
	int len;
	char **new_arr;

	len = _count_non_empty_string(arr);
	new_arr = malloc(sizeof(char *) * (len + 1));
	if (!new_arr)
		return (NULL);
	new_arr[len] = NULL;
	len = 0;
	while (*arr)
	{
		if (**arr)
		{
			new_arr[len] = _strdup(*arr);
			len++;
		}
		arr++;
	}
	return (new_arr);
}


/**
 * add_to_list - Add new node to end of list.
 * @lst: Ptr to ptr of head of list.
 * @data: Ptr to data to be stored.
 * Return: Ptr to newly added node.
 */
list_t *add_to_list(list_t **lst, void *data)
{
	list_t *new_node = (list_t *)malloc(sizeof(list_t));
	list_t *current;

	if (new_node == NULL)
	{
		return (NULL);
	}

	new_node->data = data;
	new_node->next = NULL;

	if (*lst == NULL)
	{
		*lst = new_node;
	}
	else
	{
		current = *lst;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}

	return (new_node);
}


/**
 * _isdigit - function that takes a
 * string and check wether it's digit or
 * not
 *
 * @s: string to check against
 * Return: 1 signify digits, 0 else
 */
int _isdigit(const char *s)
{
	if (!s)
		return (0);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}


/**
 * _get_comment_position - function that returns the
 * position of the # or the length of the line
 * if # not found
 *
 * @line: string to lookup in
 * Return: (integer) position of the #
 * or the length if not found
 */
int _get_comment_position(const char *line)
{
	int i;

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '#')
		{
			return (i);
		}
	}
	return (i);
}
