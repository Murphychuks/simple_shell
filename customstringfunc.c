#include "main.h"

/**
 * _strcmp - function checks  wether given strings
 * are identical or not
 *
 * @str1: first string to check against
 * @str2: second string to check against
 *
 * Return: 1 success case, 0 error case
 */
int _strcmp(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		return (0);
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (!*str1 && !*str2)
		return (1);
	return (0);
}




/**
* _strdup - function that takes a string and duplicates
* it and return new pointer of duplicated string
*
* @str: string to be duplicated
* Return: new char pointer to the new string
*/
char   *_strdup(const char *str)
{
	char *new_str;
	size_t  len, iterator;

	len = _strlen(str);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	new_str[len] = 0;
	iterator = 0;
	while (iterator < len)
	{
		new_str[iterator] = str[iterator];
		iterator++;
	}
	return (new_str);
}


/**
 * _strcat  - function that takes 2 string and
 * combines them
 *
 * @str1: first string
 * @str2: second string
 * Return: the combination of first and second string
 * NULL on error case
 */
char *_strcat(const char *str1, const char *str2)
{
	size_t len1, len2, iter;
	char *newstr;

	len1 = _strlen(str1);
	len2 = _strlen(str2);
	newstr = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!newstr)
		return (NULL);
	iter = 0;
	while (iter < len1)
	{
		newstr[iter] = str1[iter];
		iter++;
	}
	while (iter - len1 < len2)
	{
		newstr[iter] = str2[iter - len1];
		iter++;
	}
	newstr[iter] = 0;
	return (newstr);
}


/**
 * _strlen - function that calculate the length of given string
 *
 * @s: string (characters)
 * Return: number of characters
 */
size_t _strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}




/**
 * _strslice - function that  take string
 * and return specified part of it
 *
 * @line: to be sliced
 * @start: start position index zero based
 * @end: end position index zero based(excluded)
 * Return: part of the string
 */
char *_strslice(const char *line, int start, int end)
{
	char *slice;
	int len, iter;

	if (start < 0)
		start = 0;
	len = _strlen(line);
	if (len < end || end < 0)
		end = len;
	slice = malloc(sizeof(char) * (end - start + 1));
	iter = 0;
	while (start + iter < end)
	{
		slice[iter] = line[start + iter];
		iter++;
	}
	slice[iter] = 0;
	return (slice);
}
