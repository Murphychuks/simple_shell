#include "main.h"

/**
 * _atoi - function that convert
 * string into integer
 *
 * @str: to be converted
 * Return: converted integer
 */
int _atoi(const char *str)
{
	int number;
	int sign;

	sign = 1;
	number = 0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '+')
		str++;
	while (*str)
	{
		number = number * 10 + (*str - 48);
		str++;
	}
	return (number * sign);
}


/**
 * _count_number_length - function that
 * calculate the length of the given number
 *
 * @number: to calculate it's length
 * Return: length
 */
int _count_number_length(int number)
{
	int len;

	len = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		len++;
		number *= -1;
	}
	while (number)
	{
		len++;
		number /= 10;
	}
	return (len);
}


/**
 * _itoa - function convert number int
 * string
 *
 * @number: to be converted
 * Return: converted string
 */
char *_itoa(int number)
{
	int len;
	char *str_number;

	len = _count_number_length(number);
	str_number = malloc(sizeof(char) * (len + 1));
	if (!str_number)
		return (NULL);
	str_number[len] = 0;
	if (!number)
	{
		str_number[0] = '0';
		return (str_number);
	}
	if (number < 0)
	{
		str_number[0] = '-';
		number *= -1;
	}
	while (number)
	{
		str_number[--len] = number % 10 + 48;
		number /= 10;
	}
	return (str_number);
}


/**
 * _copy - function that copy data into dest
 *
 * @dest: buffer in which the data will be copied
 * @src: buffer source of the characters
 * @size: length of data that will be copied into line
 * Return: dest
 */
char *_copy(char *dest, const char *src, size_t size)
{
	size_t iter;

	iter = 0;
	while (iter < size)
	{
		dest[iter] = src[iter];
		iter++;
	}
	dest[iter] = 0;
	return (dest);
}


/**
   * pop_from_list - Remove and return data from front of list.
   * @list: Ptr to ptr of head of list.
   * Return: Ptr to data removed, or NULL if list is empty.
   */
void *pop_from_list(list_t **list)
{
	list_t *removed_node = *list;
	void *removed_data = removed_node->data;

	if (!list && *list == NULL)
	{
		return (NULL);
	}

	*list = removed_node->next;
	free(removed_node);

	return (removed_data);
}
